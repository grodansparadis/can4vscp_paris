/* ******************************************************************************
 * 	VSCP (Very Simple Control Protocol) 
 * 	http://www.vscp.org
 *
 *  Paris Smart Relay Module
 * 	akhe@grodansparadis.com
 *
 *  Copyright (C) 1995-2015 Ake Hedman, Grodans Paradis AB
 *                          <akhe@grodansparadis.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 *	This file is part of VSCP - Very Simple Control Protocol 	
 *	http://www.vscp.org
 *
 * ******************************************************************************
 */

#include "vscp_compiler.h"
#include "vscp_projdefs.h"

#include <p18cxxx.h>
#include <timers.h>
#include <delays.h>
#include <inttypes.h>
#include <ecan.h>
#include <vscp_firmware.h>
#include <vscp_class.h>
#include <vscp_type.h>
#include "smartrelay.h"
#include "version.h"


#if defined(RELEASE)

#pragma config WDT = ON, WDTPS = 128
#pragma config OSC = HSPLL
#pragma config BOREN = BOACTIVE
#pragma config STVREN = ON
#pragma config BORV = 3
#pragma config LVP = ON
#pragma config CPB = ON
#pragma config BBSIZ = 2048
#pragma config WRTD  = OFF

#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF

#pragma config EBTRB = OFF

#else

#pragma config WDT = OFF
#pragma config OSC = HSPLL
#pragma config PWRT = ON
#pragma config BOREN = BOACTIVE
#pragma config STVREN = ON
#pragma config BORV = 3
#pragma config LVP = OFF
#pragma config CPB = OFF
#pragma config WRTD  = OFF

#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF

#pragma config EBTRB = OFF

#endif

// Startup code from c018.c
//void _startup(void);

// Calculate and st required filter and mask
// for the current decision matrix
void calculateSetFilterMask( void );

//extern const rom int log_Table[]; // log10 for Hummidity measurement

// The device URL (max 32 characters including null termination)
const uint8_t vscp_deviceURL[] = "www.eurosource.se/paris_010.xml";

volatile unsigned long measurement_clock; // Clock for measurments

uint8_t sendTimer;  // Timer for CAN send
uint8_t seconds;    // counter for seconds
uint8_t minutes;    // counter for minutes
uint8_t hours;      // Counter for hours

// Bit set for relay that should pulse
// bit 0 - Relay 0 etc
uint8_t relay_pulse_flags;

// An array with 16-bit timers one
// for each relay
uint16_t relay_pulse_timer[8];

// An array with 16-bit timers one
// for each relay
uint16_t relay_protection_timer[8];


///////////////////////////////////////////////////////////////////////////////
// Isr() 	- Interrupt Service Routine
//      	- Services Timer0 Overflow
//      	- Services GP3 Pin Change
//////////////////////////////////////////////////////////////////////////////

#ifdef RELOCATE
//#pragma code low_vector = 0x208
#else
//#pragma code low_vector = 0x08
#endif

void interrupt low_priority  interrupt_at_low_vector( void )
{
    // Clock
    if ( INTCONbits.TMR0IF ) { // If a Timer0 Interrupt, Then...

        // Reload value for 1 ms reolution
        WriteTimer0(TIMER0_RELOAD_VALUE);
        
        vscp_timer++;
        vscp_configtimer++;
        measurement_clock++;
        sendTimer++;

        // Check for init button
        if ( INIT_BUTTON ) {
            vscp_initbtncnt = 0;
        } else {
            // Active
            vscp_initbtncnt++;
        }

        // Status LED
        vscp_statuscnt++;
        if ( ( VSCP_LED_BLINK1 == vscp_initledfunc ) &&
                ( vscp_statuscnt > 100 ) ) {

            if ( STATUS_LED ) {
                STATUS_LED = 0;
            }
            else {
                STATUS_LED = 1;
            }

            vscp_statuscnt = 0;

        }
        else if (VSCP_LED_ON == vscp_initledfunc) {
            STATUS_LED = 1;
            vscp_statuscnt = 0;
        }
        else if (VSCP_LED_OFF == vscp_initledfunc) {
            STATUS_LED = 0;
            vscp_statuscnt = 0;
        }

        INTCONbits.TMR0IF = 0; // Clear Timer0 Interrupt Flag

    }

    return;
}


//***************************************************************************
// Main() - Main Routine
//***************************************************************************

void main()
{
    init(); // Initialize Micro controller

    // Check VSCP persistent storage and
    // restore if needed
    if ( !vscp_check_pstorage() ) {

        // Spoiled or not initialized - reinitialize
        init_app_eeprom();
        init_app_ram();     // Needed because some ram positions
                            // are initialized from EEPROM

    }

    vscp_init();    // Initialize the VSCP functionality

    while ( 1 ) {   // Loop Forever

        ClrWdt();   // Feed the dog

        if ( ( vscp_initbtncnt > 250 ) &&
                ( VSCP_STATE_INIT != vscp_node_state ) ) {

            // Init. button pressed
            vscp_nickname = VSCP_ADDRESS_FREE;
            eeprom_write( VSCP_EEPROM_NICKNAME, VSCP_ADDRESS_FREE );
            vscp_init();
            
        }

        // Check for a valid  event
        vscp_imsg.flags = 0;
        vscp_getEvent();

        switch ( vscp_node_state ) {

            case VSCP_STATE_STARTUP: // Cold/warm reset

                // Get nickname from EEPROM
                if (VSCP_ADDRESS_FREE == vscp_nickname) {
                    // new on segment need a nickname
                    vscp_node_state = VSCP_STATE_INIT;
                } else {
                    // been here before - go on
                    vscp_node_state = VSCP_STATE_ACTIVE;
                    vscp_goActiveState();
                }
                break;

            case VSCP_STATE_INIT: // Assigning nickname
                vscp_handleProbeState();
                break;

            case VSCP_STATE_PREACTIVE:  // Waiting for host initialisation
                vscp_goActiveState();
                break;

            case VSCP_STATE_ACTIVE:     // The normal state

                // Check for incoming event?
                if (vscp_imsg.flags & VSCP_VALID_MSG) {

                    if ( VSCP_CLASS1_PROTOCOL == vscp_imsg.vscp_class  ) {

                        // Handle protocol event
                        vscp_handleProtocolEvent();

                    }

                    doDM();
					
                }
                break;

            case VSCP_STATE_ERROR: // Everything is *very* *very* bad.
                vscp_error();
                break;

            default: // Should not be here...
                vscp_node_state = VSCP_STATE_STARTUP;
                break;

        }

        // do a measurement if needed
        if ( measurement_clock > 1000 ) {

            measurement_clock = 0;
 
            // Do VSCP one second jobs
            vscp_doOneSecondWork();

            // Temperature report timers are only updated if in active
            // state guid_reset
            if ( VSCP_STATE_ACTIVE == vscp_node_state ) {

                // Do VSCP one second jobs
                doApplicationOneSecondWork();

            }

        }

        // Timekeeping
        if ( seconds > 59 ) {

            seconds = 0;
            minutes++;

            if ( minutes > 59 ) {
                minutes = 0;
                hours++;
            }

            if ( hours > 23 ) hours = 0;

        }

        doWork();

    } // while
}

///////////////////////////////////////////////////////////////////////////////
// Init - Initialization Routine
//  

void init()
{

    //uint8_t msgdata[ 8 ];

    // Initialize data
    init_app_ram();

    // Initialize the uP

    // PORTA
    // RA0/AN0  - output
    // RA1/AN1  - output
    // RA2/AN2  - output
    // RA3/AN3  - output
    // RA4      - output
    // RA5/AN4  - output
    TRISA = 0x00;
    PORTA = 0x00;

    // PortB

    // RB0/AN10     - output    Relay 2 (I3)
    // RB1/AN8      - output    Relay 1 (I2)
    // RB2 CAN TX   - output
    // RB3 CAN RX   - input
    // RB4/AN9      - Out       Relay 0 (I1)
    // RB5/LVPGM    - Not used = output.
    // RB&/PGC      - Not used = output.
    // RB7/PGD      - Not used = output.
    TRISB = 0b00001000;
    PORTB = 0x00;

    // RC0 - Input  - Init button
    // RC1 - Output - Status LED - Default off
    // RC2 - Output - Not used.
    // RC3 - Output - Not used.
    // RC4 - Output - Relay 6 (I7).
    // RC5 - Output - Relay 5 (I6).
    // RC6 - Output - Relay 4 (I5).
    // RC7 - Output - Telay 3 (I4).
    TRISC = 0b00000001;
    PORTC = 0x00;

/*
    // Sensor 0 timer
    OpenTimer0( TIMER_INT_OFF &
                    T0_16BIT &
                    T0_PS_1_2 &
                    T0_SOURCE_INT);

    // Sensor 1 timer
    OpenTimer1( TIMER_INT_OFF &
                    T1_16BIT_RW &
                    T1_SOURCE_INT &
                    T1_PS_1_1 &
                    T1_OSC1EN_OFF &
                    T1_SYNC_EXT_OFF);

    // Timer 2 is used as a 1 ms clock
    // 156 is loaded eight time to give ~1250 cycles
    PR2 = TIMER2_RELOAD_VALUE; // Set reload value
    OpenTimer2( TIMER_INT_ON &
                    T2_PS_1_4 &
                    T2_POST_1_16 );

 */

    OpenTimer0( TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_8 );
    WriteTimer0( TIMER0_RELOAD_VALUE );

    // Set relays to there off position
    RELAY0 = 0;
    RELAY1 = 0;
    RELAY2 = 0;
    RELAY3 = 0;
    RELAY4 = 0;
    RELAY5 = 0;
    RELAY6 = 0;

    // Initialize CAN
    ECANInitialize();

    // Must be in Config mode to change many of settings.
    //ECANSetOperationMode(ECAN_OP_MODE_CONFIG);

    // Return to Normal mode to communicate.
    //ECANSetOperationMode(ECAN_OP_MODE_NORMAL);

    /*
        msgdata[ 0 ] = 1;
            msgdata[ 1 ] = 2;
            msgdata[ 2 ] = 3;
            msgdata[ 3 ] = 4;

            if ( vscp18f_sendMsg( 0x123,  msgdata, 4, CAN_TX_PRIORITY_0 & CAN_TX_XTD_FRAME & CAN_TX_NO_RTR_FRAME ) ) {
                    ;
            }

     */

    // Enable peripheral interrupt
    INTCONbits.PEIE = 1;

    // Enable global interrupt
    INTCONbits.GIE = 1;

    return;
}

///////////////////////////////////////////////////////////////////////////////
// init_app_ram
//

void init_app_ram( void )
{
    uint8_t i;

    measurement_clock = 0;      // start a new meaurement cycle

    seconds = 0;
    minutes = 0;
    hours = 0;

    relay_pulse_flags = 0;      // No pulse outputs yet

    // Clear timers
    for ( i = 0; i < 8; i++ ) {
        relay_pulse_timer[ i ] = 0;
        relay_protection_timer[ i ] = 0;
    }

    for ( i=0; i<7; i++ ) {

        // Init pulsed relays
        if ( eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i ) &
                                RELAY_CONTROLBIT_PULSE ) {

            relay_pulse_flags |= (1<<i); // Enable pulse output
            relay_pulse_timer[ i ] =
                eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB + i ) * 256 +
                eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB + i );
        }

        // Init protection timers
        if ( eeprom_read(VSCP_EEPROM_END + REG_RELAY5_CONTROL + i ) & RELAY_CONTROLBIT_PROTECTION) {
            relay_protection_timer[ i ] =
                eeprom_read(VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_MSB + i ) * 256 +
                eeprom_read(VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_LSB + i );
        }

    }
    
}


///////////////////////////////////////////////////////////////////////////////
// init_app_eeprom
//

void init_app_eeprom(void)
{
    unsigned char i, j;

    eeprom_write( VSCP_EEPROM_END + REG_RELAY_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY_SUBZONE, 0 );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_CONTROL,
                    RELAY_CONTROLBIT_ONEVENT |
                    RELAY_CONTROLBIT_OFFEVENT |
                    RELAY_CONTROLBIT_ENABLED );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_PULSE_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_PULSE_TIME_LSB, 0  );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_LSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_PROTECTION_TIME_MSB, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_PROTECTION_TIME_LSB, 0 );

    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY0_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY1_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY2_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY3_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY4_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY5_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY6_SUBZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_ZONE, 0 );
    eeprom_write( VSCP_EEPROM_END + REG_RELAY7_SUBZONE, 0 );

    // * * * Decision Matrix * * *
    // All elements disabled.
    for ( i = 0; i < DESCION_MATRIX_ROWS; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            eeprom_write( VSCP_EEPROM_END + REG_DESCION_MATRIX + i * 8 + j, 0 );
        }
    }

}

///////////////////////////////////////////////////////////////////////////////
// doApplicationOneSecondWork
//

void doApplicationOneSecondWork(void)
{

    uint8_t i;
    uint8_t ctrlreg; // Current control register
    BOOL bOn = FALSE;

    for ( i = 0; i < 8; i++ ) {

        // Get control register for this relay
        ctrlreg = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i );

        // If not enabled check next
        if ( !( ctrlreg & RELAY_CONTROLBIT_ENABLED ) ) continue;

        // * * * Protection timer * * *

        if ( relay_protection_timer[ i ] ) {

            relay_protection_timer[ i ]--;

            // Check if its time to act on protection time
            if ( !relay_protection_timer[ i ] &&
                    ( eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i ) &
                                    RELAY_CONTROLBIT_PROTECTION ) ) {

                // Yes - its time to protect this relay
                doActionOff( 0, (1 << i) );

                // Should alarm be sent?
                if ( ctrlreg & RELAY_CONTROLBIT_ALARM ) {
                    SendInformationEvent( i, VSCP_CLASS1_ALARM,
                                            VSCP_TYPE_ALARM_ALARM );
                }

            }
        }
        else {
            // Reload protection timer
            relay_protection_timer[ i ] =
                    eeprom_read(VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB + i ) * 256 +
                    eeprom_read(VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB + i );
        }

        // * * * Pulsed relays * * *
        if ( relay_pulse_flags & (1 << i) ) {

            if ( relay_pulse_timer[ i ] ) {

                relay_pulse_timer[ i ]--;

                // If zero its time for state change
                if ( !relay_pulse_timer[ i ] ) {

                    switch ( i ) {

                        case 0:
                            if ( RELAY0 ) {
                                RELAY0 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY0 = 1;
                                bOn = TRUE;
                            }
                            break;

                        case 1:
                            if ( RELAY1 ) {
                                RELAY1 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY1 = 1;
                                bOn = TRUE;
                            }
                            break;

                        case 2:
                            if ( RELAY2 ) {
                                RELAY2 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY2 = 1;
                                bOn = TRUE;
                            }
                            break;

                        case 3:
                            if ( RELAY3 ) {
                                RELAY3 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY3 = 1;
                                bOn = TRUE;
                            }
                            break;

                        case 4:
                            if ( RELAY4 ) {
                                RELAY4 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY4 = 1;
                                bOn = TRUE;
                            }
                            break;

                        case 5:
                            if ( RELAY5 ) {
                                RELAY5 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY5 = 1;
                                bOn = TRUE;
                            }
                            break;

                        case 6:
                            if ( RELAY6 ) {
                                RELAY6 = 0;
                                bOn = FALSE;
                            } else {
                                RELAY6 = 1;
                                bOn = TRUE;
                            }
                            break;

                    }

                    // Reload pulse timer
                    relay_pulse_timer[ i ] =
                            eeprom_read( VSCP_EEPROM_END +
                                            REG_RELAY0_PULSE_TIME_MSB + 2*i ) * 256 +
                            eeprom_read( VSCP_EEPROM_END +
                                            REG_RELAY0_PULSE_TIME_LSB + 2*i );

                    if ( bOn ) {

                        // Reload protection timer
                        if ( eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i ) & RELAY_CONTROLBIT_PROTECTION ) {
                            relay_protection_timer[ i ] =
                                eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB + 2*i ) * 256 +
                                eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB + 2*i );
                        }

                        if ( ctrlreg & RELAY_CONTROLBIT_ONEVENT ) {
                            SendInformationEvent( i, VSCP_CLASS1_INFORMATION,
                                                    VSCP_TYPE_INFORMATION_ON );
                        }

                        if ( ctrlreg & RELAY_CONTROLBIT_STARTEVENT ) {
                            SendInformationEvent( i, VSCP_CLASS1_INFORMATION,
                                                    VSCP_TYPE_INFORMATION_START );
                        }

                    } else {

                        if ( ctrlreg & RELAY_CONTROLBIT_OFFEVENT ) {
                            SendInformationEvent( i, VSCP_CLASS1_INFORMATION,
                                                    VSCP_TYPE_INFORMATION_OFF );
                        }

                        if (ctrlreg & RELAY_CONTROLBIT_STOPEVENT) {
                            SendInformationEvent( i, VSCP_CLASS1_INFORMATION,
                                                    VSCP_TYPE_INFORMATION_STOP );
                        }
                    }

                } // State change

            } // Something to count down
            else {
                // Reload the pulse timer
                relay_pulse_timer[ 0 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB + 2*i ) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB + 2*i );
            }

        } // Pulse bit

    } // for all relays
}



///////////////////////////////////////////////////////////////////////////////
// Get Major version number for this hardware module
//

unsigned char getMajorVersion()
{
    return FIRMWARE_MAJOR_VERSION;
}

///////////////////////////////////////////////////////////////////////////////
// Get Minor version number for this hardware module
//

unsigned char getMinorVersion()
{
    return FIRMWARE_MINOR_VERSION;
}

///////////////////////////////////////////////////////////////////////////////
// Get Subminor version number for this hardware module
//

unsigned char getSubMinorVersion()
{
    return FIRMWARE_SUB_MINOR_VERSION;
}

///////////////////////////////////////////////////////////////////////////////
// Get GUID from EEPROM
//

#ifdef ENABLE_WRITE_2PROTECTED_LOCATIONS

void vscp_setGUID(uint8_t idx, uint8_t data ) {
    if ( idx>15 ) return;
    eeprom_write(VSCP_EEPROM_REG_GUID + idx, data);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Get Manufacturer id and subid from EEPROM
//

#ifdef ENABLE_WRITE_2PROTECTED_LOCATIONS

void vscp_setManufacturerId( uint8_t idx, uint8_t data ) {
    if ( idx>7 ) return;
    eeprom_write(VSCP_EEPROM_REG_MANUFACTUR_ID0 + idx, data);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Get the bootloader algorithm code
//

unsigned char getBootLoaderAlgorithm(void)
{
    return VSCP_BOOTLOADER_PIC1;
}

///////////////////////////////////////////////////////////////////////////////
// Get the buffer size
//

unsigned char getBufferSize(void)
{
    return 8; // Standard CAN frame
}

///////////////////////////////////////////////////////////////////////////////
//  vscp_readNicknamePermanent
//

uint8_t vscp_readNicknamePermanent(void)
{
    return eeprom_read( VSCP_EEPROM_NICKNAME );
}

///////////////////////////////////////////////////////////////////////////////
//  vscp_writeNicknamePermanent
//

void vscp_writeNicknamePermanent(uint8_t nickname)
{
    eeprom_write( VSCP_EEPROM_NICKNAME, nickname );
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getZone
//

uint8_t vscp_getZone(void)
{
    return eeprom_read( VSCP_EEPROM_END + REG_RELAY_ZONE );
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getSubzone
//

uint8_t vscp_getSubzone(void)
{
    return eeprom_read( VSCP_EEPROM_END + REG_RELAY_SUBZONE );
}

///////////////////////////////////////////////////////////////////////////////
// doWork
//
// The actual work is done here.
//

void doWork(void)
{
    if ( VSCP_STATE_ACTIVE == vscp_node_state ) {
		;
    }
}

///////////////////////////////////////////////////////////////////////////////
// vscp_readAppReg
//

uint8_t vscp_readAppReg(uint8_t reg)
{    
    uint8_t rv;

    rv = 0x00; // default read

    // Zone
    if ( reg == 0x00 ) {
        rv = eeprom_read(VSCP_EEPROM_END + REG_RELAY_ZONE);
	}
    // SubZone
	else if ( reg == 0x01 ) {
        rv = eeprom_read(VSCP_EEPROM_END + REG_RELAY_SUBZONE);
	}
    else if ( (reg >= REG_RELAY0_STATE) && (reg < REG_RELAY0_CONTROL) ) {

        switch ( reg ) {

            // Relay 0 Status
            case REG_RELAY0_STATE:
                rv = RELAY0;
                break;

            // Relay 1 Status
            case REG_RELAY1_STATE:
                rv = RELAY1;
                break;

            // Relay 2 Status
            case REG_RELAY2_STATE:
                rv = RELAY2;
                break;

            // Relay 3 Status
            case REG_RELAY3_STATE:
                rv = RELAY3;
                break;

            // Relay 4 Status
            case REG_RELAY4_STATE:
                rv = RELAY4;
                break;

            // Relay 5 Status
            case REG_RELAY5_STATE:
                rv = RELAY5;
                break;

            // Relay 6 Status
            case REG_RELAY6_STATE:
                rv = RELAY6;
                break;

            // Relay 7 Status
            case REG_RELAY7_STATE:
                rv = 0;
                break;
        }
    }
    
    // Read all other registers including DM
    else if ( ( reg >= REG_RELAY0_CONTROL ) &&
        (reg < (REG_DESCION_MATRIX + DESCION_MATRIX_ROWS * 8 ) ) ) {
        rv = eeprom_read( VSCP_EEPROM_END + reg );
    }

    return rv;

}

///////////////////////////////////////////////////////////////////////////////
// vscp_writeAppReg
//

uint8_t vscp_writeAppReg( uint8_t reg, uint8_t val )
{
    uint8_t rv;
    BOOL bInfoEvent = FALSE;
    BOOL bOn = FALSE;

    rv = ~val; // error return

	// Zone
    if ( reg == REG_RELAY_ZONE ) {
		eeprom_write(VSCP_EEPROM_END + REG_RELAY_ZONE, val);
        rv = eeprom_read(VSCP_EEPROM_END + REG_RELAY_ZONE);
	}
	else if ( reg == REG_RELAY_SUBZONE ) {
        // SubZone
        eeprom_write(VSCP_EEPROM_END + REG_RELAY_SUBZONE, val);
        rv = eeprom_read(VSCP_EEPROM_END + REG_RELAY_SUBZONE);
	}
    // Relay Status registers?
    else if ( (reg >= REG_RELAY0_STATE) && (reg <= REG_RELAY7_STATE) ) {

        if ( eeprom_read( VSCP_EEPROM_END +
                            REG_RELAY0_CONTROL + reg - 2 ) &
                            RELAY_CONTROLBIT_ENABLED ) {

            switch ( reg ) {

                // Relay 0 State
                case REG_RELAY0_STATE:
                    
                    bInfoEvent = TRUE;

                    if ( 1 == val ) {

                        RELAY0 = 1;
                        rv = RELAY0;
                        bOn = TRUE;

                        // If needed - Update protection timer
                        if ( eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL ) & RELAY_CONTROLBIT_PROTECTION ) {
                            relay_protection_timer[ 0 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB ) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB );
                        }

                    }
                    else if (0 == val) {
                        RELAY0 = 0;
                        rv = RELAY0;
                        bOn = FALSE;
                    }
                    break;

                // Relay 1 State
                case REG_RELAY1_STATE:

                    bInfoEvent = TRUE;

                    if (1 == val) {

                        RELAY1 = 1;
                        rv = RELAY1;
                        bOn = TRUE;

                        if (eeprom_read(VSCP_EEPROM_END + REG_RELAY1_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                            relay_protection_timer[ 1 ] =
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_MSB) * 256 +
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_LSB);
                        }

                    }
                    else if (0 == val) {
                        RELAY1 = 0;
                        rv = RELAY1;
                        bOn = FALSE;
                    }
                    break;

                // Relay 2 State
                case REG_RELAY2_STATE:

                    bInfoEvent = TRUE;

                    if (1 == val) {

                        RELAY2 = 1;
                        rv = RELAY2;
                        bOn = TRUE;

                        if ( eeprom_read(VSCP_EEPROM_END + REG_RELAY2_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                            relay_protection_timer[ 2 ] =
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_MSB) * 256 +
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_LSB);
                        }

                    }
                    else if (0 == val) {
                        RELAY2 = 0;
                        rv = RELAY2;
                        bOn = FALSE;

                    }
                    break;

                // Relay 3 State
                case REG_RELAY3_STATE:

                    bInfoEvent = TRUE;

                    if (1 == val) {

                        RELAY3 = 1;
                        rv = RELAY3;
                        bOn = TRUE;

                        if (eeprom_read(VSCP_EEPROM_END + REG_RELAY3_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                            relay_protection_timer[ 3 ] =
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_MSB) * 256 +
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_LSB);
                        }

                    }
                    else if (0 == val) {
                        RELAY3 = 0;
                        rv = RELAY3;
                        bOn = FALSE;

                    }
                    break;

                // Relay 4 State
                case REG_RELAY4_STATE:

                    bInfoEvent = TRUE;

                    if (1 == val) {

                        RELAY4 = 1;
                        rv = RELAY4;
                        bOn = TRUE;

                        if (eeprom_read(VSCP_EEPROM_END + REG_RELAY4_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                            relay_protection_timer[ 4 ] =
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_MSB) * 256 +
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_LSB);
                        }

                    }
                    else if (0 == val) {
                        RELAY4 = 0;
                        rv = RELAY4;
                        bOn = FALSE;

                    }
                    break;

                // Relay 5 State
                case REG_RELAY5_STATE:

                    bInfoEvent = TRUE;

                    if (1 == val) {

                        RELAY5 = 1;
                        rv = RELAY5;
                        bOn = TRUE;

                        if (eeprom_read(VSCP_EEPROM_END + REG_RELAY5_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                            relay_protection_timer[ 5 ] =
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_MSB) * 256 +
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_LSB);
                        }

                    }
                    else if (0 == val) {
                        RELAY5 = 0;
                        rv = RELAY5;
                        bOn = FALSE;
                    }
                    break;

                // Relay 6 State
                case REG_RELAY6_STATE:

                    bInfoEvent = TRUE;

                    if (1 == val) {
                        
                        RELAY6 = 1;
                        rv = RELAY6;
                        bOn = TRUE;

                        if (eeprom_read(VSCP_EEPROM_END + REG_RELAY6_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                            relay_protection_timer[ 6 ] =
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_MSB) * 256 +
                                    eeprom_read(VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_LSB);
                        }

                    }
                    else if (0 == val) {
                        RELAY6 = 0;
                        rv = RELAY6;
                        bOn = FALSE;
                    }
                    break;

            }
        }
    }

    // Control registers
    else if ( (reg >= REG_RELAY0_CONTROL ) &&
                (reg <= REG_RELAY7_CONTROL) ) {

        switch( reg ) {

            case REG_RELAY0_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {

                    RELAY0 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x01; // Enable pulse output
                    relay_pulse_timer[ 0 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB ) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB );
                }
                else {
                    relay_pulse_flags &= 0b11111110; // Disable pulse output
                    RELAY0 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 0 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB );
                }
                break;

            case REG_RELAY1_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {

                    RELAY1 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x02; // Enable pulse output
                    relay_pulse_timer[ 1 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB);
                }
                else {
                    relay_pulse_flags &= 0b11111101; // Disable pulse output
                    RELAY1 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 1 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB );
                }
                break;

            case REG_RELAY2_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {

                    RELAY2 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x04; // Enable pulse output
                    relay_pulse_timer[ 2 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_MSB) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_LSB);
                }
                else {
                    relay_pulse_flags &= 0b11111011; // Disable pulse output
                    RELAY2 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 2 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_LSB );
                }
                break;

            case REG_RELAY3_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {

                    RELAY3 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x08; // Enable pulse output
                    relay_pulse_timer[ 3 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_MSB) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_LSB);
                }
                else {
                    relay_pulse_flags &= 0b11110111; // Disable pulse output
                    RELAY3 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 3 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_LSB );
                }
                break;

            case REG_RELAY4_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {

                    RELAY4 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x10; // Enable pulse output
                    relay_pulse_timer[ 4 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_MSB) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_LSB);
                }
                else {
                    relay_pulse_flags &= 0b11101111; // Disable pulse output
                    RELAY4 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 4 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_LSB );
                }
                break;

            case REG_RELAY5_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {

                    RELAY5 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x20; // Enable pulse output
                    relay_pulse_timer[ 5 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_MSB) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_LSB);
                }
                else {
                    relay_pulse_flags &= 0b11011111; // Disable pulse output
                    RELAY5 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 5 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_LSB );
                }
                break;

            case REG_RELAY6_CONTROL:

                eeprom_write( VSCP_EEPROM_END + reg, val );
                rv = eeprom_read( VSCP_EEPROM_END + reg );

                if ( val & RELAY_CONTROLBIT_PULSE ) {
                    
                    RELAY6 = 0; // Start out at a known state
                    bOn = FALSE;

                    relay_pulse_flags |= 0x40; // Enable pulse output
                    relay_pulse_timer[ 6 ] =
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_MSB) * 256 +
                                    eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_LSB);
                }
                else {
                    relay_pulse_flags &= 0b10111111; // Disable pulse output
                    RELAY3 = 0; // End with off
                    bOn = FALSE;
                }

                if ( val & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 6 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_LSB );
                }
                break;

        }

    }
    // Pulse time registers
    else if ( (reg >= REG_RELAY0_PULSE_TIME_MSB ) &&
                    (reg <= REG_RELAY7_PULSE_TIME_LSB ) ) {

        // Write to EEPROM
        eeprom_write( VSCP_EEPROM_END + reg, val );
        rv = eeprom_read( VSCP_EEPROM_END + reg );

        // We let the defaault take care of the MSB's
        // and give some special treatment to the LSB's
        switch ( reg ) {

            case REG_RELAY0_PULSE_TIME_LSB:
                relay_pulse_timer[ 0 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB);
                break;

            case REG_RELAY1_PULSE_TIME_LSB:
                relay_pulse_timer[ 1 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PULSE_TIME_LSB);
                break;

            case REG_RELAY2_PULSE_TIME_LSB:
                relay_pulse_timer[ 2 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_LSB);
                break;

            case REG_RELAY3_PULSE_TIME_LSB:
                relay_pulse_timer[ 3 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_LSB);
                break;

            case REG_RELAY4_PULSE_TIME_LSB:
                relay_pulse_timer[ 4 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_LSB);
                break;

            case REG_RELAY5_PULSE_TIME_LSB:
                relay_pulse_timer[ 5 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_LSB);
                break;

            case REG_RELAY6_PULSE_TIME_LSB:
                relay_pulse_timer[ 6 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_LSB);
                break;

            case REG_RELAY7_PULSE_TIME_LSB:
                relay_pulse_timer[ 7 ] =
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY7_PULSE_TIME_MSB) * 256 +
                    eeprom_read( VSCP_EEPROM_END + REG_RELAY7_PULSE_TIME_LSB);
                break;

            default:
                break;
        }

    }
    // Relay protection time registers
    else if ( ( reg >= REG_RELAY0_PROTECTION_TIME_MSB ) &&
                ( reg <= REG_RELAY7_PROTECTION_TIME_LSB ) ) {

        // Write to EEPROM
        eeprom_write( VSCP_EEPROM_END + reg, val );
        rv = eeprom_read( VSCP_EEPROM_END + reg );
        
        switch ( reg ) {

            case REG_RELAY0_PROTECTION_TIME_LSB:
                relay_protection_timer[ 0 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY1_PROTECTION_TIME_LSB:
                relay_protection_timer[ 1 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY2_PROTECTION_TIME_LSB:
                relay_protection_timer[ 2 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY3_PROTECTION_TIME_LSB:
                relay_protection_timer[ 3 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY4_PROTECTION_TIME_LSB:
                relay_protection_timer[ 4 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY5_PROTECTION_TIME_LSB:
                relay_protection_timer[ 5 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY6_PROTECTION_TIME_LSB:
                relay_protection_timer[ 6 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_LSB );
                break;

            case REG_RELAY7_PROTECTION_TIME_LSB:
                relay_protection_timer[ 7 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY7_PROTECTION_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY7_PROTECTION_TIME_LSB );
                break;

            default:
                break;
        }

    }
    // Relay Zone/Subzone registers
    else if ( (reg >= REG_RELAY0_ZONE ) && (reg <= REG_RELAY7_SUBZONE) ) {

        // Write to EEPROM
        eeprom_write( VSCP_EEPROM_END + reg, val );
        rv = eeprom_read( VSCP_EEPROM_END + reg );

    }
    else if ( (reg >= REG_DESCION_MATRIX) &&
            (reg < (REG_DESCION_MATRIX + DESCION_MATRIX_ROWS * 8)) ) {
        eeprom_write( VSCP_EEPROM_END + reg, val );
        calculateSetFilterMask();  // Calculate new hardware filter
        rv = eeprom_read( VSCP_EEPROM_END + reg );
    }

    // --------------------------------------------------------------------------

    // Send information Event
    // if enabled in the registers
    if ( bInfoEvent ) {

        unsigned char val;
        val = eeprom_read( VSCP_EEPROM_END + 
                            REG_RELAY0_CONTROL + (reg - REG_RELAY0_STATE) );

        if ( bOn ) {

            if ( val & RELAY_CONTROLBIT_ONEVENT ) {
                SendInformationEvent( reg - REG_RELAY0_STATE,
                                        VSCP_CLASS1_INFORMATION,
                                        VSCP_TYPE_INFORMATION_ON );
            }

            if ( val & RELAY_CONTROLBIT_STARTEVENT ) {
                SendInformationEvent( reg - REG_RELAY0_STATE,
                                        VSCP_CLASS1_INFORMATION,
                                        VSCP_TYPE_INFORMATION_START );
            }

        }
        else {

            if ( val & RELAY_CONTROLBIT_OFFEVENT ) {
                SendInformationEvent( reg - REG_RELAY0_STATE,
                                        VSCP_CLASS1_INFORMATION,
                                        VSCP_TYPE_INFORMATION_OFF );
            }

            if ( val & RELAY_CONTROLBIT_STOPEVENT ) {
                SendInformationEvent( reg - REG_RELAY0_STATE,
                                        VSCP_CLASS1_INFORMATION,
                                        VSCP_TYPE_INFORMATION_STOP );
            }
        }
    }

    return rv;

}

///////////////////////////////////////////////////////////////////////////////
// Send Decsion Matrix Information
//

void sendDMatrixInfo(void)
{

    vscp_omsg.priority = VSCP_PRIORITY_MEDIUM;
    vscp_omsg.flags = VSCP_VALID_MSG + 2;
    vscp_omsg.vscp_class = VSCP_CLASS1_PROTOCOL;
    vscp_omsg.vscp_type = VSCP_TYPE_PROTOCOL_GET_MATRIX_INFO_RESPONSE;

    vscp_omsg.data[ 0 ] = DESCION_MATRIX_ROWS;
    vscp_omsg.data[ 1 ] = REG_DESCION_MATRIX;

    vscp_sendEvent(); // Send data
}


///////////////////////////////////////////////////////////////////////////////
// SendInformationEvent
//

void SendInformationEvent( unsigned char idx,
                            unsigned char eventClass,
                            unsigned char eventTypeId )
{
    uint8_t data[3];
/*
    vscp_omsg.priority = VSCP_PRIORITY_MEDIUM;
    vscp_omsg.flags = VSCP_VALID_MSG + 3;
    vscp_omsg.vscp_class = eventClass;
    vscp_omsg.vscp_type = eventTypeId;

    vscp_omsg.data[ 0 ] = idx; // Register
    vscp_omsg.data[ 1 ] = eeprom_read( VSCP_EEPROM_END + REG_RELAY_SUBZONE);
    vscp_omsg.data[ 2 ] = eeprom_read( VSCP_EEPROM_END + REG_RELAY1_SUBZONE + idx );

    vscp_sendEvent(); // Send data
*/
    data[ 0 ] = idx; // Register
    data[ 1 ] = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_ZONE + 2*idx );
    data[ 2 ] = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_SUBZONE + 2*idx );
    sendVSCPFrame( eventClass,
                    eventTypeId,
                    vscp_nickname,
                    VSCP_PRIORITY_MEDIUM,
                    3,
                    data );
}

///////////////////////////////////////////////////////////////////////////////
// Do decision Matrix handling
// 
// The routine expects vscp_imsg to contain a vaild incoming event
//

void doDM(void)
{
    unsigned char i;
    unsigned char dmflags;
    unsigned short class_filter;
    unsigned short class_mask;
    unsigned char type_filter;
    unsigned char type_mask;

    // Don't deal with the protocol functionality
    if ( VSCP_CLASS1_PROTOCOL == vscp_imsg.vscp_class ) return;

    for (i = 0; i < DESCION_MATRIX_ROWS; i++) {

        // Get DM flags for this row
        dmflags = eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + 1 + (8 * i) );

        // Is the DM row enabled?
        if ( dmflags & VSCP_DM_FLAG_ENABLED ) {

            // Should the originating id be checked and if so is it the same?
            if ( ( dmflags & VSCP_DM_FLAG_CHECK_OADDR ) &&
                    ( vscp_imsg.oaddr != eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) ) ) ) {
                continue;
            }

            /*  
            
              No need for this as each relay has it's own zone/subzone register
            
            // Check if zone should match and if so if it match
            if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
                if ( 255 != vscp_imsg.data[ 1 ] ) {
                    if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END + REG_RELAY_ZONE ) ) {
                        continue;
                    }
                }
            }

            // Check if subzone should match and if so if it match
            if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
                if ( 255 != vscp_imsg.data[ 2 ] ) {
                    if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END + REG_RELAY_SUBZONE ) ) {
                        continue;
                    }
                }
            }*/
            
            class_filter = ( dmflags & VSCP_DM_FLAG_CLASS_FILTER)*256 +
                    eeprom_read( VSCP_EEPROM_END +
                    REG_DESCION_MATRIX +
                    (8 * i) +
                    VSCP_DM_POS_CLASSFILTER);
            class_mask = ( dmflags & VSCP_DM_FLAG_CLASS_MASK)*256 +
                    eeprom_read( VSCP_EEPROM_END +
                    REG_DESCION_MATRIX +
                    (8 * i) +
                    VSCP_DM_POS_CLASSMASK);
            type_filter = eeprom_read( VSCP_EEPROM_END +
                    REG_DESCION_MATRIX +
                    (8 * i) +
                    VSCP_DM_POS_TYPEFILTER);
            type_mask = eeprom_read( VSCP_EEPROM_END +
                    REG_DESCION_MATRIX +
                    (8 * i) +
                    VSCP_DM_POS_TYPEMASK);

            if ( !( ( class_filter ^ vscp_imsg.vscp_class ) & class_mask ) &&
                    !( ( type_filter ^ vscp_imsg.vscp_type ) & type_mask ) ) {

                // OK Trigger this action
                switch ( eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTION ) ) {

                    case ACTION_ON: // Enable relays in arg. bitarry
                        doActionOn( dmflags, eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTIONPARAM ) );
                        break;

                    case ACTION_OFF: // Disable relays in arg. bitarry
                        doActionOff( dmflags, eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTIONPARAM ) );
                        break;

                    case ACTION_PULSE: // Pulse relays in arg. bitarry, zone, subzone
                        doActionPulse( dmflags, eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTIONPARAM ) );
                        break;

                    case ACTION_STATUS: // Send status for all relays
                        doActionStatus( dmflags, eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTIONPARAM ) );
                        break;

                    case ACTION_DISABLE: // Disable realys in bitarray
                        doActionDisable( dmflags, eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTIONPARAM ) );
                        break;

                    case ACTION_TOGGLE: // Toggle relay(s)
                        doActionToggle( dmflags, eeprom_read( VSCP_EEPROM_END + REG_DESCION_MATRIX + (8 * i) + VSCP_DM_POS_ACTIONPARAM ) );
                        break;

                } // case
            } // Filter/mask
        } // Row enabled
    } // for each row
}

///////////////////////////////////////////////////////////////////////////////
// doActionOn
// 

void doActionOn(unsigned char dmflags, unsigned char arg)
{

    unsigned char i;
    unsigned char val;

    for (i = 0; i < 8; i++) {

        // If the rely should not be handled just move on
        if ( !( arg & ( 1 << i ) ) ) continue;

        // Check if zone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
            if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_ZONE + i ) ) {
                continue;
            }
        }
        
        // Check if subzone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
            if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_SUBZONE + i ) ) {
                continue;
            }
        }

        val = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i );

        // Do nothing if disabled
        if ( !( val & RELAY_CONTROLBIT_ENABLED ) ) continue;

        switch ( i ) {

            case 0:
                RELAY0 = 1;

                if (eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL ) & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 0 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PROTECTION_TIME_LSB );
                }
                break;

            case 1:
                RELAY1 = 1;

                if (eeprom_read( VSCP_EEPROM_END + REG_RELAY1_CONTROL) & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 1 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PROTECTION_TIME_LSB );
                }
                break;

            case 2:
                RELAY2 = 1;

                if (eeprom_read( VSCP_EEPROM_END + REG_RELAY2_CONTROL) & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 2 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PROTECTION_TIME_LSB );
                }
                break;

            case 3:
                RELAY3 = 1;

                if ( eeprom_read( VSCP_EEPROM_END + REG_RELAY3_CONTROL) & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 3 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PROTECTION_TIME_LSB );
                }
                break;

            case 4:
                RELAY4 = 1;

                if (eeprom_read( VSCP_EEPROM_END + REG_RELAY4_CONTROL) & RELAY_CONTROLBIT_PROTECTION ) {
                    relay_protection_timer[ 4 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PROTECTION_TIME_LSB );
                }
                break;

            case 5:
                RELAY5 = 1;

                if (eeprom_read( VSCP_EEPROM_END + REG_RELAY5_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                    relay_protection_timer[ 5 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PROTECTION_TIME_LSB );
                }
                break;

            case 6:
                RELAY6 = 1;

                if ( eeprom_read( VSCP_EEPROM_END + REG_RELAY6_CONTROL) & RELAY_CONTROLBIT_PROTECTION) {
                    relay_protection_timer[ 6 ] =
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_MSB ) * 256 +
                            eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PROTECTION_TIME_LSB );
                }
                break;

        }

        // Should off event be sent?
        if ( val & RELAY_CONTROLBIT_ONEVENT ) {
            SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_ON );
        }

        // Should stop event be sent?
        if ( val & RELAY_CONTROLBIT_STARTEVENT ) {
            SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_START );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// doActionOff
// 

void doActionOff( unsigned char dmflags, unsigned char arg )
{

    unsigned char i;
    unsigned char val;

    for ( i = 0; i < 8; i++ ) {

        // If the rely should not be handled just move on
        if ( !( arg & ( 1 << i ) ) ) continue;

        // Check if zone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
            if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_ZONE + i ) ) {
                continue;
            }
        }
        
        // Check if subzone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
            if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_SUBZONE + i ) ) {
                continue;
            }
        }

        val = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i );

        // Do nothing if disabled
        if ( !( val & RELAY_CONTROLBIT_ENABLED ) ) continue;

        switch ( i ) {

            case 0:
                RELAY0 = 0;
                break;

            case 1:
                RELAY1 = 0;
                break;

            case 2:
                RELAY2 = 0;
                break;

            case 3:
                RELAY3 = 0;
                break;

            case 4:
                RELAY4 = 0;
                break;

            case 5:
                RELAY5 = 0;
                break;

            case 6:
                RELAY6 = 0;
                break;

        }

        // Should off event be sent?
        if ( val & RELAY_CONTROLBIT_OFFEVENT ) {
            SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_OFF );
        }

        // Should stop event be sent?
        if ( val & RELAY_CONTROLBIT_STOPEVENT ) {
            SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_STOP );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// doActionPulse
// 

void doActionPulse(unsigned char dmflags, unsigned char arg)
{

    unsigned char i;
    unsigned char val;

    for ( i = 0; i < 8; i++ ) {

        // If the rely should not be handled just move on
        if ( !( arg & ( 1 << i ) ) ) continue;

        // Check if zone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
            if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_ZONE + i ) ) {
                continue;
            }
        }
        
        // Check if subzone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
            if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_SUBZONE + i ) ) {
                continue;
            }
        }

        val = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i );

        // Do nothing if disabled
        if ( !( val & RELAY_CONTROLBIT_ENABLED ) ) continue;

        switch (i) {

            case 0:
                RELAY0 = 0; // Start out at a known state
                relay_pulse_flags |= 0x01; // Enable pulse output
                relay_pulse_timer[ 0 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY0_PULSE_TIME_LSB );
                break;

            case 1:
                RELAY1 = 0; // Start out at a known state
                relay_pulse_flags |= 0x02; // Enable pulse output
                relay_pulse_timer[ 1 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY1_PULSE_TIME_LSB );
                break;

            case 2:
                RELAY2 = 0; // Start out at a known state
                relay_pulse_flags |= 0x04; // Enable pulse output
                relay_pulse_timer[ 2 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY2_PULSE_TIME_LSB );
                break;

            case 3:
                RELAY3 = 0; // Start out at a known state
                relay_pulse_flags |= 0x08; // Enable pulse output
                relay_pulse_timer[ 3 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY3_PULSE_TIME_LSB );
                break;

            case 4:
                RELAY4 = 0; // Start out at a known state
                relay_pulse_flags |= 0x10; // Enable pulse output
                relay_pulse_timer[ 4 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY4_PULSE_TIME_LSB );
                break;

            case 5:
                RELAY5 = 0; // Start out at a known state
                relay_pulse_flags |= 0x20; // Enable pulse output
                relay_pulse_timer[ 5 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY5_PULSE_TIME_LSB );
                break;

            case 6:
                RELAY6 = 0; // Start out at a known state
                relay_pulse_flags |= 0x40; // Enable pulse output
                relay_pulse_timer[ 6 ] =
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_MSB ) * 256 +
                        eeprom_read( VSCP_EEPROM_END + REG_RELAY6_PULSE_TIME_LSB );
                break;

        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// doActionStatus
// 

void doActionStatus(unsigned char dmflags, unsigned char arg)
{

    unsigned char i;
    unsigned char val;
    BOOL bOn = FALSE;

    for (i = 0; i < 8; i++) {

        // If the rely should not be handled just move on
        if (!(arg & (1 << i))) continue;

        // Check if zone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
            if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_ZONE + i ) ) {
                continue;
            }
        }
        
        // Check if subzone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
            if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_SUBZONE + i ) ) {
                continue;
            }
        }

        val = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i );

        switch (i) {

            case 0:
                bOn = RELAY0;
                break;

            case 1:
                bOn = RELAY1;
                break;

            case 2:
                bOn = RELAY2;
                break;

            case 3:
                bOn = RELAY3;
                break;

            case 4:
                bOn = RELAY4;
                break;

            case 5:
                bOn = RELAY5;
                break;

            case 6:
                bOn = RELAY6;
                break;

        }

        if (bOn) {

            // Should off event be sent?
            if ( val & RELAY_CONTROLBIT_OFFEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_OFF );
            }

            // Should stop event be sent?
            if ( val & RELAY_CONTROLBIT_STOPEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_STOP );
            }

        }
        else {

            // Should off event be sent?
            if ( val & RELAY_CONTROLBIT_OFFEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_OFF );
            }

            // Should stop event be sent?
            if ( val & RELAY_CONTROLBIT_STOPEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_STOP );
            }

        }

    }
}

///////////////////////////////////////////////////////////////////////////////
// doActionDisable
// 

void doActionDisable(unsigned char dmflags, unsigned char arg)
{

    unsigned char i;
    unsigned char val;

    for ( i = 0; i < 8; i++ ) {

        // If the rely should not be handled just move on
        if ( !( arg & (1 << i) ) ) continue;

        // Check if zone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
            if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_ZONE + i ) ) {
                continue;
            }
        }
        
        // Check if subzone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
            if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_SUBZONE + i ) ) {
                continue;
            }
        }

        val = eeprom_read( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i );
        eeprom_write( VSCP_EEPROM_END + REG_RELAY0_CONTROL + i, val & ~RELAY_CONTROLBIT_ENABLED );
    }

}

///////////////////////////////////////////////////////////////////////////////
// doActionToggle
// 

void doActionToggle( unsigned char dmflags, unsigned char arg )
{

    unsigned char i;
    unsigned char val;
    BOOL bOn = FALSE;

    for ( i = 0; i < 8; i++ ) {

        // If the relay should not be handled just move on
        if ( !( arg & (1 << i) ) ) continue;

        // Check if zone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_ZONE ) {
            if ( vscp_imsg.data[ 1 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_ZONE + i ) ) {
                continue;
            }
        }
        
        // Check if subzone should match and if so check if it match
        if ( dmflags & VSCP_DM_FLAG_CHECK_SUBZONE ) {
            if ( vscp_imsg.data[ 2 ] != eeprom_read( VSCP_EEPROM_END +
                    REG_RELAY1_SUBZONE + i ) ) {
                continue;
            }
        }

        val = eeprom_read(VSCP_EEPROM_END + REG_RELAY0_CONTROL + i);

        switch ( i ) {

            case 0:
                if ( RELAY0 ) {
                    RELAY0 = 0;
                    bOn = FALSE;
                } else {
                    RELAY0 = 1;
                    bOn = TRUE;
                }
                break;

            case 1:
                if ( RELAY1 ) {
                    RELAY1 = 0;
                    bOn = FALSE;
                } else {
                    RELAY1 = 1;
                    bOn = TRUE;
                }
                break;

            case 2:
                if ( RELAY2 ) {
                    RELAY2 = 0;
                    bOn = FALSE;
                } else {
                    RELAY2 = 1;
                    bOn = TRUE;
                }
                break;

            case 3:
                if ( RELAY3 ) {
                    RELAY3 = 0;
                    bOn = FALSE;
                } else {
                    RELAY3 = 1;
                    bOn = TRUE;
                }
                break;

            case 4:
                if ( RELAY4 ) {
                    RELAY4 = 0;
                    bOn = FALSE;
                } else {
                    RELAY4 = 1;
                    bOn = TRUE;
                }
                break;

            case 5:
                if ( RELAY5 ) {
                    RELAY5 = 0;
                    bOn = FALSE;
                } else {
                    RELAY5 = 1;
                    bOn = TRUE;
                }
                break;

            case 6:
                if ( RELAY6 ) {
                    RELAY6 = 0;
                    bOn = FALSE;
                } else {
                    RELAY6 = 1;
                    bOn = TRUE;
                }
                break;

        }

        if ( bOn ) {

            // Should on event be sent?
            if ( val & RELAY_CONTROLBIT_ONEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_ON );
            }

            // Should start event be sent?
            if ( val & RELAY_CONTROLBIT_STARTEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_START );
            }

        }
        else {

            // Should off event be sent?
            if ( val & RELAY_CONTROLBIT_OFFEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_OFF );
            }

            // Should stop event be sent?
            if (val & RELAY_CONTROLBIT_STOPEVENT ) {
                SendInformationEvent( i, VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_STOP );
            }

        }

    }
}



///////////////////////////////////////////////////////////////////////////////
//                        VSCP Required Methods
//////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Get Major version number for this hardware module
//

unsigned char vscp_getMajorVersion()
{
    return FIRMWARE_MAJOR_VERSION;
}

///////////////////////////////////////////////////////////////////////////////
// Get Minor version number for this hardware module
//

unsigned char vscp_getMinorVersion()
{
    return FIRMWARE_MINOR_VERSION;
}

///////////////////////////////////////////////////////////////////////////////
// Get Subminor version number for this hardware module
//

unsigned char vscp_getSubMinorVersion()
{
    return FIRMWARE_SUB_MINOR_VERSION;
}

///////////////////////////////////////////////////////////////////////////////
// getVSCP_GUID
//
// Get GUID from EEPROM
//

uint8_t vscp_getGUID(uint8_t idx)
{
    return eeprom_read( VSCP_EEPROM_REG_GUID + idx );
}


///////////////////////////////////////////////////////////////////////////////
// getDeviceURL
//
// Get device URL from EEPROM
//

uint8_t vscp_getMDF_URL(uint8_t idx)
{
    return vscp_deviceURL[ idx ];
}

///////////////////////////////////////////////////////////////////////////////
// Get Manufacturer id and subid from EEPROM
//

uint8_t vscp_getUserID(uint8_t idx)
{
    return eeprom_read( VSCP_EEPROM_REG_USERID + idx );
}

///////////////////////////////////////////////////////////////////////////////
//  setVSCPUserID
//

void vscp_setUserID(uint8_t idx, uint8_t data)
{
    eeprom_write( idx + VSCP_EEPROM_REG_USERID, data );
}

///////////////////////////////////////////////////////////////////////////////
// getVSCPManufacturerId
// 
// Get Manufacturer id and subid from EEPROM
//

uint8_t vscp_getManufacturerId(uint8_t idx)
{
    return eeprom_read( VSCP_EEPROM_REG_MANUFACTUR_ID0 + idx );
}

///////////////////////////////////////////////////////////////////////////////
// Get the bootloader algorithm code
//

uint8_t vscp_getBootLoaderAlgorithm(void)
{
    return VSCP_BOOTLOADER_PIC1;
}

///////////////////////////////////////////////////////////////////////////////
// Get the buffer size
//

uint8_t vscp_getBufferSize(void)
{
    return 8; // Standard CAN frame
}


///////////////////////////////////////////////////////////////////////////////
//  getNickname
//

uint8_t vscp_getNickname(void)
{
    return eeprom_read(VSCP_EEPROM_NICKNAME);
}

///////////////////////////////////////////////////////////////////////////////
//  setNickname
//

void vscp_setNickname(uint8_t nickname)
{
    eeprom_write(VSCP_EEPROM_NICKNAME, nickname);
}

///////////////////////////////////////////////////////////////////////////////
//  getSegmentCRC
//

uint8_t vscp_getSegmentCRC(void)
{
    return eeprom_read( VSCP_EEPROM_SEGMENT_CRC );
}

///////////////////////////////////////////////////////////////////////////////
//  setSegmentCRC
//

void vscp_setSegmentCRC(uint8_t crc)
{
    eeprom_write( VSCP_EEPROM_SEGMENT_CRC, crc );
}

///////////////////////////////////////////////////////////////////////////////
//  setVSCPControlByte
//

void vscp_setControlByte(uint8_t ctrl)
{
    eeprom_write(VSCP_EEPROM_CONTROL, ctrl);
}


///////////////////////////////////////////////////////////////////////////////
//  getVSCPControlByte
//

uint8_t vscp_getControlByte(void)
{
    return eeprom_read(VSCP_EEPROM_CONTROL);
}

///////////////////////////////////////////////////////////////////////////////
//  vscp_getEmbeddedMdfInfo
//

void vscp_getEmbeddedMdfInfo(void)
{
    // No embedded DM so we respond with info about that

    vscp_omsg.priority = VSCP_PRIORITY_NORMAL;
    vscp_omsg.flags = VSCP_VALID_MSG + 3;
    vscp_omsg.vscp_class = VSCP_CLASS1_PROTOCOL;
    vscp_omsg.vscp_type = VSCP_TYPE_PROTOCOL_RW_RESPONSE;

    vscp_omsg.data[ 0 ] = 0;
    vscp_omsg.data[ 1 ] = 0;
    vscp_omsg.data[ 2 ] = 0;

    // send the event
    vscp_sendEvent();
}

/*
///////////////////////////////////////////////////////////////////////////////
// vscp_getZone
//

uint8_t vscp_getZone( void )
{
        return eeprom_read( VSCP_EEPROM_END + EEPROM_ZONE );
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getSubzone
//

uint8_t vscp_getSubzone( void )
{
        return eeprom_read( VSCP_EEPROM_END + EEPROM_SUBZONE );
}
 */

///////////////////////////////////////////////////////////////////////////////
// vscp_goBootloaderMode
//

void vscp_goBootloaderMode( uint8_t algorithm )
{
    if ( VSCP_BOOTLOADER_PIC1 != algorithm  ) return;

    // OK, We should enter boot loader mode
    // 	First, activate bootloader mode
    eeprom_write(VSCP_EEPROM_BOOTLOADER_FLAG, VSCP_BOOT_FLAG);

    // Reset processor
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
//  vscp_getMatrixInfo
//

void vscp_getMatrixInfo(char *pData)
{
    uint8_t i;

    vscp_omsg.data[ 0 ] = 7; // Matrix is seven rows
    vscp_omsg.data[ 1 ] = 72; // Matrix start offset

    // The rest set to zero no paging
    for ( i = 2; i < 8; i++ ) {
        vscp_omsg.data[ i ] = 0;
    }

}

///////////////////////////////////////////////////////////////////////////////
// vscp_getFamilyCode
//

uint32_t vscp_getFamilyCode() {
    return 0L;
}


///////////////////////////////////////////////////////////////////////////////
// vscp_getFamilyType
//

uint32_t vscp_getFamilyType() {
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// vscp_restoreDefaults
//

void vscp_restoreDefaults() {
    init_app_eeprom();
    init_app_ram();
}


///////////////////////////////////////////////////////////////////////////////
// vscp_getRegisterPagesUsed
//

uint8_t vscp_getRegisterPagesUsed( void )
{
    return 1; // One pae used
}

///////////////////////////////////////////////////////////////////////////////
// sendVSCPFrame
//

int8_t sendVSCPFrame( uint16_t vscpclass,
                        uint8_t vscptype,
                        uint8_t nodeid,
                        uint8_t priority,
                        uint8_t size,
                        uint8_t *pData )
{
    uint32_t id = ( (uint32_t)priority << 26 ) |
                    ( (uint32_t)vscpclass << 16 ) |
                    ( (uint32_t)vscptype << 8 ) |
                    nodeid; // node address (our address)

    if ( !sendCANFrame( id, size, pData ) ) {
        return FALSE;
    }

    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// getVSCPFrame
//

int8_t getVSCPFrame(uint16_t *pvscpclass,
                        uint8_t *pvscptype,
                        uint8_t *pNodeId,
                        uint8_t *pPriority,
                        uint8_t *pSize,
                        uint8_t *pData)
{
    uint32_t id;

    if ( !getCANFrame(&id, pSize, pData) ) {
        return FALSE;
    }

    *pNodeId = id & 0x0ff;
    *pvscptype = (id >> 8) & 0xff;
    *pvscpclass = (id >> 16) & 0x1ff;
    *pPriority = (uint16_t) (0x07 & (id >> 26));

    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// sendCANFrame
//

int8_t sendCANFrame(uint32_t id, uint8_t dlc, uint8_t *pdata)
{
    uint8_t rv = FALSE;
    sendTimer = 0;

    while ( sendTimer < 1000 ) {
        if ( ECANSendMessage( id, pdata, dlc, ECAN_TX_XTD_FRAME ) ) {
            rv = TRUE;
            break;
        }
    }

    vscp_omsg.flags = 0;

    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// getCANFrame
//

int8_t getCANFrame(uint32_t *pid, uint8_t *pdlc, uint8_t *pdata)
{
    ECAN_RX_MSG_FLAGS flags;

    // Don't read in new event if there already is a event
    // in the input buffer
    if (vscp_imsg.flags & VSCP_VALID_MSG) return FALSE;

    if ( ECANReceiveMessage( pid, pdata, pdlc, &flags) ) {

        // RTR not interesting
        if (flags & ECAN_RX_RTR_FRAME) return FALSE;

        // Must be extended frame
        if (!(flags & ECAN_RX_XTD_FRAME)) return FALSE;

        return TRUE;

    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// calculateSetFilterMask
//
// Calculate and set required filter and mask
// for the current decision matrix
//

void calculateSetFilterMask( void )
{
    uint8_t i,j;
    uint8_t lastOID;
    uint32_t rowmask;
    uint32_t rowfilter;

    // Reset filter masks
    uint32_t mask = 0xffffffff; // Just id 0x00000000 will come true
    uint32_t filter = 0;

    // Go through all DM rows
    for ( i=0; i < DESCION_MATRIX_ROWS; i++ ) {

        // No need to check not active DM rows
        if ( eeprom_read( VSCP_EEPROM_END + 8*i + 1 ) & 0x80 ) {

            // build the mask
            // ==============
            // We receive
            //  - all priorities
            //  - hardcoded and not hardcoded
            //  - from all nodes

            rowmask =
                    // Bit 9 of class mask
                    ( (uint32_t)( eeprom_read( VSCP_EEPROM_END + 8*i + 1 ) & 2 ) << 23 ) |
                    // Rest of class mask
                    ( (uint32_t)eeprom_read( VSCP_EEPROM_END + 8*i + 2 ) << 16 ) |
                    // Type mask
                    ( (uint32_t)eeprom_read( VSCP_EEPROM_END + 8*i + 4 ) << 8 ) |
					// OID  - handle later
					0xff;
                    /*( ( eeprom_read( VSCP_EEPROM_END + 8*i + 1 ) & 0x20 ) << 20 )*/;   // Hardcoded bit

            // build the filter
            // ================

            rowfilter =
                    // Bit 9 of class filter
                    ( (uint32_t)( eeprom_read( VSCP_EEPROM_END + 8*i + 1 ) & 1 ) << 24 ) |
                    // Rest of class filter
                    ( (uint32_t)eeprom_read( VSCP_EEPROM_END + 8*i + 3 ) << 16 ) |
                    // Type filter
                    ( (uint32_t)eeprom_read( VSCP_EEPROM_END + 8*i + 5 ) << 8 ) |
                    // OID Mask cleard if not same OID for all or one or more
                    // rows don't have OID check flag set.
                    eeprom_read( VSCP_EEPROM_END + 8*i );

            if ( 0 == i ) filter = rowfilter;   // Hack for first iteration loop

            // Form the mask - if one mask have a don't care (0)
            // the final mask should also have a don't care on that position
            mask &= rowmask;

            // Check the calculated filter and the current
            // filter to see if the bits are the same. If they
            // are not then clear the mask at that position
            for ( j=0; j<32; j++ ) {
                // If two bits are different we clear the mask bit
                if ( ( ( filter >> j ) & 1 ) != ( ( rowfilter >> j ) & 1 ) ) {
                    mask &= ~(1<<j);
                }
            }

            // Form the filter
            // if two bits are not the same they will be zero
            // All zeros will be zero
            // All ones will be one
            filter &= rowfilter;

            // Not check OID?
            if ( !eeprom_read( VSCP_EEPROM_END + 8*i + 1 ) & 0x40 ) {
                // No should not be checked for this position
                // This mean that we can't filter on a specific OID
                // so mask must be a don't care
                mask &= ~0xff;
            }

            if (i) {
                // If the current OID is different than the previous
                // we accept all
                for (j = 0; j < 8; j++) {
                    if ((lastOID >> i & 1)
                            != (eeprom_read(VSCP_EEPROM_END + 8 * i) >> i & 1)) {
                        mask &= (1 << i);
                    }
                }

                lastOID = eeprom_read(VSCP_EEPROM_END + 8 * i);

            } 
            else {
                // First round we just store the OID
                lastOID = eeprom_read(VSCP_EEPROM_END + 8 * i);
            }

        }
    }
    
    // Must be in Config mode to change settings.
    ECANSetOperationMode( ECAN_OP_MODE_CONFIG );

    //Set mask 1
    ECANSetRXM1Value( mask, ECAN_MSG_XTD );

    // Set filter 1
    ECANSetRXF1Value( filter, ECAN_MSG_XTD );

    // Return to Normal mode to communicate.
    ECANSetOperationMode( ECAN_OP_MODE_NORMAL );

}
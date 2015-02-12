// File:  main.h

/* ******************************************************************************
 * VSCP (Very Simple Control Protocol)
 * http://www.vscp.org
 *
 * 2004-09-18
 * akhe@eurosource.se
 *
 * Copyright (C) 1995-2005 Ake Hedman, eurosource
 * Copyright (C) 1995-2013 Ake Hedman, Grodans Paradis AB
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

#ifndef SMARTRELAY_H
#define SMARTRELAY_H

//Defines
#define	TRUE			1
#define	FALSE			0

//
// 8 MHz with PLL => 8 MHz
// 1:4 prescaler => 1 MHz (1 uS cycle )
// 1 ms == 1000 uS
// 65535 - 1000 = 64535 = 0xfc17
//
// Timer2 use 250 and prescaler 1:4
//
//#define TIMER0_RELOAD_VALUE		0xfc17

//
// 10 MHz with PLL => 40 MHz
// 1:4 prescaler => 1.25 MHz ( 0.800 uS cycle )
// 1 ms == 1000 uS
// 65535 - 1250 = 64285 = 0xfb1d
//
// Timer2 use 156 and prescaler 1:8
//
#define TIMER0_RELOAD_VALUE		0xfb1d

//
// Timer 2 is used as a 1 ms clock
// 156 is loaded eight time to give ~1250 cycles
// Timer2 use 156 and prescaler 1:4, Postscaler 1:16
// 100 ns * 56 * 4 * 16 ~ 1 ms
//
#define TIMER2_RELOAD_VALUE		156

//
// Size for array used for temp mean calculations
//
#define TEMPERATURE_ARRAY_SIZE 	0x0A


#define STATUS_LED  PORTCbits.RC1
#define INIT_BUTTON PORTCbits.RC0

// Defines for relaybits
#define RELAY0  LATBbits.LATB4
#define RELAY1  LATBbits.LATB1
#define RELAY2  LATBbits.LATB0
#define RELAY3  LATCbits.LATC7
#define RELAY4  LATCbits.LATC6
#define RELAY5  LATCbits.LATC5
#define RELAY6  LATCbits.LATC4

// * * * Relay states * * *
#define RELAY_STATE_INACTIVE                0
#define RELAY_STATE_ACTIVE                  2
#define RELAY_STATE_PULSE                   3

#define RELAY_CONTROLBIT_STATE              0x01 	// Current relay state

// * * * Relay control bits * * *
#define RELAY_CONTROLBIT_PULSE              0x01 	// Enable pulse output
#define RELAY_CONTROLBIT_ALARM              0x02 	// Send alarm on protection time activation
#define RELAY_CONTROLBIT_PROTECTION         0x04 	// Enable protection timer
#define RELAY_CONTROLBIT_ONEVENT            0x08 	// Send ON event
#define RELAY_CONTROLBIT_OFFEVENT           0x10 	// Semd OFF event
#define RELAY_CONTROLBIT_STARTEVENT         0x20 	// Send START event
#define RELAY_CONTROLBIT_STOPEVENT          0x40 	// Sned STOP event
#define RELAY_CONTROLBIT_ENABLED            0x80 	// Relay enabled

// -----------------------------------------------

// * * *  Registers * * *
#define REG_RELAY_ZONE                      0
#define REG_RELAY_SUBZONE                   1

#define REG_RELAY0_STATE                    2
#define REG_RELAY1_STATE                    3
#define REG_RELAY2_STATE                    4
#define REG_RELAY3_STATE                    5
#define REG_RELAY4_STATE                    6
#define REG_RELAY5_STATE                    7
#define REG_RELAY6_STATE                    8
#define REG_RELAY7_STATE                    9

#define REG_RELAY0_CONTROL                  10
#define REG_RELAY1_CONTROL                  11
#define REG_RELAY2_CONTROL                  12
#define REG_RELAY3_CONTROL                  13
#define REG_RELAY4_CONTROL                  14
#define REG_RELAY5_CONTROL                  15
#define REG_RELAY6_CONTROL                  16
#define REG_RELAY7_CONTROL                  17

#define REG_RELAY0_PULSE_TIME_MSB           18
#define REG_RELAY0_PULSE_TIME_LSB           19
#define REG_RELAY1_PULSE_TIME_MSB           20
#define REG_RELAY1_PULSE_TIME_LSB           21
#define REG_RELAY2_PULSE_TIME_MSB           22
#define REG_RELAY2_PULSE_TIME_LSB           23
#define REG_RELAY3_PULSE_TIME_MSB           24
#define REG_RELAY3_PULSE_TIME_LSB           25
#define REG_RELAY4_PULSE_TIME_MSB           26
#define REG_RELAY4_PULSE_TIME_LSB           27
#define REG_RELAY5_PULSE_TIME_MSB           28
#define REG_RELAY5_PULSE_TIME_LSB           29
#define REG_RELAY6_PULSE_TIME_MSB           30
#define REG_RELAY6_PULSE_TIME_LSB           31
#define REG_RELAY7_PULSE_TIME_MSB           32
#define REG_RELAY7_PULSE_TIME_LSB           33

#define REG_RELAY0_PROTECTION_TIME_MSB      34
#define REG_RELAY0_PROTECTION_TIME_LSB      35
#define REG_RELAY1_PROTECTION_TIME_MSB      36
#define REG_RELAY1_PROTECTION_TIME_LSB      37
#define REG_RELAY2_PROTECTION_TIME_MSB      38
#define REG_RELAY2_PROTECTION_TIME_LSB      39
#define REG_RELAY3_PROTECTION_TIME_MSB      40
#define REG_RELAY3_PROTECTION_TIME_LSB      41
#define REG_RELAY4_PROTECTION_TIME_MSB      42
#define REG_RELAY4_PROTECTION_TIME_LSB      43
#define REG_RELAY5_PROTECTION_TIME_MSB      44
#define REG_RELAY5_PROTECTION_TIME_LSB      45
#define REG_RELAY6_PROTECTION_TIME_MSB      46
#define REG_RELAY6_PROTECTION_TIME_LSB      47
#define REG_RELAY7_PROTECTION_TIME_MSB      48
#define REG_RELAY7_PROTECTION_TIME_LSB      49

#define REG_RELAY0_ZONE                     50
#define REG_RELAY0_SUBZONE                  51
#define REG_RELAY1_ZONE                     52
#define REG_RELAY1_SUBZONE                  53
#define REG_RELAY2_ZONE                     54
#define REG_RELAY2_SUBZONE                  55
#define REG_RELAY3_ZONE                     56
#define REG_RELAY3_SUBZONE                  57
#define REG_RELAY4_ZONE                     58
#define REG_RELAY4_SUBZONE                  59
#define REG_RELAY5_ZONE                     60
#define REG_RELAY5_SUBZONE                  61
#define REG_RELAY6_ZONE                     62
#define REG_RELAY6_SUBZONE                  63
#define REG_RELAY7_ZONE                     64
#define REG_RELAY7_SUBZONE                  65

#define REG_DESCION_MATRIX                  72    // Start of matrix
//      72 - 127
#define DESCION_MATRIX_ROWS                 7

// * * * Persistent storage

#define VSCP_EEPROM_BOOTLOADER_FLAG         0x00	// Reserved for bootloader

#define VSCP_EEPROM_NICKNAME                0x01	// Persistant nickname id storage
#define VSCP_EEPROM_SEGMENT_CRC             0x02	// Persistant segment crc storage
#define VSCP_EEPROM_CONTROL                 0x03	// Persistant control byte

//#define EEPROM_ZONE                       0x04	// Zone node belongs to
//#define EEPROM_SUBZONE                    0x05	// Subzone node belongs to

#define VSCP_EEPROM_REG_USERID              0x06
#define VSCP_EEPROM_REG_USERID1             0x07
#define VSCP_EEPROM_REG_USERID2             0x08
#define VSCP_EEPROM_REG_USERID3             0x09
#define VSCP_EEPROM_REG_USERID4             0x0A

// The following can be stored in flash or eeprom

#define VSCP_EEPROM_REG_MANUFACTUR_ID0      0x0B
#define VSCP_EEPROM_REG_MANUFACTUR_ID1      0x0C
#define VSCP_EEPROM_REG_MANUFACTUR_ID2      0x0D
#define VSCP_EEPROM_REG_MANUFACTUR_ID3      0x0E

#define VSCP_EEPROM_REG_MANUFACTUR_SUBID0   0x0F
#define VSCP_EEPROM_REG_MANUFACTUR_SUBID1   0x10
#define VSCP_EEPROM_REG_MANUFACTUR_SUBID2   0x11
#define VSCP_EEPROM_REG_MANUFACTUR_SUBID3   0x12

// The following can be stored in program ROM (recommended) or in EEPROM

#define VSCP_EEPROM_REG_GUID                0x13	// Start of GUID MSB
// 		0x13 - 0x22

#define VSCP_EEPROM_REG_DEVICE_URL          0x23	// Start of Device URL storage
// 		0x23 - 0x42

#define VSCP_EEPROM_END                     0x43	// marks end of VSCP EEPROM usage
//   (next free position)

// --------------------------------------------------------------------------------

// * * * Actions * * *
#define ACTION_NOOP                         0
#define ACTION_ON                           1
#define ACTION_OFF                          2
#define ACTION_PULSE                        3
#define ACTION_TOGGLE                       4
// 4-9 reserved
#define ACTION_STATUS                       10
// 11-15 reserved
#define ACTION_DISABLE                      16

// Function Prototypes

void doWork(void);
void init(void);
void init_app_ram(void);
void init_app_eeprom(void);
void read_app_register(unsigned char reg);
void write_app_register(unsigned char reg, unsigned char val);
void sendDMatrixInfo(void);
void SendInformationEvent(unsigned char idx, unsigned char eventClass, unsigned char eventTypeId);

void doDM(void);

void doActionOn(unsigned char dmflags, unsigned char arg);
void doActionOff(unsigned char dmflags, unsigned char arg);
void doActionPulse(unsigned char dmflags, unsigned char arg);
void doActionStatus(unsigned char dmflags, unsigned char arg);
void doActionDisable(unsigned char dmflags, unsigned char arg);
void doActionToggle(unsigned char dmflags, unsigned char arg);

void doApplicationOneSecondWork(void);

/*!
        Send Extended ID CAN frame
        @param id CAN extended ID for frame.
        @param size Number of databytes 0-8
        @param pData Pointer to databytes of frame.
        @return TRUE (!=0) on success, FALSE (==0) on failure.
 */
int8_t sendCANFrame(uint32_t id, uint8_t size, uint8_t *pData);

/*!
        Get extended ID CAN frame
        @param pid Pointer to CAN extended ID for frame.
        @param psize Pointer to number of databytes 0-8
        @param pData Pointer to databytes of frame.
        @return TRUE (!=0) on success, FALSE (==0) on failure.
 */
int8_t getCANFrame(uint32_t *pid, uint8_t *psize, uint8_t *pData);

#endif

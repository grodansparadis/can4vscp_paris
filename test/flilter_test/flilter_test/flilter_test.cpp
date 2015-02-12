// flilter_test.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>

#define VSCP_EEPROM_END		0

typedef unsigned char uint8_t;
typedef unsigned long uint32_t;

//	7	Enabled if set to 1 
//	6	oaddr should be checked (=1) or not checked (=0)
//	5	Indicates hard-coded originating address if set to 1
//	4	Match Zone to trigger DM entry
//	3	Match sub-zone to trigger DM entry 
//	2	Reserved
//	1	Class-mask bit 8 
//	0	Class-filter bit 8 
//
// 
//Byte 0	Byte 1	Byte 2		Byte 3			Byte 4		Byte 5		Byte 6	Byte 7
//oaddr	flags	class-mask	class-filter	type-mask	type-filter	action	action-parameter


unsigned char dm[] = {
		0,0x80,0xff,0x1e,0xff,0x02,0,0x7f,
		0,0x80,0xff,0x1e,0xff,0x05,0,1,
		0,0x00,0,0,0,0,0,0,
		0,0x00,0,0,0,0,0,0,
		0,0x00,0,0,0,0,0,0,
		0,0x00,0,0,0,0,0,0,
		0,0x00,0,0,0,0,0,0
	};


unsigned char readEEPROM( int pos )
{
	return dm[ pos ];
}

void print32( unsigned long val )
{
	int i;
	char buf[128];
	char *p = buf + sizeof( buf )-1;
	memset( buf, 0, sizeof(buf) );

	p--;
	for ( i=0; i<32; i++ ) {
		if ( ( val >> i ) & 1 ) {
			*p-- = '1';
		}
		else {
			*p-- = '0';
		}

		if ( !((31-i) % 4) ) *p-- = ' ';
	}

	p++;p++;
	strcpy( buf, p );
	*p = 0;
	printf("%s -- %08X\n", buf, val );
}


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
    for ( i=0; i<7; i++ ) {

        // No need to check not active DM rows
        if ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 0x80 ) {

            // build the mask
            // ==============
            // We receive
            //  - all priorities
            //  - hardcoded and not hardcoded
            //  - from all nodes

            rowmask =
                    // Bit 9 of class mask
                    ( ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 2 ) << 23 ) |
                    // Rest of class mask
                    ( readEEPROM( VSCP_EEPROM_END + 8*i + 2 ) << 16 ) |
                    // Type mask
                    ( readEEPROM( VSCP_EEPROM_END + 8*i + 4 ) << 8 ) |
					// OID  - handle later
					0xff;                        
                    /*( ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 0x20 ) << 20 )*/;   // Hardcoded bit

            // build the filter
            // ================

            rowfilter =
                    // Bit 9 of class filter
                    ( ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 1 ) << 24 ) |
                    // Rest of class filter
                    ( readEEPROM( VSCP_EEPROM_END + 8*i + 3 ) << 16 ) |
                    // Type filter
                    ( readEEPROM( VSCP_EEPROM_END + 8*i + 5 ) << 8 ) |
                    // OID Mask cleard if not same OID for all or one or more
                    // rows don't have OID check flag set.
                    readEEPROM( VSCP_EEPROM_END + 8*i );

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
            if ( !readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 0x40 ) {
                // No should not be checked for this position
                // This mean that we can't filter on a specific OID
                // so mask must be a don't care
                mask &= ~0xff;
            }

            if ( i ) {
                // If the current OID is different than the previous
                // we accept all 
				for (j=0; j<8; j++ ) {
					if ( (lastOID>>i & 1 ) != (readEEPROM( VSCP_EEPROM_END + 8*i )>>i & 1) ) {
						mask &= (1<<i);	
					}
				}

                lastOID = readEEPROM( VSCP_EEPROM_END + 8*i );

            }
            else {
                // First round we just store the OID
                lastOID = readEEPROM( VSCP_EEPROM_END + 8*i );
            }

        }
    }

	printf("DM Matrix\n");
	printf("=========\n");
	for ( i=0; i<(7*8);i++ ) {
		printf("%02X ", readEEPROM( i ) );
		if ( !((i+1) % 8) ) printf("\n");
	}
	printf("\n");
	printf("\n");
	
	// mask
	printf("MASK\n");
	printf("====\n");
	for ( i=0; i<7; i++ ) {
		unsigned long val;
		// No need to check not active DM rows
        if ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 0x80 ) {
			val =
				// Bit 9 of class mask
				( ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 2 ) << 23 ) |
				// Rest of class mask
				( readEEPROM( VSCP_EEPROM_END + 8*i + 2 ) << 16 ) |
				// Type mask
				( readEEPROM( VSCP_EEPROM_END + 8*i + 4 ) << 8 ) |
				// OID  - handle later
				0xff;
			print32( val );
		}
	}
	printf("--------------------------------------------------\n");
	print32( mask );

	// mask
	printf("\n\n");
	printf("FILTER\n");
	printf("======\n");
	for ( i=0; i<7; i++ ) {
		unsigned long val;
		// No need to check not active DM rows
        if ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 0x80 ) {
			val =
				// Bit 9 of class filter
                    ( ( readEEPROM( VSCP_EEPROM_END + 8*i + 1 ) & 1 ) << 24 ) |
                    // Rest of class filter
                    ( readEEPROM( VSCP_EEPROM_END + 8*i + 3 ) << 16 ) |
                    // Type filter
                    ( readEEPROM( VSCP_EEPROM_END + 8*i + 5 ) << 8 ) |
                    // OID Mask cleard if not same OID for all or one or more
                    // rows don't have OID check flag set.
                    readEEPROM( VSCP_EEPROM_END + 8*i );
			print32( val );
		}
	}
	printf("--------------------------------------------------\n");
	print32( filter );
	
	printf("Done!\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	calculateSetFilterMask();

	return 0;
}


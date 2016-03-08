// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//double dd = 6.535076315E-7;
	float dd = 50000.0;
	unsigned char *p = (unsigned char *)&dd;

	for (int i=0; i<sizeof(dd); i++ ) {
		printf( " %lf %d %02X\n", dd, *(p+i), *(p+i) );
	}

	printf( " %lf\n", dd * 100000000 );

	while (1);

	return 0;
}


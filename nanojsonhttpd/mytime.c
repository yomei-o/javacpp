/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#include <string.h>
#include "mytime.h"


#ifdef _WIN32

int myclock()
{
	return -((int)clock());
}

#endif


#ifdef unix

/*
** get clock
*/
static unsigned int get_clock()
{
	struct timeval tv;
	struct timezone tz;
	unsigned int t=0;

	if(!gettimeofday(&tv, &tz)) {
		t  = (unsigned int)tv.tv_sec * myclock_sec();
		t += (unsigned int)tv.tv_usec / (1000 * 1000 / myclock_sec());
	}

	return t;
}

//tatic int myclock_flag=0;

/*
** countdown system clock emuration
*/
int myclock()
{
	static int offset = 0;
	static unsigned int last = 0;
	unsigned int t;

	t = get_clock();
	/* adjust time */
	if((t - offset)<last || (t - offset)>(last+myclock_sec()*10)) {
		//printf("hosei!\n");
		offset = t - last - myclock_sec();
	}
	last = t - offset;
	return -last;
}
#endif


#if (defined _SH2)||(defined _SH4)

int myclock()
{
	return GetFreeRun10m000();
}

#endif



#if 0


main()
{
	int i;


	while(1)
	{
			i=myclock();
			printf("%08d\n",-i);
			ymsleep(1000);
	}



}

#endif



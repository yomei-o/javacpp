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

#include <stdio.h>

#ifdef _WIN32
#include <process.h>
#include <io.h>
#include <fcntl.h>
#endif

#ifdef unix
#include <unistd.h>
#include <fcntl.h>
#endif

#include "fdup2.h"


FILE* fdup(FILE* fp,char*mode)
{
	int fd;
	if(fp==NULL)return NULL;
	fd=dup(fileno(fp));
	return fdopen(fd,mode);
}


FILE *fdup2( FILE *oldfp, FILE *newfp )
{
	int oldfd, newfd;
	int res;

	if( oldfp==NULL || newfp==NULL ) return NULL;

	oldfd = fileno( oldfp );
	newfd = fileno( newfp );
	
	res = dup2( oldfd, newfd );

	if( res==-1) return NULL;
	else return newfp;
}





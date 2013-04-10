/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA

import java.io.*;
import java.lang.*;

#else 

#include "String_.h"
#include "SockInit.h"
#include "Thread.h"

#include "sock2_local.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/



#ifdef JAVA 
#define println(a) System.out.println(a)
#define printf System.out.printf
#else
#define println(a) printf("%s\n",(char*)(a))
#endif

#ifdef JAVA 
#else
#define null 0
#define byte char
#define true 1
#define false 0
#endif








#ifdef JAVA
SockInit()
#else
SockInit::SockInit()
#endif
{
	winsock_init();
}

#ifndef JAVA
SockInit::SockInit(int id)
{
	winsock_done();
}
#endif

#ifndef JAVA
SockInit::~SockInit()
{
}
#endif


#ifndef JAVA
SockInit& SockInit::operator =(SockInit *f)
{
	if(f==NULL)goto end;
	delete f;
end:
	return *this;
}
#endif


static SockInit a;



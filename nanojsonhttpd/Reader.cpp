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
#include "Reader.h"
#include "Thread.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
#define null NULL
#define byte char
#define true 1
#define false 0
#endif



#ifdef JAVA
public class Reader implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif




#ifdef JAVA
Reader()
#else
Reader::Reader()
#endif
{
	handle=null;
	p_close=s_close;
	p_read=s_read;
	p_dup=s_dup;
	//if(p_open)handle=p_open(null);
}

#ifndef JAVA
Reader::Reader(int id)
{
	handle=null;
	p_close=s_close;
	p_read=s_read;
	p_dup=s_dup;
	//if(p_open)handle=p_open(null);
}
#endif


#ifndef JAVA
Reader::Reader(const Reader & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
Reader::~Reader()
{
	if(handle && p_close)p_close(handle);
	handle=null;
}
#endif


#ifndef JAVA
Reader& Reader::operator =(Reader *f)
{
	if(f==NULL)goto end;
	handle=f->handle;
	p_close=f->p_close;
	p_read=f->p_read;
	p_dup=f->p_dup;
	handle=p_dup(handle);
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
Reader& Reader::operator =(Reader& f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
	return *this;
}
#endif


#ifndef JAVA
void Reader::close()
{
	if(p_close)p_close(handle);
	handle=null;
}
#endif

#ifndef JAVA
int  Reader::read()
{
	char ret=-1;

	if(p_read)p_read(handle,&ret,0,1);
	return ret;
}
#endif


#ifndef JAVA
void Reader::s_close(void* vp)
{
	//printf("Reader close()\n");
}
#endif


#ifndef JAVA
void* Reader::s_dup(void* vp)
{
	//printf("Reader dup()\n");
	return vp;
}
#endif


#ifndef JAVA
int Reader::s_read(void* vp,char* buf,int off,int sz)
{
	buf[off]=0x33;
	return 1;
}
#endif

#ifdef JAVA
}
#endif



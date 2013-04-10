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
#include "Writer.h"
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
public class Writer implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif




#ifdef JAVA
Writer()
#else
Writer::Writer()
#endif
{
	handle=null;
	p_close=s_close;
	p_write=s_write;
	p_dup=s_dup;
	//if(p_open)handle=p_open(null);
}

#ifndef JAVA
Writer::Writer(int id)
{
	handle=null;
	p_close=s_close;
	p_write=s_write;
	p_dup=s_dup;
	//if(p_open)handle=p_open(null);
}
#endif

#ifndef JAVA
Writer::Writer(const Writer & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_write=f.p_write;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
Writer::~Writer()
{
	if(handle && p_close)p_close(handle);
	handle=null;
}
#endif


#ifndef JAVA
Writer& Writer::operator =(Writer *f)
{
	if(f==NULL)goto end;
	handle=f->handle;
	p_close=f->p_close;
	p_write=f->p_write;
	p_dup=f->p_dup;
	handle=p_dup(handle);
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
Writer& Writer::operator =(Writer& f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_write=f.p_write;
	p_dup=f.p_dup;
	handle=p_dup(handle);
	return *this;
}
#endif


#ifndef JAVA
void Writer::close()
{
	if(p_close)p_close(handle);
	handle=null;
}
#endif

#ifndef JAVA
void Writer::write(int c)
{
	char cc=c;
	if(p_write)p_write(handle,&cc,0,1);
}
#endif

#ifndef JAVA
void Writer::write(String & c)
{
	char* p;
	p=c.getBytes("utf-8");
	while(*p)
	{
		write(*p);
		p++;
	}
}
#endif


#ifndef JAVA
void Writer::s_close(void* vp)
{
	//printf("Writer close()\n");
}
#endif

#ifndef JAVA
void* Writer::s_dup(void* vp)
{
	//printf("Writer dup()\n");
	return vp;
}
#endif


#ifndef JAVA
int Writer::s_write(void* vp,char* buf,int off,int sz)
{
	return -1;
}
#endif

#ifdef JAVA
}
#endif



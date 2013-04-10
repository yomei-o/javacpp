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
#include "InputStream.h"

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
#define null 0
#define byte char
#define true 1
#define false 0
#endif



#ifdef JAVA
public class InputStream implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif




#ifdef JAVA
InputStream()
#else
InputStream::InputStream()
#endif
{
	handle=null;
	p_open=s_open;
	p_reset=s_reset;
	p_close=s_close;
	p_read=s_read;
	p_dup=s_dup;
	p_skip=s_skip;
	//if(p_open)handle=p_open(null);
}

#ifndef JAVA
InputStream::InputStream(int id)
{
	handle=null;
	p_open=s_open;
	p_reset=s_reset;
	p_close=s_close;
	p_read=s_read;
	p_dup=s_dup;
	p_skip=s_skip;
	//if(p_open)handle=p_open(null);
}
#endif


#ifndef JAVA
InputStream::InputStream(const InputStream & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_reset=f.p_reset;
	p_read=f.p_read;
	p_skip=f.p_skip;
	p_dup=f.p_dup;
	if(p_dup!=null)handle=p_dup(handle);
}
#endif

#ifndef JAVA
InputStream::~InputStream()
{
	if(handle && p_close)p_close(handle);
	handle=null;
}
#endif


#ifndef JAVA
InputStream& InputStream::operator =(InputStream *f)
{
	if(f==NULL)goto end;
	handle=f->handle;
	p_close=f->p_close;
	p_reset=f->p_reset;
	p_read=f->p_read;
	p_skip=f->s_skip;
	p_dup=f->p_dup;
	if(p_dup!=null)handle=p_dup(handle);
	delete f;
end:
	return *this;
}
#endif

#if 0
InputStream& InputStream::operator =(InputStream& f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_reset=f.p_reset;
	p_read=f.p_read;
	p_dup=f.p_dup;
	p_skip=f.s_skip;
	if(p_dup!=null)handle=p_dup(handle);
	return *this;
}
#endif

#ifndef JAVA
InputStream& InputStream::operator =(InputStream f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_reset=f.p_reset;
	p_read=f.p_read;
	p_skip=f.s_skip;
	p_dup=f.p_dup;
	if(p_dup!=null)handle=p_dup(handle);
	return *this;
}
#endif

#ifndef JAVA
bool InputStream::operator ==(int id)
{
	if(id==0 && handle==NULL)return true;
	return false;
}
#endif

#ifndef JAVA
bool InputStream::operator !=(int id)
{
	if(id==0 && handle==NULL)return false;
	return true;
}
#endif

#ifndef JAVA
void InputStream::reset()
{
	if(p_reset)p_reset(handle);
}
#endif

#ifndef JAVA
void InputStream::close()
{
	if(p_close)p_close(handle);
	handle=null;
}
#endif

#ifndef JAVA
int  InputStream::read(char* p,int o,int s)
{
	if(p_read)return p_read(handle,p,o,s);
	return -1;
}
#endif

#ifndef JAVA
int  InputStream::skip(int s)
{
	if(p_skip)return p_skip(handle,s);
	return 0;
}
#endif


#ifndef JAVA
void InputStream::s_reset(void* vp)
{
	//printf("InputStream reset()\n");
}
#endif

#ifndef JAVA
void InputStream::s_close(void* vp)
{
	//printf("InputStream close()\n");
}
#endif


#ifndef JAVA
void* InputStream::s_dup(void* vp)
{
	//printf("InputStream dup()\n");
	return vp;
}
#endif

#ifndef JAVA
void* InputStream::s_open(void* vp)
{
	//printf("InputStream open()\n");
	return (void*)1;
}
#endif


#ifndef JAVA
int InputStream::s_read(void* vp,char* p,int o,int sz)
{
	int i;
	//printf("InputStream read(%08x,%d,%d)\n",p,o,sz);
	for(i=0;i<sz;i++){
		p[o+i]=((i&15)<<4)+(i&15);
	}
	return sz;
}
#endif

#ifndef JAVA
int InputStream::s_skip(void* vp,int sz)
{
	//printf("InputStream skip()\n");
	return 0;
}
#endif


#ifdef JAVA
}
#endif



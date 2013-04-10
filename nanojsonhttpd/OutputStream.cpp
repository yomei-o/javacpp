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
#include "OutputStream.h"

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
public class OutputStream implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif




#ifdef JAVA
OutputStream()
#else
OutputStream::OutputStream()
#endif
{
	handle=null;
	p_open=s_open;
	p_flush=s_flush;
	p_close=s_close;
	p_write=s_write;
	p_dup=s_dup;
	//if(p_open)handle=p_open(null);
}

#ifndef JAVA
OutputStream::OutputStream(int id)
{
	handle=null;
	p_open=s_open;
	p_flush=s_flush;
	p_close=s_close;
	p_write=s_write;
	p_dup=s_dup;
	//if(p_open)handle=p_open(null);
}
#endif

#ifndef JAVA
OutputStream::OutputStream(const OutputStream & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_flush=f.p_flush;
	p_write=f.p_write;
	p_dup=f.p_dup;
	if(p_dup)handle=p_dup(handle);
}
#endif

#ifndef JAVA
OutputStream::~OutputStream()
{
	if(handle && p_close)p_close(handle);
	handle=null;
}
#endif


#ifndef JAVA
OutputStream& OutputStream::operator =(OutputStream *f)
{
	if(f==NULL)goto end;
	handle=f->handle;
	p_close=f->p_close;
	p_flush=f->p_flush;
	p_write=f->p_write;
	p_dup=f->p_dup;
	if(p_dup!=null)handle=p_dup(handle);
	delete f;
end:
	return *this;
}
#endif

#if 0
OutputStream& OutputStream::operator =(OutputStream& f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_flush=f.p_flush;
	p_write=f.p_write;
	p_dup=f.p_dup;
	if(p_dup!=null)handle=p_dup(handle);
	return *this;
}
#endif

#ifndef JAVA
OutputStream& OutputStream::operator =(OutputStream f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_flush=f.p_flush;
	p_write=f.p_write;
	p_dup=f.p_dup;
	if(p_dup!=null)handle=p_dup(handle);
	return *this;
}
#endif

#ifndef JAVA
bool OutputStream::operator ==(int id)
{
	if(id==0 && handle==NULL)return true;
	return false;
}
#endif

#ifndef JAVA
bool OutputStream::operator !=(int id)
{
	if(id==0 && handle==NULL)return false;
	return true;
}
#endif



#ifndef JAVA
void OutputStream::flush()
{
	if(p_flush)p_flush(handle);
}
#endif

#ifndef JAVA
void OutputStream::close()
{
	if(p_close)p_close(handle);
	handle=null;
}
#endif

#ifndef JAVA
int OutputStream::write(char* p,int o,int s)
{
	if(p_write)return p_write(handle,p,o,s);
	return -1;
}
#endif

#ifndef JAVA
void OutputStream::s_flush(void* vp)
{
	//printf("OutputStream flush()\n");
}
#endif

#ifndef JAVA
void OutputStream::s_close(void* vp)
{
	//printf("OutputStream close()\n");
}
#endif

#ifndef JAVA
void* OutputStream::s_dup(void* vp)
{
	//printf("OutputStream dup()\n");
	return vp;
}
#endif

#ifndef JAVA
void* OutputStream::s_open(void* vp)
{
	//printf("OutputStream open()\n");
	return (void*)1;
}
#endif


#ifndef JAVA
int  OutputStream::s_write(void* vp,char* p,int o,int ss)
{
	//int i,sz;
	//printf("OutputStream write(%08x,%d,%d)\n",p,o,ss);
	//sz=ss>16?16:ss;
	//for(i=0;i<sz;i++){
	//	if(i%16==0)printf("%08x: ",p+o+i);
	//	printf("%02x ",p[o+i]&255);
	//	if(i%16==15)printf("\n");
	//	if(i+1==sz)printf("\n");
	//
	//}
	return -1;
}
#endif

#ifdef JAVA
}
#endif



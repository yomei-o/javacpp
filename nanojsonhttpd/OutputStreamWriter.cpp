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

#include "OutputStreamWriter.h"

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
public class OutputStreamWriter implements Runnable{
#endif



#ifdef JAVA
	//member list
#endif




#ifdef JAVA
OutputStreamWriter()
#else
OutputStreamWriter::OutputStreamWriter()
#endif
{
}

#ifndef JAVA
OutputStreamWriter::OutputStreamWriter(int id)
{
}
#endif


#ifndef JAVA
OutputStreamWriter::OutputStreamWriter(const OutputStreamWriter & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_write=f.p_write;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
OutputStreamWriter::OutputStreamWriter(OutputStream & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_write=f.p_write;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
OutputStreamWriter::~OutputStreamWriter()
{
}
#endif


#ifndef JAVA
OutputStreamWriter& OutputStreamWriter::operator =(OutputStreamWriter *f)
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
OutputStreamWriter& OutputStreamWriter::operator =(OutputStreamWriter& f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_write=f.p_write;
	p_dup=f.p_dup;
	handle=p_dup(handle);
	return *this;
}
#endif



#ifdef JAVA
}
#endif





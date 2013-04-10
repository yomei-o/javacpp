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

#include "FileWriter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOutputStream.h"

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
public class FileWriter implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif





#ifndef JAVA
FileWriter::FileWriter(int id)
{
}
#endif


#ifndef JAVA
	FileWriter::FileWriter(const FileWriter & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_write=f.p_write;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
FileWriter::FileWriter(File & f)
{
	FileOutputStream fos=null;
	fos=new FileOutputStream(f);

	handle=fos.handle;
	p_close=fos.p_close;
	p_write=fos.p_write;
	p_dup=fos.p_dup;
	handle=p_dup(handle);

}
#endif

#ifndef JAVA
FileWriter::FileWriter(String & f)
{
	FileOutputStream fos=null;
	fos=new FileOutputStream(f);

	handle=fos.handle;
	p_close=fos.p_close;
	p_write=fos.p_write;
	p_dup=fos.p_dup;
	handle=p_dup(handle);

}
#endif


#ifndef JAVA
FileWriter::FileWriter(char* f)
{
	FileOutputStream fos=null;
	fos=new FileOutputStream(f);

	handle=fos.handle;
	p_close=fos.p_close;
	p_write=fos.p_write;
	p_dup=fos.p_dup;
	handle=p_dup(handle);

}
#endif


#ifndef JAVA
FileWriter::~FileWriter()
{
}
#endif


#ifndef JAVA
FileWriter& FileWriter::operator =(FileWriter *f)
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
FileWriter& FileWriter::operator =(FileWriter& f)
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



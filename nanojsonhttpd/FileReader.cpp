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

#include "FileReader.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileInputStream.h"

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
public class FileReader implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif





#ifndef JAVA
FileReader::FileReader(int id)
{
}
#endif


#ifndef JAVA
FileReader::FileReader(const FileReader & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
FileReader::FileReader(File & f)
{
	FileInputStream fis=null;
	fis=new FileInputStream(f);

	handle=fis.handle;
	p_close=fis.p_close;
	p_read=fis.p_read;
	p_dup=fis.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
FileReader::FileReader(String & str)
{
	FileInputStream fis=null;
	fis=new FileInputStream(str);

	handle=fis.handle;
	p_close=fis.p_close;
	p_read=fis.p_read;
	p_dup=fis.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
FileReader::FileReader(char* str)
{
	FileInputStream fis=null;
	fis=new FileInputStream(str);

	handle=fis.handle;
	p_close=fis.p_close;
	p_read=fis.p_read;
	p_dup=fis.p_dup;
	handle=p_dup(handle);
}
#endif


#ifndef JAVA
FileReader::~FileReader()
{
}
#endif


#ifndef JAVA
FileReader& FileReader::operator =(FileReader *f)
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
FileReader& FileReader::operator =(FileReader& f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
	return *this;
}
#endif


#ifdef JAVA
}
#endif



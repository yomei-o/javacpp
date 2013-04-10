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

#include "BufferedReader.h"

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
public class BufferedReader implements Runnable{
#endif


#ifdef JAVA
	//member list
#endif





#ifndef JAVA
BufferedReader::BufferedReader(int id)
{
}
#endif


#ifndef JAVA
BufferedReader::BufferedReader(const BufferedReader & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
BufferedReader::BufferedReader(Reader & f)
{
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
}
#endif

#ifndef JAVA
BufferedReader::~BufferedReader()
{
}
#endif


#ifndef JAVA
BufferedReader& BufferedReader::operator =(BufferedReader *f)
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
BufferedReader& BufferedReader::operator =(BufferedReader& f)
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
String BufferedReader::readLine()
{
	String ret=null;
	String s=null;
	char a;
	ret="";

	while(1){
		a=read();
		if(a==0 || a==-1)break;
		if(a=='\r')continue;
		if(a=='\n')break;

		s=new String(&a,0,1);
		ret+=s;
	}

	return ret;
}
#endif



#ifdef JAVA
}
#endif



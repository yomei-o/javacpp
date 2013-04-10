/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA
//  JAVA packagename
package com.yomei.myhttpd;

import java.io.*;
import java.lang.*;

#else 

#include "SafeBufferedReader.h"
#include "FileReader.h"

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
public class SafeBufferedReader extends BufferedReader{
#endif


#ifdef JAVA
	int maxn=0;
	//member list
#endif





#ifndef JAVA
SafeBufferedReader::SafeBufferedReader(int id):BufferedReader(id)
{
	maxn=4096;
}
#endif


#ifndef JAVA
	SafeBufferedReader::SafeBufferedReader(const SafeBufferedReader & f):BufferedReader(f)
{
	maxn=4096;
//	handle=f.handle;
//	p_close=f.p_close;
//	p_read=f.p_read;
//	p_dup=f.p_dup;
//	handle=p_dup(handle);
}
#endif

#ifdef JAVA
public SafeBufferedReader(Reader f)
{
	super(f);
	maxn=4096;
}
#else
SafeBufferedReader::SafeBufferedReader(Reader & f):BufferedReader(f)
{
	maxn=4096;
//	handle=f.handle;
//	p_close=f.p_close;
//	p_read=f.p_read;
//	p_dup=f.p_dup;
//	handle=p_dup(handle);
}
#endif

#ifndef JAVA
SafeBufferedReader::~SafeBufferedReader()
{
}
#endif


#ifndef JAVA
SafeBufferedReader& SafeBufferedReader::operator =(SafeBufferedReader *f)
{
	if(f==NULL)goto end;
	maxn=f->maxn;
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
SafeBufferedReader& SafeBufferedReader::operator =(SafeBufferedReader& f)
{
	maxn=f.maxn;
	handle=f.handle;
	p_close=f.p_close;
	p_read=f.p_read;
	p_dup=f.p_dup;
	handle=p_dup(handle);
	return *this;
}
#endif

#ifdef JAVA
public void setMaximum(int n)
#else
void SafeBufferedReader::setMaximum(int n)
#endif
{
	if(n>0)maxn=n;
}
#ifdef JAVA
public String readLine()
#else
String SafeBufferedReader::readLine()
#endif

{
	String ret=null;
	String s=null;
	char a;
	int err=0;
	int ct=0;

#ifdef JAVA
	char[] b=null;
#else
	char* b=null;
#endif

	b=new char[1];
	ret="";

	while(true){
		a=(char)-1;
#ifdef JAVA
		try{
#endif
		a=(char)read();
#ifdef JAVA
		}catch(Exception e){}
#endif
		if(a==0 || a==((char)-1))break;
		if(a=='\r')continue;
		if(a=='\n')break;
		b[0]=a;
		s=new String(b,0,1);
		ret+=s;
		ct++;
		if(ct>maxn){
			err=1;
			break;
		}
	}

#ifndef JAVA
	delete[] b;
#endif
	if(err!=0){
		String ss=null;
		return ss;
	}
	return ret;
}



#if 0

#ifdef JAVA
public static void main(String argv2[])
#else 
int main(int argc,char* argv[])
#endif
{

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

#ifdef JAVA
	try{
#endif

	FileReader fr=null;

	fr=new FileReader("test.txt");

	SafeBufferedReader sbr=null;
	sbr=new SafeBufferedReader(fr);
	
	String sss=null;

	sss=sbr.readLine();
	//printf(">>%s<<\n",sss);

#ifdef JAVA
	}catch(Exception e){}
#endif

#ifndef JAVA
	return 0;
#endif
}
#endif


#ifdef JAVA
}
#endif



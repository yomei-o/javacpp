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
#include "StringTokenizer.h"
#include "Thread.h"

#include "strtok_r.h"

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
StringTokenizer()
#else
StringTokenizer::StringTokenizer()
#endif
{
	str="";
	sep=" \r\n\t";
	p=null;
	isfirst=1;
}

#ifndef JAVA
StringTokenizer::StringTokenizer(int id)
{
	str="";
	sep=" \r\n\t";
	p=null;
	isfirst=1;
}
#endif


#ifndef JAVA
StringTokenizer::StringTokenizer(char* ss)
{
	str=ss;
	sep=" \r\n\t";
	p=null;	
	isfirst=1;
}
#endif
#ifndef JAVA
StringTokenizer::StringTokenizer(String & ss)
{
	str=ss;
	sep=" \r\n\t";
	p=null;
	isfirst=1;
}
#endif

#ifndef JAVA
StringTokenizer::StringTokenizer(char* ss,char* sseepp)
{
	str=ss;
	sep=sseepp;
	p=null;	
	isfirst=1;
}
#endif
#ifndef JAVA
StringTokenizer::StringTokenizer(String & ss,String & sseepp)
{
	str=ss;
	sep=sseepp;
	p=null;
	isfirst=1;
}
#endif


#ifndef JAVA
StringTokenizer::~StringTokenizer()
{
}
#endif


#ifndef JAVA
StringTokenizer& StringTokenizer::operator =(StringTokenizer *f)
{
	if(f==NULL)goto end;
	str=f->str;
	sep=f->sep;
	p=f->p;
	isfirst=f->isfirst;
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
bool StringTokenizer::hasMoreTokens()
{
	char *pp;
	char *ret;
	String nokori=null;
	if(isfirst)nokori=str;
	else{
		if(p==NULL)return false;
		nokori=p;
	}
	if(nokori==null)return false;

	ret=my_strtok_r(nokori,(char*)sep,&pp);

	if(ret==NULL)return false;
	return true;
}
#endif
#ifndef JAVA
String 	StringTokenizer::nextToken()
{
	String ret=null;
	char* t;

	t=my_strtok_r(isfirst?((char*)str):NULL,(char*)sep,&p);
	if(t)ret=t;
	isfirst=0;
	return ret;
}
#endif




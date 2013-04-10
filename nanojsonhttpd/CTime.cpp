/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA
//  JAVA packagename
package com.yomei.myhttpd;
//  JAVA imports
#endif

#ifndef JAVA
#include <time.h>
#include "String_.h"
#include "CTime.h"
#include "mytime.h"
#endif


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define print(a) printf("%s\n",(char*)(a))

#define null 0
#define byte char
#define true 1
#define false 0


#ifdef JAVA
public class CTime{
#endif

#ifdef JAVA
CTime()
#else
CTime::CTime()
#endif
{
#ifndef JAVA
	m_null=false;
#endif
}

#ifndef JAVA
CTime::CTime(int id)
{
	if(id==0)m_null=true;
}
#endif

#ifndef JAVA
CTime::~CTime()
{
}
#endif

#ifndef JAVA
class CTime& CTime::operator =(class CTime *f)
{
	if(f==NULL)goto end;
	m_null=f->m_null;
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
bool CTime::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif


#ifndef JAVA
bool CTime::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif

#ifndef JAVA
CTime::CTime(const class CTime &f)
{
	m_null=f.m_null;
}
#endif


#ifdef JAVA
public static int  get()
#else
int  CTime::get()
#endif
{
	int ret=0;
#ifdef JAVA
	ret=(int)(System.currentTimeMillis()/1000);
#else
	ret=(int)(::time(null));
#endif
	return ret;
}

#ifdef JAVA
}
#endif


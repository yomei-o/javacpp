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
#include "String_.h"
#include "MyClock.h"
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
public class MyClock{
#endif

#ifdef JAVA
MyClock()
#else
MyClock::MyClock()
#endif
{
#ifndef JAVA
	m_null=false;
#endif
}

#ifndef JAVA
MyClock::MyClock(int id)
{
	if(id==0)m_null=true;
}
#endif

#ifndef JAVA
MyClock::~MyClock()
{
}
#endif

#ifndef JAVA
class MyClock& MyClock::operator =(class MyClock *f)
{
	if(f==NULL)goto end;
	m_null=f->m_null;
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
bool MyClock::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif


#ifndef JAVA
bool MyClock::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif

#ifndef JAVA
MyClock::MyClock(const class MyClock &f)
{
	m_null=f.m_null;
}
#endif


#ifdef JAVA
public static int  get()
#else
int  MyClock::get()
#endif
{
	int ret=0;
#ifdef JAVA
	ret=(int)(System.currentTimeMillis()& 0xffffffff);
	ret=-ret;
#else
	ret=myclock();
#endif
	return ret;
}

#ifdef JAVA
}
#endif


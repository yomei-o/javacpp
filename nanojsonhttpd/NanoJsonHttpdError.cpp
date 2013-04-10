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
import java.net.*;
import java.util.*;

#else 

#include "NanoJsonHttpdError.h"
#include "String_.h"
#include "Thread.h"
#include "NanoJsonHttpd.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/

#define MAX_SERVER_NUM 20


#ifdef JAVA 
#ifdef ANDROID
#define println(a) System.out.println(a)
#else
#define println(a) System.out.println(a)
#endif
#else
#define println(a) printf("%s\n",(char*)(a))
#endif


#ifdef JAVA 
#else
#define null 0
#define byte char
#define true 1
#define false 0
#define boolean bool
#endif



#ifdef JAVA 
#define BEGIN_TRY() try{
#define END_TRY() }catch(Exception e){}
#else
#define BEGIN_TRY()
#define END_TRY()
#endif

#ifndef JAVA
#define ArrayOf(a,b) (*a[b])
#else
#define ArrayOf(a,b) (a[b])
#endif

#ifdef JAVA
#define ArrayLength(ii,a) ii=a.length
#else
#define ArrayLength(ii,a) {ii=0; while(a[ii]!=null)ii++;}
#endif


#ifdef JAVA
public class NanoJsonHttpdError{
#endif

static boolean flagError=false;


#ifdef JAVA
NanoJsonHttpdError()
#else
NanoJsonHttpdError::NanoJsonHttpdError()
#endif
{
}

#ifndef JAVA
NanoJsonHttpdError::NanoJsonHttpdError(int id)
{
}
#endif

#ifndef JAVA
NanoJsonHttpdError::~NanoJsonHttpdError()
{
}
#endif


#ifndef JAVA
class NanoJsonHttpdError& NanoJsonHttpdError::operator =(class NanoJsonHttpdError *f)
{
	if(f==NULL)goto end;
	delete f;
end:
	return *this;
}
#endif



#ifdef JAVA
public static void setError()
#else
void NanoJsonHttpdError::setError()
#endif
{
	flagError=true;
}

#ifdef JAVA
public static boolean isError()
#else
boolean NanoJsonHttpdError::isError()
#endif
{
	return flagError;
}



#ifdef JAVA
}
#endif







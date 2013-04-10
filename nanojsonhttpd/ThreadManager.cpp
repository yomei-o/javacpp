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

#include "ThreadManager.h"
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
public class ThreadManager{
#endif

static NanoJsonHttpd h=null;
static Thread st=null;
static boolean isInit=false;


#ifdef JAVA
ThreadManager()
#else
ThreadManager::ThreadManager()
#endif
{
}

#ifndef JAVA
ThreadManager::ThreadManager(int id)
{
}
#endif

#ifndef JAVA
ThreadManager::~ThreadManager()
{
}
#endif


#ifndef JAVA
class ThreadManager& ThreadManager::operator =(class ThreadManager *f)
{
	if(f==NULL)goto end;
	delete f;
end:
	return *this;
}
#endif



#ifdef JAVA
public static void start()
#else
void ThreadManager::start()
#endif
{
	int i;
	if(isInit==true)return;
	isInit=true;

#ifdef JAVA
	try{
#endif
	h=new NanoJsonHttpd();
	st=new Thread(h);
	st.start();
#ifdef JAVA
	}catch(Exception e){e.printStackTrace();}
#endif
	for(i=0;i<10;i++){
		if(h.isReady())break;
#ifdef JAVA
		try{
#endif
		st.sleep(100);
#ifdef JAVA
	}catch(Exception e){e.printStackTrace();}
#endif
	}

}

#ifdef JAVA
public static void stop()
#else
void ThreadManager::stop()
#endif
{
	if(isInit==false)return;
	isInit=false;
	h.stopAll();
#ifdef JAVA
	try{
#endif
	st.join();
#ifdef JAVA
	}catch(Exception e){e.printStackTrace();}
#endif
	h=null;
	st=null;

}



#ifdef JAVA
}
#endif






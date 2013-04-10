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

#include "NanoJsonHttpd.h"
#include "NanoJsonHttpdError.h"
#include "HttpSession.h"
#include "Thread.h"

#include "FileReader.h"
#include "BufferedReader.h"


#include "InetSocketAddress.h"
#include "StringTokenizer.h"
#include "InetAddress.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/



#ifdef JAVA 
#define getchar() System.in.read()
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
#define boolean bool
#endif



#ifdef JAVA
public class NanoJsonHttpd implements Runnable{
#endif


#ifdef JAVA
	ServerSocket s=null;
	int port;
	static int stop_req=0;
	static int is_ready=0;
	//member list
#else
	int NanoJsonHttpd::stop_req=0;
	int NanoJsonHttpd::is_ready=0;
#endif




#ifdef JAVA
NanoJsonHttpd()
#else
NanoJsonHttpd::NanoJsonHttpd()
#endif
{
#ifndef JAVA
	prun=s_run;
	isnull=false;
#endif
	//println("NanoJsonHttpd()\n");
	port=11228;
	stop_req=0;
	is_ready=0;
}

#ifndef JAVA
NanoJsonHttpd::NanoJsonHttpd(int id)
{
#ifndef JAVA
	prun=s_run;
	isnull=true;
#endif
	//println("NanoJsonHttpd(id)\n");
	port=11228;
	stop_req=0;
	is_ready=0;
}
#endif

#ifndef JAVA
NanoJsonHttpd::~NanoJsonHttpd()
{
	//println("~NanoJsonHttpd()\n");
}
#endif


#ifndef JAVA
NanoJsonHttpd& NanoJsonHttpd::operator =(NanoJsonHttpd *f)
{
	if(f==NULL)goto end;
	port=f->port;
	prun=f->prun;
	isnull=f->isnull;
	is_ready=f->is_ready;
	s=f->s;

	delete f;
end:
	return *this;
}
#endif

#ifdef JAVA
public void run()
#else
void NanoJsonHttpd::run()
#endif
{
	println("NanoJsonHttpd::run()\n");



#ifdef JAVA
	try{
#endif
		s=null;
		s=new ServerSocket(port);
#ifdef JAVA
	}catch(Exception e){}
#endif

	//s=null;

	if(s==null){
		println("server bind error!\n");
		NanoJsonHttpdError.setError();
		return;
	}
	is_ready=1;
#ifdef JAVA
	try{
#endif
	s.setSoTimeout(2000);
#ifdef JAVA
	}catch(Exception e){}
#endif

	Socket cs=null;

	while(true){
		//printf("kita!!\n");
#ifdef JAVA
	try{
#endif
		cs=s.accept();
		if(cs!=null){
			//printf("accept!!\n");
			HttpSession hs=null;

			hs=new HttpSession(cs);
			hs.start();
			cs=null;
		}
#ifdef JAVA
	}catch(Exception e){}
#endif
		//printf("nuketa\n");
		if(stop_req!=0){
		break;
		}
	}
	is_ready=0;
#ifdef JAVA
	try{
#endif
	s.close();
#ifdef JAVA
	}catch(Exception e){}
#endif
}


#ifndef JAVA
void NanoJsonHttpd::s_run(void* arg)
{
	NanoJsonHttpd* r=new NanoJsonHttpd();
	((Runnable*)arg)->flag=1;
	r->run();
	delete r;
}
#endif



#ifdef JAVA
public void stopAll()
#else
void NanoJsonHttpd::stopAll()
#endif
{
	stop_req=1;
}


#ifndef JAVA
bool NanoJsonHttpd::operator ==(int id)
{
	if(isnull)return true;
	return false;
}
#endif

#ifndef JAVA
bool NanoJsonHttpd::operator !=(int id)
{
	if(isnull)return false;
	return true;
}
#endif



#ifdef JAVA
boolean isReady()
#else
boolean NanoJsonHttpd::isReady()
#endif
{
	if(is_ready==0)return false;
	return true;
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

		int c=0;
		NanoJsonHttpd h=null;
		Thread t=null;
		Thread st;

		t=new Thread();
		h=new NanoJsonHttpd();
		st=new Thread(h);

		st.start();

		while(true){
			c=getchar();
			if(c=='q' || c=='Q')break;
		}

		h.stopAll();



#ifdef JAVA
	}catch(Exception e){e.printStackTrace();}
#endif


#ifndef JAVA
	return 0;
#endif
}
#endif





#ifdef JAVA
}
#endif

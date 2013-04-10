#ifdef JAVA

package com.sony.myssdp;
import java.io.*;
import java.lang.*;

#else 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TestEvent.h"
#include "TestListener.h"
#include "MyListener.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif


#ifndef JAVA
#define null 0
#define byte char
#define true 1
#define false 0
#endif

#ifdef JAVA 
#define print(a) System.out.println(a)
#define printf System.out.printf
#else
#define print(a) printf("%s\n",(char*)(a))
#endif



#ifdef JAVA
public class Main{
#endif


#ifdef JAVA
public static TestListener tt=null;
#else
static TestListener tt=null;
#endif


#ifdef JAVA
public static void regist(TestListener tl)
#else 
void regist(TestListener& tl)
#endif
{
	TestEvent te=null;
	te=new TestEvent();

	tt=tl;
	if(tt!=null)tt.onTestEvent(te);
}

#ifdef JAVA
public static TestListener create()
#else 
TestListener create()
#endif
{
	TestListener tl=null;
	tl=new MyListener();
	return tl;
}

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

	TestListener tl=null;
	TestListener tl_null=null;

	//tl=new MyListener();
	tl=create();
	regist(tl);
	regist(tl_null);

#ifndef JAVA
	return 0;
#endif
}





#ifdef JAVA
}
#endif




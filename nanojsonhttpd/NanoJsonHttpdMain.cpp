/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA
package com.yomei.myhttpd;
//  JAVA imports
import java.io.*;
import java.net.*;
#else /* JAVA */

//  C Include
#include <stdio.h>
#ifdef unix
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

//  Memory Debug
#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif /* _WIN32 */

#include "NanoJsonHttpdMain.h"
#include "String_.h"
#include "ThreadManager.h"
#include "NanoJsonHttpdError.h"

#endif /* JAVA */


#ifndef JAVA 
#define null 0
#define byte char
#define true 1
#define false 0
#endif /* JAVA */

/*
** Console I/O function for C
*/
#ifndef JAVA

static void println(char* a){
	printf("%s\n",a);
}
static void print(char* a){
	printf("%s",a);
}
static void mysleep(int ms)
{
#ifdef unix
	::sleep(ms / 1000);
	usleep((ms % 1000) * 1000);
#endif
#ifdef _WIN32
	Sleep(ms);
#endif
}

#endif /* JAVA */
//
// Main class 
//


#ifdef JAVA
public class NanoJsonHttpdMain{
#endif /* JAVA */


//
// C like I/O methods
//
#ifdef JAVA
public static void print(String s){
	System.out.print(s);
}
#else
void NanoJsonHttpdMain::print(String& s){
	::print((char*)s);
}
void NanoJsonHttpdMain::print(char*s){
	::print(s);
}
#endif


#ifdef JAVA
public static void println(String s){
	System.out.println(s);
}
#else
void NanoJsonHttpdMain::println(String& s){
	::println((char*)s);
}
void NanoJsonHttpdMain::println(char*s){
	::println(s);
}
#endif


#ifdef JAVA
public static void sleep(int ms){
	try{
		Thread.sleep(ms);
	}catch(Exception e){}
}
#else
void NanoJsonHttpdMain::sleep(int ms){
	mysleep(ms);
}
#endif




/*
** Main function
*/
#ifndef JAVA
int main(int argc,char* argv[]){
	NanoJsonHttpdMain::main(argc-1,&argv[1]);
	return 1;
}
#endif

#ifdef JAVA
public static void main(String argv[])
{
	main(argv.length,argv);
}
#endif

#ifdef JAVA
public static void main(int argc,String argv[])
#else
void NanoJsonHttpdMain::main(int argc,char* argv[])
#endif
{

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	println("NanoJsonHttpdMain Thread start");
	ThreadManager.start();	
	while(true){
		if(NanoJsonHttpdError.isError())break;
		sleep(1000*3);	
	}
	ThreadManager.stop();	
	println("NanoJsonHttpdMain Thread end");

}

#ifdef JAVA
}
#endif


 


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

#include "String_.h"
#include "MyAddress.h"
#include "Thread.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/



#ifdef JAVA 
#define print(a) System.out.println(a)
#define printf System.out.printf
#else
#define print(a) printf("%s\n",(char*)(a))
#endif

#ifdef JAVA 
#else
#define null 0
#define byte char
#define true 1
#define false 0
#endif




#ifdef JAVA
public class MyAddress{
#endif


#ifdef JAVA
int port=0;
int len=0;
int type=0;
byte[] address=new byte[16];
#endif

#ifdef JAVA
MyAddress()
#else
MyAddress::MyAddress()
#endif
{
	int i;
#ifndef JAVA
	isnull=false;
#endif
	len=0;
	type=0;
	for(i=0;i<16;i++)address[i]=0;
	port=0;
}

#ifndef JAVA
MyAddress::MyAddress(int id)
{
	int i;

	isnull=true;
	len=0;
	type=0;
	for(i=0;i<16;i++)address[i]=0;
	port=0;
}
#endif

#ifndef JAVA
MyAddress::~MyAddress()
{
}
#endif

#ifndef JAVA
MyAddress::MyAddress(const MyAddress& f)
{
	int i;
	isnull=f.isnull;

	port=f.port;
	len=f.len;
	type=f.type;
	for(i=0;i<16;i++)address[i]=f.address[i];
}
#endif



#ifndef JAVA
MyAddress& MyAddress::operator =(MyAddress *f)
{
	int	i;
	if(f==NULL)goto end;
	isnull=f->isnull;

	port=f->port;
	len=f->len;
	type=f->type;
	for(i=0;i<16;i++)address[i]=f->address[i];

	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
MyAddress& MyAddress::operator =(MyAddress f)
{
	int i;

	isnull=f.isnull;

	port=f.port;
	len=f.len;
	type=f.type;
	for(i=0;i<16;i++)address[i]=f.address[i];

	return *this;
}
#endif


#ifndef JAVA
bool MyAddress::operator ==(int a)
{
	if(isnull)return true;
	return false;
}
#endif

#ifndef JAVA
bool MyAddress::operator !=(int a)
{
	if(isnull)return false;
	return true;
}
#endif


#ifdef JAVA
public int getType()
#else
int MyAddress::getType(void)
#endif
{
	return type;
}

#ifdef JAVA
public void clearType()
#else
void MyAddress::clearType(void)
#endif
{
	type=0;
}

#ifdef JAVA
public void setType(int t)
#else
void MyAddress::setType(int t)
#endif
{
	type=t;
}


#ifdef JAVA
public int getPort()
#else
int MyAddress::getPort(void)
#endif
{
	return port;
}

#ifdef JAVA
public void clearPort()
#else
void MyAddress::clearPort(void)
#endif
{
	port=0;
}

#ifdef JAVA
public void setPort(int t)
#else
void MyAddress::setPort(int t)
#endif
{
	port=t;
}



#ifdef JAVA
public int getLength()
#else
int MyAddress::getLength(void)
#endif
{
	return len;
}

#ifdef JAVA
public void clearLength()
#else
void MyAddress::clearLength(void)
#endif
{
	len=0;
}

#ifdef JAVA
public void setLength(int t)
#else
void MyAddress::setLength(int t)
#endif
{
	len=t;
}



#ifdef JAVA
public byte[] getAddress()
#else
char* MyAddress::getAddress(void)
#endif
{
#ifdef JAVA
	byte[] ret=null;
#else
	byte *ret=null;
#endif
	int i;

	ret=new byte[16];
	for(i=0;i<16;i++)ret[i]=address[i];
	return ret;
}

#ifdef JAVA
public void clearAddress()
#else
void MyAddress::clearAddress(void)
#endif
{
	int i;
	for(i=0;i<16;i++)address[i]=0;
}

#ifdef JAVA
public void setAddress(byte[]  a,int o,int s)
#else
void MyAddress::setAddress(char* a,int o,int s)
#endif
{
	int i;
	if(s<0 || s>=16)return;
	for(i=0;i<s;i++)address[i]=a[i+o];
}



#ifdef JAVA
}
#endif



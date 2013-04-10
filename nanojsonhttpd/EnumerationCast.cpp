/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String_.h"
#include "EnumerationCast.h"
#include "NetworkInterface.h"
#include "InetAddress.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#define null 0

EnumerationCast::EnumerationCast()
{
	m=NULL;
}

EnumerationCast::EnumerationCast(int id)
{
	m=NULL;
}

EnumerationCast::~EnumerationCast()
{
	if(m)free(m);
	m=NULL;
}

bool EnumerationCast::operator ==(int a)
{
	if(m==NULL && a==0)return true;
	return false;
}
bool EnumerationCast::operator !=(int a)
{
	if(m==NULL && a==0)return false;
	return true;
}

EnumerationCast::EnumerationCast(const EnumerationCast& f)
{
	int len=0;
	int sz;
	if(f.m==NULL){
		m=NULL;
		return;
	}
	len=(int)strlen((char*)(f.m));
	sz=len+1;
	m=malloc(sz);
	strncpy((char*)m,(char*)(f.m),sz);

}

EnumerationCast& EnumerationCast::operator =(char *f)
{
	int len=0;
	int sz;
	if(f==NULL){
		m=NULL;
		goto end;
		return *this;
	}
	if(m)free(m);
	len=(int)strlen(f);
	sz=len+1+16;
	m=malloc(sz);
	strncpy((char*)m,f,sz);
end:
	return *this;
}

EnumerationCast::operator String()
{
	String ret=null;
	if(m)ret=(char*)m;
	return ret;
}

EnumerationCast::operator NetworkInterface()
{
	NetworkInterface ret=null;
	if(m)ret=(char*)m;
	return ret;
}

EnumerationCast::operator InetAddress()
{
	InetAddress ret=null;
	if(m)ret=(char*)m;
	return ret;
}

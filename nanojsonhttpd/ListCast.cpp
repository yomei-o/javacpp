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
#include "ListCast.h"
#include "InterfaceAddress.h"

//#include "mylist.h"

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

ListCast::ListCast()
{
	m=NULL;
}

ListCast::ListCast(int id)
{
	m=NULL;
}

ListCast::~ListCast()
{
	if(m)free(m);
	m=NULL;
}

bool ListCast::operator ==(int a)
{
	if(m==NULL && a==0)return true;
	return false;
}
bool ListCast::operator !=(int a)
{
	if(m==NULL && a==0)return false;
	return true;
}

ListCast::ListCast(const ListCast& f)
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

ListCast& ListCast::operator =(char *f)
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

ListCast::operator String()
{
	String ret=null;
	if(m)ret=(char*)m;
	return ret;
}

ListCast::operator InterfaceAddress()
{
	InterfaceAddress ret=null;
	if(m)ret=(char*)m;
	return ret;
}

/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"
#include "Enumeration.h"

#include "myenum.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define print(a) printf("%s\n",a)

#define null 0
#define byte char
#define true 1
#define false 0

Enumeration::Enumeration()
{
	m=myenum_open();
}

Enumeration::Enumeration(int id)
{
	m=NULL;
}

Enumeration::~Enumeration()
{
	if(m)myenum_close((MYENUM*)m);
	m=NULL;
}

Enumeration::Enumeration(const Enumeration &f)
{
	m=myenum_dup((MYENUM*)(f.m));
}

Enumeration& Enumeration::operator =(Enumeration *f)
{
	if(f==NULL)goto end;

	m=myenum_dup((MYENUM*)(f->m));

	delete f;
end:
	return *this;
}
#if 0
Enumeration& Enumeration::operator =(Enumeration &f)
{
	if(m){
		myenum_close((MYENUM*)m);
		m=NULL;
	}
	m=myenum_dup((MYENUM*)(f.m));
	return *this;
}
#endif
Enumeration& Enumeration::operator =(Enumeration f)
{
	if(m){
		myenum_close((MYENUM*)m);
		m=NULL;
	}
	m=myenum_dup((MYENUM*)(f.m));
	return *this;
}

bool Enumeration::hasMoreElements()
{
	int ret;
	ret=myenum_hasmore((MYENUM*)m);
	return ret?true:false;
}

EnumerationCast Enumeration::nextElement()
{
	//String ret=null;
	EnumerationCast ret=null;
	char* p=null;
	p=myenum_next((MYENUM*)m);
	if(p){
		ret=p;
	}
	return ret;
}

void	Enumeration::add(String& s)
{
	char* p=null;
	if(s.equals(""))return;

	p=s.getBytes();
	myenum_add((MYENUM*)m,p);
}

void	Enumeration::add(char* s)
{
	if(s==NULL)return;
	myenum_add((MYENUM*)m,s);
}

bool Enumeration::operator ==(int a)
{
	if(m==NULL && a==0)return true;
	return false;
}

bool Enumeration::operator !=(int a)
{
	if(m==NULL && a==0)return false;
	return true;
}

#if 0

int main(){

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	Enumeration e=null;

	e=new Enumeration();
	e.add("000");
	e.add("111");
	e.add("222");

	while(e.hasMoreElements()){
		String s=null;
		s=(String)e.nextElement();
		printf(">>%s<<\n",(char*)s);
	}
	return 1;
}
#endif


/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/


#include "String_.h"
#include "Class.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define println(a) printf("%s\n",(char*)(a))

#define null 0
#define byte char
#define true 1
#define false 0

Class::Class()
{
	m_null=false;
	name="";
}

Class::Class(int id)
{
	if(id==0)m_null=true;
	name="";
}

Class::~Class()
{
}

Class& Class::operator =(Class *f)
{
	name="";
	if(f==NULL)goto end;
	m_null=f->m_null;
	name=f->name;
	delete f;
end:
	return *this;
}

bool Class::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}

bool Class::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}

Class::Class(const Class &f)
{
	m_null=f.m_null;
	name=f.name;
}


String Class::getName()
{
	String ret=null;
	ret=name;
	return ret;
}


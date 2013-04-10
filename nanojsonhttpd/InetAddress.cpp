/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"
#include "InetAddress.h"
#include "Class.h"
#include "strtag.h"


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


#define println(a) printf("%s\n",(char*)(a))

#define null 0
#define byte char
#define true 1
#define false 0

InetAddress::InetAddress()
{
	m_null=false;

	type=0;
	len=0;
	memset(address,0,16);
}

InetAddress::InetAddress(int id)
{
	m_null=true;
	type=0;
	len=0;
	memset(address,0,16);
}

InetAddress::~InetAddress()
{
}

#if 0
InetAddress& InetAddress::operator =(InetAddress& f)
{
	type=0;
	len=0;
	memset(address,0,16);
	m_null=true;

	m_null=f.m_null;
	type=f.type;
	len=f.len;
	memcpy(address,f.address,16);

	return *this;
}
#endif

InetAddress& InetAddress::operator =(InetAddress f)
{
	type=0;
	len=0;
	memset(address,16,0);
	m_null=true;

	m_null=f.m_null;
	type=f.type;
	len=f.len;
	memcpy(address,f.address,16);

	return *this;
}

InetAddress& InetAddress::operator =(InetAddress *f)
{
	type=0;
	len=0;
	memset(address,16,0);
	m_null=true;

	if(f==NULL)goto end;

	m_null=f->m_null;
	type=f->type;
	len=f->len;
	memcpy(address,f->address,16);
	delete f;
end:
	return *this;
}

bool InetAddress::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}

bool InetAddress::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}

InetAddress::InetAddress(const InetAddress &f)
{
	type=0;
	len=0;
	memset(address,16,0);
	m_null=true;

	m_null=f.m_null;
	type=f.type;
	len=f.len;
	memcpy(address,f.address,16);


}



InetAddress& InetAddress::operator =(char* f)
{
	char*p;

	type=0;
	len=0;
	memset(address,16,0);
	m_null=true;

	if(f==NULL)goto end;

	p=strtag_find(f,"<type");
	if(p)sscanf(p,"%d",&type);
	p=strtag_find(f,"<len");
	if(p)sscanf(p,"%d",&len);
	
	p=strtag_find(f,"<address");
	if(p && len>0 && len<=16)strtag_decode(p,address);

	m_null=false;
end:
	return *this;
}


char* InetAddress::getAddress(){
	char* ret=null;

	switch(type){
	case 1:
		ret=new char[16];
		memset(ret,0,16);
		memcpy(ret,address,4);
		break;
	case 2:
		ret=new char[16];
		memset(ret,0,16);
		memcpy(ret,address,16);
		break;
	default:
		break;
	}
	return ret;
}

Class InetAddress::getClass(){
	Class ret=null;
	ret=new Class();

	switch(type){
	case 1:
		ret.name="java.net.Inet4Address";
		break;
	case 2:
		ret.name="java.net.Inet6Address";
		break;
	default:
		ret.name="Object";
		break;
	}
	return ret;
}


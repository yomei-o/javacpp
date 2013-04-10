/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA

import java.io.*;
import java.lang.*;

#else 

#include "sock2_local.h"

#include "String_.h"
#include "DatagramPacket.h"
#include "InetSocketAddress.h"
#include "InetAddress.h"


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
DatagramPacket()
#else
DatagramPacket::DatagramPacket()
#endif
{
	isnull=false;
	host="";


	port=0;

	data=null;
	data_len=0;
	data_off=0;
}

#ifndef JAVA
DatagramPacket::DatagramPacket(int id)
{
	isnull=true;

	host=0;

	port=0;
	data=null;
	data_len=0;
	data_off=0;
}
#endif

#ifndef JAVA
DatagramPacket::DatagramPacket(char *d,int len)
{
	isnull=true;

	host="";

	port=0;
	data=d;
	data_len=len;
	data_off=0;
}
#endif

#ifndef JAVA
DatagramPacket::DatagramPacket(char *d,int off,int len)
{
	isnull=true;

	host=0;

	port=0;
	data=d;
	data_len=len;
	data_off=off;
}
#endif

#ifndef JAVA
DatagramPacket::~DatagramPacket()
{
}
#endif


#ifndef JAVA
DatagramPacket& DatagramPacket::operator =(DatagramPacket *f)
{
	if(f==NULL)goto end;
	isnull=f->isnull;
	port=f->port;

	host=f->host;
	data=f->data;
	data_len=f->data_len;
	data_off=f->data_off;

	delete f;
end:
	return *this;
}
#endif


#ifndef JAVA
bool DatagramPacket::operator ==(int a)
{
	if(isnull)return true;
	return false;
}
#endif

#ifndef JAVA
bool DatagramPacket::operator !=(int a)
{
	if(isnull)return false;
	return true;
}
#endif


#ifndef JAVA
void DatagramPacket::setPort(int p)
{
	port=p;
}
#endif

#ifndef JAVA
int DatagramPacket::getPort()
{
	return port;
}
#endif


#ifndef JAVA
void DatagramPacket::setSocketAddress(InetSocketAddress & ina)
{

	port=ina.port;
	host=ina.host;

}
#endif

#ifndef JAVA
InetSocketAddress DatagramPacket::getSocketAddress()
{
	InetSocketAddress ret=null;

	ret=new InetSocketAddress(host,port);
	return ret;
}
#endif

#ifndef JAVA
int DatagramPacket::getOffset()
{
	return data_off	;
}
#endif

#ifndef JAVA
int DatagramPacket::getLength()
{
	return data_len;
}
#endif


#ifndef JAVA
InetAddress DatagramPacket::getAddress()
{
	int t;

	InetAddress ret=null;
	if(port==0)goto end;
	if(host==null || host.equals(""))goto end;

	ret=new InetAddress();

	ret.type=1;
	ret.len=4;
	memset(ret.address,0,16);
	t=inet_addr(host);
	memcpy(ret.address,&t,4);
end:
	return ret;
}
#endif

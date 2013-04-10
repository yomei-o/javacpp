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

#include "String_.h"
#include "Socket2.h"
#include "InetSocketAddress.h"
#include "InetAddress.h"

#include "sock2_local.h"


#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/



#ifdef JAVA 
#define print(a) System.out.println(a)
#define printf System.out.printf
#else
#define print(a) printf("%s\n",a)
#endif

#ifdef JAVA 
#else
#define null NULL
#define byte char
#define true 1
#define false 0
#endif



// for Visual Studio 6 , Visual Studio 2002 ,Visual Studio 2003
#if defined(_MSC_VER) && (_MSC_VER<1700)
static int snprintf(char * buf,size_t n,const char *format,...)
{
	int ret;
	va_list ap;
    va_start(ap, format);
    ret = vsprintf(buf,format, ap);
    va_end(ap);
	return ret;
}
#endif


#ifdef JAVA
Socket2()
#else
Socket2::Socket2()
#endif
{
 	timeout=0;
	s=-1;
	isconnected=false;
	create=true;
}

#ifndef JAVA
Socket2::Socket2(int id)
{
	timeout=0;
	s=-1;
	isconnected=false;
	create=false;
}
#endif


#ifndef JAVA
Socket2::~Socket2()
{
	if(s!=-1)::closesocket(s);
	s=-1;
}
#endif




#ifndef JAVA
Socket2& Socket2::operator =(Socket2 *f)
{
	if(s!=-1){
		::closesocket(s);
		isconnected=false;
		create=false;
	}
	s=-1;

	if(f==NULL)goto end;
	if((f->s)!=-1){
		s=f->s;
		f->s=-1;
	}
	timeout=f->timeout;
	isconnected=f->isconnected;
	create=f->create;

	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
bool Socket2::operator ==(int id)
{
	if(id==0 && create==false)return true;
	return false;
}
#endif

#ifndef JAVA
bool Socket2::operator !=(int id)
{
	if(id==0 && create==false)return false;
	return true;
}
#endif


#ifndef JAVA
void Socket2::connect(InetSocketAddress& isa,int tt)
{
	struct addrinfo hints;
	struct addrinfo *ai0;
	struct addrinfo *ai;
	char cport[64];
	int ret;
	struct timeval tv;
	fd_set readfds;
	int n;

	snprintf(cport,sizeof(cport),"%d",isa.port);
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;

	ret=getaddrinfo((char*)(isa.host),cport,&hints,&ai0);
	if(ret){
		fprintf(stderr,"myssh client getaddrinfo error \n");
		return ;
	}
	for(ai=ai0;ai;ai=ai->ai_next){
		s = socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
		if(s==-1){
			fprintf(stderr,"myssh client create socket error \n");
		}
		if(s<0)continue;	
		if(timeout)internal_setSoTimeout(timeout);

		if(tt){
			winsock_asyncmode(s);
		}

		::connect(s,ai->ai_addr,(int)(ai->ai_addrlen));

		if(tt){
			FD_ZERO(&readfds);
			FD_SET(s, &readfds);
			memset(&tv,0,sizeof(tv));
			tv.tv_sec=tt/1000;
			tv.tv_usec=(tt%1000)*1000;

			n = select((int)(s+1),NULL, &readfds, NULL, &tv);
			if(n!=0)isconnected=true;
		}

		if(tt){
			winsock_syncmode(s);
		}

		if(n==0){
			fprintf(stderr,"myssh client connect error \n");
			::closesocket(s);
			s=-1;
			continue;
		}
		break;
	}
}
#endif


#ifndef JAVA
void Socket2::connect(InetSocketAddress& isa)
{
	struct addrinfo hints;
	struct addrinfo *ai0;
	struct addrinfo *ai;
	char cport[64];
	int ret;

	snprintf(cport,sizeof(cport),"%d",isa.port);
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;

	ret=getaddrinfo((char*)(isa.host),cport,&hints,&ai0);
	if(ret){
		fprintf(stderr,"myssh client getaddrinfo error \n");
		return ;
	}
	for(ai=ai0;ai;ai=ai->ai_next){
		s = socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
		if(s==-1){
			fprintf(stderr,"myssh client create socket error \n");
		}
		if(s<0)continue;	
		if(timeout)internal_setSoTimeout(timeout);

		ret=::connect(s,ai->ai_addr,(int)(ai->ai_addrlen));

		if(ret==-1){
			fprintf(stderr,"myssh client connect error \n");
			::closesocket(s);
			s=-1;
			continue;
		}
		break;
	}
	if(ret==0)isconnected=true;
}
#endif



#ifndef JAVA
void Socket2::close()
{
	SOCKET ss;
	ss=s;
	s=-1;
	if(ss!=-1)::closesocket(ss);
	create=false;
}
#endif

#ifndef JAVA
bool Socket2::isClosed()
{
	if(create==false)return true;
	return false;
}
#endif

#ifndef JAVA
bool Socket2::isConnected()
{
	return isconnected;
}
#endif


#ifndef JAVA
void Socket2::setSoTimeout(int tt)
{
	timeout=tt;
	if(s!=-1){
		internal_setSoTimeout(timeout);
	}
}
#endif

#ifndef JAVA
void Socket2::internal_setSoTimeout(int tt)
{
	int ret;

	struct timeval tv;
	tv.tv_sec  = tt/1000;
	tv.tv_usec = (tt%1000)*1000;

#ifdef _WIN32
	ret=setsockopt( s, SOL_SOCKET, SO_SNDTIMEO,(char*)&tt,(socklen_t) sizeof(tt));
#endif
#ifdef unix
	ret=setsockopt( s, SOL_SOCKET, SO_SNDTIMEO,(char*)&tv,(socklen_t) sizeof(tv));
#endif
	tv.tv_sec  = tt/1000;
	tv.tv_usec = (tt%1000)*1000;
#ifdef _WIN32
	ret=setsockopt( s, SOL_SOCKET, SO_RCVTIMEO,(char*)&tt,(socklen_t)sizeof(tt) );
#endif
#ifdef unix
	ret=setsockopt( s, SOL_SOCKET, SO_RCVTIMEO,(char*)&tv,(socklen_t)sizeof(tv) );
#endif

}
#endif


#ifndef JAVA
int Socket2::s_write(void* s,char* buf,int off ,int sz)
{
	int ret;
	int r=0;
	while(sz>0){
		ret=send((SOCKET)s,buf+off,sz,0);
		if(ret<0)break;
		off+=ret;
		sz-=ret;
		r+=ret;
	}
	if(r==0)return -1;
	return r;
}
#endif
#ifndef JAVA
int Socket2::s_read(void* s,char* buf,int off,int sz)
{
#if 0
	int ret,ret2;
	ret2=0;
	while(sz>0){
		ret=recv((SOCKET)s,buf+off,sz,0);
		if(ret<=0)break;
		off+=ret;
		sz-=ret;
		ret2+=ret;
	}
	return ret2;
#endif
#if 1
	int ret;
	ret=recv((SOCKET)s,buf+off,sz,0);
	return ret;
#endif
}
#endif


#ifndef JAVA
OutputStream Socket2::getOutputStream()
{
	OutputStream os;
	os.p_close=null;
	os.p_dup=null;
	os.p_write=s_write;
	os.p_open=null;
	os.p_flush=null;

	os.handle=(void*)s;

	return os;
}
#endif

#ifndef JAVA
InputStream Socket2::getInputStream()
{
	InputStream os;
	os.p_close=null;
	os.p_dup=null;
	os.p_read=s_read;
	os.p_open=null;
	os.p_reset=null;

	os.handle=(void*)s;

	return os;
}
#endif




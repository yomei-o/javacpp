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
#include "Socket.h"
//#include "Thread.h"
#include "InetSocketAddress.h"
#include "InetAddress.h"

#include "sock2_local.h"
#include "sockdup.h"


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

#endif /* JAVA*/



#ifdef JAVA 
#define println(a) System.out.println(a)
#define printf System.out.printf
#else
#define println(a) printf("%s\n",(char*)(a))
#endif

#ifdef JAVA 
#else
#define null 0
#define byte char
#define true 1
#define false 0
#endif





// for Visual Studio 6 , Visual Studio 2002 ,Visual Studio 2003
#ifndef JAVA
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
#endif



#ifdef JAVA
Socket()
#else
Socket::Socket()
#endif
{
 	timeout=0;
 	//s = socket(AF_INET, SOCK_STREAM, 0);
	s=-1;
//	printf("Socket() %08x\n",s);
}

#ifndef JAVA
Socket::Socket(int id)
{
	timeout=0;
	s=-1;

	local_address_type=0;
	local_address_len=0;
	memset(local_address,0,16);
	inet_address_type=0;
	inet_address_len=0;
	memset(inet_address,0,16);
}
#endif


#ifndef JAVA
Socket::Socket(const Socket & f)
{
	s=-1;
	if(f.s!=-1){
		s=dupsocket(f.s);

	local_address_type=f.local_address_type;
	local_address_len=f.local_address_len;
	memcpy(local_address,f.local_address,16);
	inet_address_type=f.inet_address_type;
	inet_address_len=f.inet_address_len;
	memcpy(inet_address,f.inet_address,16);

	}
	timeout=0;
}
#endif

#ifndef JAVA
Socket::~Socket()
{
//	printf("~Socket() %08x\n",s);
	if(s!=-1)::closesocket(s);
	s=-1;
}
#endif




#ifndef JAVA
Socket& Socket::operator =(Socket *f)
{
	if(s!=-1){
		::closesocket(s);
		//printf("closesocket %08x\n",s);
	}
	s=-1;

	local_address_type=0;
	local_address_len=0;
	memset(local_address,0,16);
	inet_address_type=0;
	inet_address_len=0;
	memset(inet_address,0,16);

	if(f==NULL)goto end;
	if((f->s)!=-1)s=dupsocket(f->s);
	timeout=f->timeout;

	local_address_type=f->local_address_type;
	local_address_len=f->local_address_len;
	memcpy(local_address,f->local_address,16);
	inet_address_type=f->inet_address_type;
	inet_address_len=f->inet_address_len;
	memcpy(inet_address,f->inet_address,16);

	//	printf("dupsocket() %08x\n",s);
	delete f;
end:
	return *this;
}
#endif

#if 0
Socket& Socket::operator =(Socket& f)
{
	if(s!=-1)closesocket(s);
	s=-1;

	local_address_type=0;
	local_address_len=0;
	memset(local_address,0,16);
	inet_address_type=0;
	inet_address_len=0;
	memset(inet_address,0,16);

	if(f.s!=-1)s=dupsocket(f.s);
	timeout=f.timeout;

	local_address_type=f.local_address_type;
	local_address_len=f.local_address_len;
	memcpy(local_address,f.local_address,16);
	inet_address_type=f.inet_address_type;
	inet_address_len=f.inet_address_len;
	memcpy(inet_address,f.inet_address,16);

	return *this;
}
#endif
#ifndef JAVA
Socket& Socket::operator =(Socket f)
{
	if(s!=-1)::closesocket(s);
	s=-1;

	local_address_type=0;
	local_address_len=0;
	memset(local_address,0,16);
	inet_address_type=0;
	inet_address_len=0;
	memset(inet_address,0,16);

	if(f.s!=-1)s=dupsocket(f.s);
	timeout=f.timeout;

	local_address_type=f.local_address_type;
	local_address_len=f.local_address_len;
	memcpy(local_address,f.local_address,16);
	inet_address_type=f.inet_address_type;
	inet_address_len=f.inet_address_len;
	memcpy(inet_address,f.inet_address,16);

	return *this;
}
#endif

#ifndef JAVA
bool Socket::operator ==(int id)
{
	if(id==0 && s==-1)return true;
	return false;
}
#endif

#ifndef JAVA
bool Socket::operator !=(int id)
{
	if(id==0 && s==-1)return false;
	return true;
}
#endif



#if 0
#ifndef JAVA
void Socket::connect(InetSocketAddress& isa)
{
	struct sockaddr_in dstAddr;
	int ret,n;
	struct timeval tv;
	fd_set readfds;
	struct hostent *he;

	memset(&dstAddr, 0, sizeof(dstAddr));
  	dstAddr.sin_port = htons(isa.port);
  	dstAddr.sin_family = AF_INET;
	dstAddr.sin_addr.s_addr = inet_addr((char*)(isa.host));
	if(dstAddr.sin_addr.s_addr==-1){
		he = gethostbyname((char*)(isa.host));
		if(he){
		dstAddr.sin_addr.s_addr=**(unsigned int **)(he->h_addr_list);
		}
	}
	if(timeout){
		FD_ZERO(&readfds);
		FD_SET(s, &readfds);

		memset(&tv,0,sizeof(tv));
		tv.tv_sec=timeout/1000;
		tv.tv_usec=(timeout%1000)*1000;

		n = select((int)(s+1),NULL, &readfds, NULL, &tv);
		if(n==0)return;
	}

	ret=::connect(s, (struct sockaddr *) &dstAddr, sizeof(dstAddr));
}
#endif
#endif


#ifndef JAVA
void Socket::close()
{
	SOCKET ss;
	ss=s;
	s=-1;
	if(ss!=-1)::closesocket(ss);
}
#endif

#ifndef JAVA
bool Socket::isClosed()
{
	if(s==-1)return true;
	return false;
}
#endif


#ifndef JAVA
void Socket::setSoTimeout(int tt)
{
	timeout=tt;
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
void* Socket::s_dup(void* s)
{
	if((SOCKET)s==-1)return (void*)-1;
	void* ret=(void*)dupsocket((SOCKET)s);
//	printf("dupsocket() %08x\n",ret);
	return ret;
}
#endif
#ifndef JAVA
void Socket::s_close(void*s)
{
	if((SOCKET)s==-1)return;
//	printf("closesocket() %08x\n",s);
	::closesocket((SOCKET)s);
}
#endif
#ifndef JAVA
int Socket::s_write(void* s,char* buf,int off ,int sz)
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
int Socket::s_read(void* s,char* buf,int off,int sz)
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
OutputStream Socket::getOutputStream()
{
	OutputStream os;
	os.p_close=s_close;
	os.p_dup=s_dup;
	os.p_write=s_write;
	os.p_open=null;
	os.p_flush=null;

	os.handle=s_dup((void*)s);

	return os;
}
#endif

#ifndef JAVA
InputStream Socket::getInputStream()
{
	InputStream os;
	os.p_close=s_close;
	os.p_dup=s_dup;
	os.p_read=s_read;
	os.p_open=null;
	os.p_reset=null;

	os.handle=s_dup((void*)s);

	return os;
}
#endif


#ifndef JAVA
InetAddress Socket::getInetAddress()
{
	char tmp[256];
	InetAddress ret=null;
	if(s==-1)return ret;

	tmp[0]=0;
	switch(inet_address_type){
	case 0:
		snprintf(tmp,256,"<type>%d</type>\n<len>%d</len>\n"
			"<address>%02x%02x%02x%02x</address>",inet_address_type,inet_address_len,
			inet_address[0]&255,inet_address[1]&255,
			inet_address[2]&255,inet_address[3]&255);
		break;
	case 1:
		snprintf(tmp,256,"<type>%d</type>\n<len>%d</len>\n"
			"<address>%02x%02x%02x%02x</address>",inet_address_type,inet_address_len,
			inet_address[0]&255,inet_address[1]&255,
			inet_address[2]&255,inet_address[3]&255);
		break;
	case 2:
		snprintf(tmp,256,"<type>%d</type>\n<len>%d</len>\n"
			"<address>%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x</address>",inet_address_type,inet_address_len,
			inet_address[0]&255,inet_address[1]&255,inet_address[2]&255,inet_address[3]&255,
			inet_address[4]&255,inet_address[5]&255,inet_address[6]&255,inet_address[7]&255,
			inet_address[8]&255,inet_address[9]&255,inet_address[10]&255,inet_address[11]&255,
			inet_address[12]&255,inet_address[13]&255,inet_address[14]&255,inet_address[15]&255);
		break;
	}
	ret=tmp;
	return ret;
}
#endif

#ifndef JAVA
InetAddress Socket::getLocalAddress()
{
	char tmp[256];
	InetAddress ret=null;
	if(s==-1)return ret;

	tmp[0]=0;
	switch(local_address_type){
	case 0:
		snprintf(tmp,256,"<type>%d</type>\n<len>%d</len>\n"
			"<address>%02x%02x%02x%02x</address>",local_address_type,local_address_len,
			local_address[0]&255,local_address[1]&255,
			local_address[2]&255,local_address[3]&255);
		break;
	case 1:
		snprintf(tmp,256,"<type>%d</type>\n<len>%d</len>\n"
			"<address>%02x%02x%02x%02x</address>",local_address_type,local_address_len,
			local_address[0]&255,local_address[1]&255,
			local_address[2]&255,local_address[3]&255);
		break;
	case 2:
		snprintf(tmp,256,"<type>%d</type>\n<len>%d</len>\n"
			"<address>%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x</address>",local_address_type,local_address_len,
			local_address[0]&255,local_address[1]&255,local_address[2]&255,local_address[3]&255,
			local_address[4]&255,local_address[5]&255,local_address[6]&255,local_address[7]&255,
			local_address[8]&255,local_address[9]&255,local_address[10]&255,local_address[11]&255,
			local_address[12]&255,local_address[13]&255,local_address[14]&255,local_address[15]&255);
		break;
	}


	ret=tmp;
	return ret;
}
#endif

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
#include "ServerSocket.h"
#include "Thread.h"
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
ServerSocket()
#else
ServerSocket::ServerSocket()
#endif
{
	timeout=-1;
  	s = -1;
  	s6 = -1;

	local_address_type=0;
	local_address_len=0;
	memset(local_address,0,sizeof(local_address));
}

#ifndef JAVA
ServerSocket::ServerSocket(int id)
{
	timeout=-1;
	s=-1;
	s6=-1;

	local_address_type=0;
	local_address_len=0;
	memset(local_address,0,sizeof(local_address));

	port=id;
	if(id<=0)return;

  	s = socket(AF_INET, SOCK_STREAM, 0);
  	s6 = socket(AF_INET6, SOCK_STREAM, 0);

	if(s==-1 && s6==-1)return;

	int ret,ret6;
	struct sockaddr_in srcAddr;
	struct sockaddr_in6 srcAddr6;
	struct in6_addr anyaddr = IN6ADDR_ANY_INIT; 


#ifdef IPV6_V6ONLY
	//fprintf(stderr,"setsockopt ipv6only kita!!\n");
	if (s6!=-1){
		int one=1;
		ret6=setsockopt(s6, IPPROTO_IPV6, IPV6_V6ONLY,(char *)&one, sizeof one);
		if(ret6==-1)fprintf(stderr,"setsockopt ipv6only error\n");
	}
#endif

	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(port);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(&srcAddr6, 0, sizeof(srcAddr6));
	srcAddr6.sin6_port =htons((unsigned short)port);
	srcAddr6.sin6_family = AF_INET6;
	srcAddr6.sin6_addr=anyaddr; 

	ret=-1;
	ret6=-1;
	if(s!=-1)ret=::bind(s,(struct sockaddr *)&srcAddr,sizeof(srcAddr));
	if(s6!=-1)ret6=::bind(s6,(struct sockaddr *)&srcAddr6,sizeof(srcAddr6));

	if(ret==-1 && ret6==-1){
		close();
		return;
	}

	ret=-1;
	ret6=-1;
	if(s!=-1)ret=::listen(s,20);
	if(s6!=-1)ret6=::listen(s6,20);

	if(ret==-1 && ret6==-1){
		close();
		return;
	}

	if(s!=-1){
		local_address_type=1;
		local_address_len=4;
		memcpy(local_address,&(srcAddr.sin_addr.s_addr),4);
	}else if(s6!=-1){
		local_address_type=2;
		local_address_len=16;
		memcpy(local_address,&(srcAddr6.sin6_addr),16);
	}
	//printf("OK listen\n");
}
#endif


#ifndef JAVA
ServerSocket::~ServerSocket()
{
	if(s!=-1)::closesocket(s);
	if(s6!=-1)::closesocket(s6);
	s=-1;
	s6=-1;
}
#endif




#ifndef JAVA
ServerSocket& ServerSocket::operator =(ServerSocket *f)
{
	if(s!=-1){
		::closesocket(s);
	}
	if(s6!=-1){
		::closesocket(s6);
	}
	s=-1;
	s6=-1;

	if(f==NULL)goto end;

	if((f->s)!=-1)s=dupsocket(f->s);
	if((f->s6)!=-1)s6=dupsocket(f->s6);
	timeout=f->timeout;

	local_address_type=f->local_address_type;
	local_address_len=f->local_address_len;
	memcpy(local_address,f->local_address,local_address_len);

	delete f;
end:
	return *this;
}
#endif

#if 0
ServerSocket& ServerSocket::operator =(ServerSocket &f)
{
	if(s!=-1){
		closesocket(s);
	}
	s=-1;

	if(f.s!=-1)s=dupsocket(f.s);
	timeout=f.timeout;

	local_address_type=f.local_address_type;
	local_address_len=f.local_address_len;
	memcpy(local_address,f.local_address,local_address_len);

	return *this;
}
#endif
#ifndef JAVA
ServerSocket& ServerSocket::operator =(ServerSocket f)
{
	if(s!=-1){
		::closesocket(s);
	}
	if(s6!=-1){
		::closesocket(s6);
	}
	s=-1;
	s6=-1;

	if(f.s!=-1)s=dupsocket(f.s);
	if(f.s6!=-1)s=dupsocket(f.s6);
	timeout=f.timeout;

	local_address_type=f.local_address_type;
	local_address_len=f.local_address_len;
	memcpy(local_address,f.local_address,local_address_len);

	return *this;
}
#endif


#ifndef JAVA
bool ServerSocket::operator ==(int id)
{
	if(id==0 && s==-1 && s6==-1)return true;
	return false;
}
#endif

#ifndef JAVA
bool ServerSocket::operator !=(int id)
{
	if(id==0 && s==-1 && s6==-1)return false;
	return true;
}
#endif


#ifndef JAVA
Socket ServerSocket::accept()
{
	Socket rets=null;
	SOCKET ss;
	struct sockaddr_storage srcAddr;
	int ret,n;
	fd_set readfds;
	struct timeval tv;

	if(s==-1 && s6==-1)return rets;

	FD_ZERO(&readfds);
		
	if(s!=-1)FD_SET(s, &readfds);
	if(s6!=-1)FD_SET(s6, &readfds);

	memset(&tv,0,sizeof(tv));
	tv.tv_sec=timeout/1000;
	tv.tv_usec=(timeout%1000)*1000;

	n = select(FD_SETSIZE, &readfds, NULL, NULL, &tv);
	if(n==0)return rets;

	memset(&srcAddr,0,sizeof(srcAddr));
	ret=sizeof(srcAddr);

	ss=-1;
	if(s!=-1 && FD_ISSET(s,&readfds)){
		ss=::accept(s,(struct sockaddr *)&srcAddr,(socklen_t*)&ret);
	}
	if(s6!=-1 && FD_ISSET(s6,&readfds)){
		ss=::accept(s6,(struct sockaddr *)&srcAddr,(socklen_t*)&ret);
	}

	if(ss!=-1 && srcAddr.ss_family==AF_INET){
		rets.local_address_type=local_address_type;
		rets.local_address_len=local_address_len;
		memcpy(rets.local_address,local_address,local_address_len);

		rets.inet_address_type=1;
		rets.inet_address_len=4;
		memcpy(rets.inet_address,&(((struct sockaddr_in*)&srcAddr)->sin_addr),4);
	
	}
	if(ss!=-1 && srcAddr.ss_family==AF_INET6){
		rets.local_address_type=local_address_type;
		rets.local_address_len=local_address_len;
		memcpy(rets.local_address,local_address,local_address_len);

		rets.inet_address_type=2;
		rets.inet_address_len=16;
		memcpy(rets.inet_address,&(((struct sockaddr_in6*)&srcAddr)->sin6_addr),16);
	
	}
	rets.s=ss;
	return rets;
}
#endif

#ifndef JAVA
void ServerSocket::close()
{
	SOCKET ss;
	SOCKET ss6;
	ss=s;
	ss6=s6;
	s=-1;
	s6=-1;
	if(ss!=-1){
		::closesocket(ss);
	}
	if(ss6!=-1){
		::closesocket(ss6);
	}
}
#endif

#ifndef JAVA
bool ServerSocket::isClosed()
{
	if(s==-1 && s6==-1)return true;
	return false;
}
#endif

#ifndef JAVA
void ServerSocket::setSoTimeout(int tt)
{
	timeout=tt;
/*
	struct timeval tv;
	int ret;
	memset(&tv,0,sizeof(tv));
	tv.tv_sec = timeout/1000;
	tv.tv_usec=(timeout%1000)*1000;
	ret=setsockopt(s, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(struct timeval));
	ret=setsockopt(s, SOL_SOCKET, SO_SNDTIMEO,(char *)&tv,sizeof(struct timeval));
	ret=setsockopt(s6, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(struct timeval));
	ret=setsockopt(s6, SOL_SOCKET, SO_SNDTIMEO,(char *)&tv,sizeof(struct timeval));
*/
}
#endif

#ifndef JAVA
InetAddress ServerSocket::getInetAddress()
{
	char tmp[256];
	InetAddress ret=null;
	if(s==-1 && s6==-1)return ret;

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

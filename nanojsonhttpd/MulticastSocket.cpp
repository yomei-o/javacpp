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
#include "MulticastSocket.h"
#include "InetSocketAddress.h"
#include "InetAddress.h"
#include "DatagramPacket.h"
#include "List.h"
#include "ListCast.h"
#include "InetAddress.h"
#include "InterfaceAddress.h"
#include "NetworkInterface.h"

#include "sock2_local.h"


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
MulticastSocket()
#else
MulticastSocket::MulticastSocket()
#endif
{
 	timeout=0;
	s=-1;
	isconnected=false;
	isbind=false;
	isauto=false;
}

#ifndef JAVA
MulticastSocket::MulticastSocket(int id)
{
	timeout=0;
	s=-1;
	isconnected=false;
	isbind=false;
	isauto=true;
}
#endif

#ifndef JAVA
MulticastSocket::MulticastSocket(const MulticastSocket& f)
{
	if(s!=-1){
		::closesocket(s);
		isconnected=false;
	}
	s=-1;

	if((f.s)!=-1){
		s=f.s;
		((MulticastSocket&)f).s=-1;
	}
	timeout=f.timeout;
	isconnected=f.isconnected;
	isbind=f.isbind;
	isauto=f.isauto;
}
#endif


#ifndef JAVA
MulticastSocket::~MulticastSocket()
{
	if(s!=-1)::closesocket(s);
	s=-1;
}
#endif




#ifndef JAVA
MulticastSocket& MulticastSocket::operator =(MulticastSocket *f)
{
	if(s!=-1){
		::closesocket(s);
		isconnected=false;
	}
	s=-1;

	if(f==NULL)goto end;
	if((f->s)!=-1){
		s=f->s;
		f->s=-1;
	}
	timeout=f->timeout;
	isconnected=f->isconnected;
	isbind=f->isbind;
	isauto=f->isauto;

	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
MulticastSocket& MulticastSocket::operator =(MulticastSocket f)
{
	if(s!=-1){
		::closesocket(s);
		isconnected=false;
	}
	s=-1;

	//if(f==NULL)goto end;
	if((f.s)!=-1){
		s=f.s;
		f.s=-1;
	}
	timeout=f.timeout;
	isconnected=f.isconnected;
	isbind=f.isbind;
	isauto=f.isauto;

	return *this;
}
#endif

#ifndef JAVA
bool MulticastSocket::operator ==(int id)
{
	if(id==0 && s==-1)return true;
	return false;
}
#endif

#ifndef JAVA
bool MulticastSocket::operator !=(int id)
{
	if(id==0 && s==-1)return false;
	return true;
}
#endif



#ifndef JAVA
bool MulticastSocket::isBound()
{
	return isbind;
}
#endif



#ifndef JAVA
void MulticastSocket::close()
{
	SOCKET ss;
	ss=s;
	s=-1;
	if(ss!=-1)::closesocket(ss);
	isauto=false;
}
#endif

#ifndef JAVA
bool MulticastSocket::isClosed()
{
	if(s==-1){
		if(isauto==false)return true;
	}
	return false;
}
#endif


#ifndef JAVA
void MulticastSocket::setSoTimeout(int tt)
{
	timeout=tt;
}
#endif


#ifndef JAVA
void MulticastSocket::setLoopbackMode(bool disable)
{
	int i;
	char a=1;

	autocreate();
	if(s==-1)return;

	if(disable)a=0;

#if defined(_WIN32) || defined(linux) || defined(__CYGWIN__)
	i=setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,(char *) &a,sizeof(a));
#else
#endif

}
#endif

#ifndef JAVA
bool MulticastSocket::getLoopbackMode()
{
	int i=0;
	char a=0;
	int sz=1;

	autocreate();
	if(s==-1)return false;

#if defined(_WIN32) || defined(linux) || defined(__CYGWIN__)
	i=getsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,(char *) &a,(socklen_t*)&sz);
#else
#endif
	if(i==-1)return false;
	if(a==1)return false;
	return true;
}
#endif


#ifndef JAVA
void MulticastSocket::bind(InetSocketAddress& isa)
{
	struct sockaddr_in dstAddr;
	//int ret;
	//struct hostent *he;
	autocreate();
	if(s==-1)return;

	if(isa.port==0)return;

	memset(&dstAddr, 0, sizeof(dstAddr));

	dstAddr.sin_family = AF_INET;
  	dstAddr.sin_port = htons(isa.port);
	if(isa.host!=null && !isa.host.equals("")){
		dstAddr.sin_addr.s_addr = inet_addr((char*)(isa.host));
	}
	//if(dstAddr.sin_addr.s_addr ==-1)dstAddr.sin_addr.s_addr =0;

	if (::bind(s, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) < 0) {
		return;
	}
	isbind=true;
}
#endif

#ifndef JAVA
void MulticastSocket::send(DatagramPacket& dp)
{
	struct sockaddr_in dstAddr;
	int ret;
	//struct hostent *he;

	autocreate();
	if(s==-1)return;
	if(dp.data==null || dp.data_len==0)return;
	if(dp.host==null || dp.host.equals(""))return;

	memset(&dstAddr, 0, sizeof(dstAddr));

	dstAddr.sin_family = AF_INET;
  	dstAddr.sin_port = htons(dp.port);
	dstAddr.sin_addr.s_addr = inet_addr((char*)(dp.host));
	ret=::sendto(s,dp.data+dp.data_off,dp.data_len,0,(struct sockaddr*)&dstAddr,sizeof(dstAddr));
}
#endif

#ifndef JAVA
void MulticastSocket::receive(DatagramPacket& dp)
{
	struct sockaddr_in dstAddr;
	int ret;
	//struct hostent *he;
	int dlen=0;

	struct timeval tv;
	fd_set readfds;
	int n;

	autocreate();
	if(s==-1)return;

	memset(&dstAddr, 0, sizeof(dstAddr));
	dlen=sizeof(dstAddr);

	if(timeout){
		FD_ZERO(&readfds);
		FD_SET(s, &readfds);

		memset(&tv,0,sizeof(tv));
		tv.tv_sec=timeout/1000;
		tv.tv_usec=(timeout%1000)*1000;

		n = select((int)(s+1),&readfds,NULL, NULL, &tv);
		if(n==0)return;
	}

	ret=::recvfrom(s,dp.data+dp.data_off,dp.data_len,0,(struct sockaddr*)&dstAddr,(socklen_t*)&dlen);
	if(ret<=0)return;
	dp.data_len=ret;

	dp.port=ntohs(dstAddr.sin_port);
	dp.host=inet_ntoa(dstAddr.sin_addr);

}
#endif

#ifndef JAVA
void MulticastSocket::autocreate()
{
	if(isauto==false)return;
	isauto=false;
	 s = socket(AF_INET, SOCK_DGRAM, 0);
	 if(s==-1)return;
	 setReuseAddress(true);
}
#endif

#ifndef JAVA
void MulticastSocket::setReuseAddress(bool a)
{
	int on;
	int ret;
	autocreate();
	if(s==-1)return;

	on=1;
	if(a==false)on=0;
	ret=setsockopt(s,SOL_SOCKET,SO_REUSEADDR ,(char *) &on,sizeof(on));
}
#endif

#ifndef JAVA
bool MulticastSocket::getReuseAddress()
{
	int on=0;
	int sz;
	int ret;

	autocreate();
	if(s==-1)return false;

	sz=sizeof(on);
	ret=getsockopt(s,SOL_SOCKET,SO_REUSEADDR ,(char *) &on,(socklen_t *)&sz);
	if(ret==-1)return false;

	if(on==1)return true;
	return false;
}
#endif


#ifndef JAVA
void MulticastSocket::joinGroup(InetSocketAddress& isa,NetworkInterface & nif)
{
	int addr1=0,addr2=0;
	List li=null;
	InterfaceAddress ifa=null;
	int i;
	int sz=0;
	struct  ip_mreq mreq;

	autocreate();
	if(s==-1)return;

	addr1=inet_addr(isa.host);

	li=nif.getInterfaceAddresses();
	sz=li.size();
	for(i=0;i<sz;i++){
		InetAddress ina=null;
		ifa=(InterfaceAddress)(li.get(i));
		ina=ifa.getAddress();
		if(ina.type==1)
		{
			char buf[128];
			buf[0]=0;
			snprintf(buf,128,"%d.%d.%d.%d",ina.address[0]&255,ina.address[1]&255,
				ina.address[2]&255,ina.address[3]&255);
			addr2=inet_addr(buf);
			break;
		}
	}
	if(addr1==0 || addr1==-1)return;
	if(addr2==0 || addr2==-1)return;
	mreq.imr_interface.s_addr = addr2;
	mreq.imr_multiaddr.s_addr = addr1;
#if defined(_WIN32) || defined(linux) || defined(__CYGWIN__)
	i=setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *) &mreq,sizeof(struct ip_mreq));
	//i=setsockopt(s,IPPROTO_IP,IP_DROP_MEMBERSHIP,(char *) &mreq,sizeof(struct ip_mreq));
#else
#endif

}
#endif

#ifndef JAVA
void MulticastSocket::leaveGroup(InetSocketAddress& isa,NetworkInterface & nif)
{
	int addr1=0,addr2=0;
	List li=null;
	InterfaceAddress ifa=null;
	int i;
	int sz=0;
	struct  ip_mreq mreq;

	autocreate();
	if(s==-1)return;

	addr1=inet_addr(isa.host);

	li=nif.getInterfaceAddresses();
	sz=li.size();
	for(i=0;i<sz;i++){
		InetAddress ina=null;
		ifa=(InterfaceAddress)(li.get(i));
		ina=ifa.getAddress();
		if(ina.type==1)
		{
			char buf[128];
			buf[0]=0;
			snprintf(buf,128,"%d.%d.%d.%d",ina.address[0]&255,ina.address[1]&255,
				ina.address[2]&255,ina.address[3]&255);
			addr2=inet_addr(buf);
			break;
		}
	}
	if(addr1==0 || addr1==-1)return;
	if(addr2==0 || addr2==-1)return;
	mreq.imr_interface.s_addr = addr2;
	mreq.imr_multiaddr.s_addr = addr1;
#if defined(_WIN32) || defined(linux) || defined(__CYGWIN__)
	//i=setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *) &mreq,sizeof(struct ip_mreq));
	i=setsockopt(s,IPPROTO_IP,IP_DROP_MEMBERSHIP,(char *) &mreq,sizeof(struct ip_mreq));
#else
#endif	
}
#endif



#ifndef JAVA
void MulticastSocket::setTimeToLive(int ttl)
{
	int ret;

	autocreate();
	if(s==-1)return;

	ret=setsockopt(s,IPPROTO_IP,IP_MULTICAST_TTL,(char *)&ttl,sizeof(ttl));
}
#endif

#ifndef JAVA
int MulticastSocket::getTimeToLive()
{
	int ret=0;
	int ttl=0;
	int sz=0;

	autocreate();
	if(s==-1)return -1;

	sz=sizeof(ttl);
	ret=getsockopt(s,IPPROTO_IP,IP_MULTICAST_TTL,(char *)&ttl,(socklen_t*)&sz);
	if(ret==-1)return -1;
	return ttl;
}
#endif


#ifndef JAVA
void MulticastSocket::setReceiveBufferSize(int sz)
{
	int ret;

	autocreate();
	if(s==-1)return;
	ret = setsockopt(s, SOL_SOCKET, SO_RCVBUF,(char *)&sz, sizeof(sz) );

}
#endif

#ifndef JAVA
int MulticastSocket::getReceiveBufferSize()
{
	int ret=0;
	int sz=0;
	int szsz=0;

	szsz=sizeof(sz);

	autocreate();
	if(s==-1)return -1;
	ret = getsockopt(s, SOL_SOCKET, SO_RCVBUF,(char *)&sz,(socklen_t*)&szsz);
	if(ret==-1)return -1;
	return sz;
}
#endif



#ifndef JAVA
void MulticastSocket::setSendBufferSize(int sz)
{
	int ret;

	autocreate();
	if(s==-1)return;
	ret = setsockopt(s, SOL_SOCKET, SO_SNDBUF,(char *)&sz, sizeof(sz) );

}
#endif

#ifndef JAVA
int MulticastSocket::getSendBufferSize()
{
	int ret=0;
	int sz=0;
	int szsz=0;

	szsz=sizeof(sz);

	autocreate();
	if(s==-1)return -1;
	ret = getsockopt(s, SOL_SOCKET, SO_SNDBUF,(char *)&sz,(socklen_t*)&szsz);
	if(ret==-1)return -1;
	return sz;
}
#endif


#ifndef JAVA
void MulticastSocket::setNetworkInterface(NetworkInterface & nif)
{
	int ret;
	int addr1=0;
	int sz;
	int i;
	List li=null;
	InterfaceAddress ifa=null;

	li=nif.getInterfaceAddresses();
	sz=li.size();
	for(i=0;i<sz;i++){
		InetAddress ina=null;
		ifa=(InterfaceAddress)(li.get(i));
		ina=ifa.getAddress();
		if(ina.type==1)
		{
			char buf[128];
			buf[0]=0;
			snprintf(buf,128,"%d.%d.%d.%d",ina.address[0]&255,ina.address[1]&255,
				ina.address[2]&255,ina.address[3]&255);
			addr1=inet_addr(buf);
			break;
		}
	}
	if(addr1==0 || addr1==-1)return;

	ret=setsockopt(s,IPPROTO_IP,IP_MULTICAST_IF,(char *)&addr1, sizeof(addr1));
}
#endif


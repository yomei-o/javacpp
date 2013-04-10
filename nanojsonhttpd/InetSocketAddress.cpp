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
#include "InetSocketAddress.h"
#include "InetAddress.h"
//#include "Thread.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


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


#ifndef JAVA 
#define IN6ADDRSZ       16
#define INADDRSZ         4
#define INT16SZ          2
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


#ifndef JAVA
static int inet_pton4(const char *src, unsigned char *dst)
{
  static const char digits[] = "0123456789";
  int saw_digit, octets, ch;
  unsigned char tmp[INADDRSZ], *tp;

  saw_digit = 0;
  octets = 0;
  tp = tmp;
  *tp = 0;
  while ((ch = *src++) != '\0') {
    const char *pch;

    if ((pch = strchr(digits, ch)) != NULL) {
      unsigned int val = *tp * 10 + (unsigned int)(pch - digits);

      if (val > 255)
        return (0);
      *tp = (unsigned char)val;
      if (! saw_digit) {
        if (++octets > 4)
          return (0);
        saw_digit = 1;
      }
    } else if (ch == '.' && saw_digit) {
      if (octets == 4)
        return (0);
      *++tp = 0;
      saw_digit = 0;
    } else
      return (0);
  }
  if (octets < 4)
    return (0);
  /* bcopy(tmp, dst, INADDRSZ); */
  memcpy(dst, tmp, INADDRSZ);
  return (1);
}
#endif

#ifndef JAVA
static int
inet_pton6(const char *src, unsigned char *dst)
{
  static const char xdigits_l[] = "0123456789abcdef",
    xdigits_u[] = "0123456789ABCDEF";
  unsigned char tmp[IN6ADDRSZ], *tp, *endp, *colonp;
  const char *xdigits, *curtok;
  int ch, saw_xdigit;
  unsigned int val;

  memset((tp = tmp), 0, IN6ADDRSZ);
  endp = tp + IN6ADDRSZ;
  colonp = NULL;
  /* Leading :: requires some special handling. */
  if (*src == ':')
    if (*++src != ':')
      return (0);
  curtok = src;
  saw_xdigit = 0;
  val = 0;
  while ((ch = *src++) != '\0') {
    const char *pch;

    if ((pch = strchr((xdigits = xdigits_l), ch)) == NULL)
      pch = strchr((xdigits = xdigits_u), ch);
    if (pch != NULL) {
      val <<= 4;
      val |= (pch - xdigits);
      if (val > 0xffff)
        return (0);
      saw_xdigit = 1;
      continue;
    }
    if (ch == ':') {
      curtok = src;
      if (!saw_xdigit) {
        if (colonp)
          return (0);
        colonp = tp;
        continue;
      }
      if (tp + INT16SZ > endp)
        return (0);
      *tp++ = (unsigned char) (val >> 8) & 0xff;
      *tp++ = (unsigned char) val & 0xff;
      saw_xdigit = 0;
      val = 0;
      continue;
    }
    if (ch == '.' && ((tp + INADDRSZ) <= endp) &&
        inet_pton4(curtok, tp) > 0) {
      tp += INADDRSZ;
      saw_xdigit = 0;
      break;    /* '\0' was seen by inet_pton4(). */
    }
    return (0);
  }
  if (saw_xdigit) {
    if (tp + INT16SZ > endp)
      return (0);
    *tp++ = (unsigned char) (val >> 8) & 0xff;
    *tp++ = (unsigned char) val & 0xff;
  }
  if (colonp != NULL) {
    /*
     * Since some memmove()'s erroneously fail to handle
     * overlapping regions, we'll do the shift by hand.
     */
    const int n = (int)(tp - colonp);
    int i;

    for (i = 1; i <= n; i++) {
      endp[- i] = colonp[n - i];
      colonp[n - i] = 0;
    }
    tp = endp;
  }
  if (tp != endp)
    return (0);
  /* bcopy(tmp, dst, IN6ADDRSZ); */
  memcpy(dst, tmp, IN6ADDRSZ);
  return (1);
}
#endif

#ifndef JAVA
static int my_inet_pton(int af, const char *src, void *dst)
{
  switch (af) {
  case AF_INET:
    return (inet_pton4(src, (unsigned char *)dst));
  case AF_INET6:
    return (inet_pton6(src, (unsigned char *)dst));
  default:
    return (-1);
  }
}
#endif



#ifdef JAVA
InetSocketAddress()
#else
InetSocketAddress::InetSocketAddress()
#endif
{
	host="";
	port=0;
}

#ifndef JAVA
InetSocketAddress::InetSocketAddress(int id)
{
	host="";
	port=id;
}
#endif

#ifndef JAVA
InetSocketAddress::InetSocketAddress(String & ho,int po)
{
	host=ho;
	port=po;
}
#endif

#ifndef JAVA
InetSocketAddress::InetSocketAddress(char* ho,int po)
{
	host=new String(ho);
	port=po;
}
#endif

#ifndef JAVA
InetSocketAddress::InetSocketAddress(InetAddress& ia,int po)
{
	char buf[256];
	buf[0]=0;
	switch(ia.type){
	case 1:
		snprintf(buf,256,"%d.%d.%d.%d",ia.address[0]& 255,
			ia.address[1]& 255,ia.address[2]& 255,ia.address[3]& 255);
		host=buf;
		break;
	case 2:
		snprintf(buf,256,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
			ia.address[0]& 255,ia.address[1]& 255,ia.address[2]& 255,ia.address[3]& 255,
			ia.address[4]& 255,ia.address[5]& 255,ia.address[6]& 255,ia.address[7]& 255,
			ia.address[8]& 255,ia.address[9]& 255,ia.address[10]& 255,ia.address[11]& 255,
			ia.address[12]& 255,ia.address[13]& 255,ia.address[14]& 255,ia.address[15]& 255);
		host=buf;
		break;
	}
	port=po;
}
#endif


#ifndef JAVA
InetSocketAddress::~InetSocketAddress()
{
}
#endif


#ifndef JAVA
InetSocketAddress& InetSocketAddress::operator =(InetSocketAddress *f)
{
	if(f==NULL)goto end;

	host=f->host;
	port=f->port;

	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
InetAddress InetSocketAddress::getAddress()
{
	int t;
	struct sockaddr_in6 addr;

	InetAddress ret;
	if(port==0)goto end;
	if(host==null || host.equals(""))goto end;

	if(strstr((char*)host,":")){
		ret.type=2;
		ret.len=16;
		memset(ret.address,0,16);
		memset(&addr,0,sizeof(struct sockaddr_in6));
		my_inet_pton(AF_INET6,host,&addr.sin6_addr);
		memcpy(ret.address,&addr.sin6_addr,16);

	}else{
		ret.type=1;
		ret.len=4;
		memset(ret.address,0,16);
		t=inet_addr(host);
		memcpy(ret.address,&t,4);
	}
end:
	return ret;
}
#endif



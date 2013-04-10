/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/


#ifdef JAVA
//  JAVA packagename
package com.yomei.myhttpd;
//  JAVA imports
#endif

#ifndef JAVA
#include "String_.h"
#include "BinaryUtil.h"
#endif


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define print(a) printf("%s\n",(char*)(a))

#ifndef JAVA
#define null 0
#define byte char
#define true 1
#define false 0
#endif


#ifdef JAVA
public class BinaryUtil{
#endif

#ifdef JAVA
BinaryUtil()
#else
BinaryUtil::BinaryUtil()
#endif
{
#ifndef JAVA
	m_null=false;
#endif
}

#ifndef JAVA
BinaryUtil::BinaryUtil(int id)
{
	if(id==0)m_null=true;
}
#endif

#ifndef JAVA
BinaryUtil::~BinaryUtil()
{
}
#endif

#ifndef JAVA
class BinaryUtil& BinaryUtil::operator =(class BinaryUtil *f)
{
	if(f==NULL)goto end;
	m_null=f->m_null;
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
bool BinaryUtil::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif


#ifndef JAVA
bool BinaryUtil::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif

#ifndef JAVA
BinaryUtil::BinaryUtil(const class BinaryUtil &f)
{
	m_null=f.m_null;
}
#endif


#ifndef JAVA
int  BinaryUtil::indexOf(byte* s,int soff,int slen,byte* d)
{
	String str=null;
	if(d==null)return -1;
	str=d;
	return indexOf(s,soff,slen,str);
}
#endif
#ifndef JAVA
int  BinaryUtil::lastIndexOf(byte* s,int soff,int slen,byte* d)
{
	String str=null;
	if(d==null)return -1;
	str=d;
	return lastIndexOf(s,soff,slen,str);
}
#endif
#ifndef JAVA
int  BinaryUtil::partOf(byte* s,int soff,int slen,byte* d)
{
	String str=null;
	if(d==null)return -1;
	str=d;
	return partOf(s,soff,slen,str);
}
#endif

#ifndef JAVA
int  BinaryUtil::nokori(byte* s,int soff,int slen,byte* d)
{
	String str=null;
	if(d==null)return -1;
	str=d;
	return nokori(s,soff,slen,str);
}
#endif


#ifdef JAVA
public static int indexOf(byte[] s,int soff,int slen,String str)
#else
int  BinaryUtil::indexOf(byte* s,int soff,int slen,String& str)
#endif
{
	int len=0;
	len=str.length();
#ifdef JAVA
	byte[] d=null;
#else
	byte* d=null;
#endif
	if(str==null)return -1;
	if(len<=0)return -1;
#ifdef JAVA
	try{
#endif
	d=str.getBytes("utf-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(d==null)return -1;
	return indexOf(s,soff,slen,d,0,len);
}

#ifdef JAVA
public static int lastIndexOf(byte[] s,int soff,int slen,String str)
#else
int  BinaryUtil::lastIndexOf(byte* s,int soff,int slen,String& str)
#endif
{
	int len=0;
	len=str.length();
#ifdef JAVA
	byte[] d=null;
#else
	byte* d=null;
#endif
	if(str==null)return -1;
	if(len<=0)return -1;
#ifdef JAVA
	try{
#endif
	d=str.getBytes("utf-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(d==null)return -1;
	return lastIndexOf(s,soff,slen,d,0,len);
}


#ifdef JAVA
public static int partOf(byte[] s,int soff,int slen,String str)
#else
int  BinaryUtil::partOf(byte* s,int soff,int slen,String& str)
#endif
{
	int len=0;
	len=str.length();
#ifdef JAVA
	byte[] d=null;
#else
	byte* d=null;
#endif
	if(str==null)return -1;
	if(len<=0)return -1;
#ifdef JAVA
	try{
#endif
	d=str.getBytes("utf-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(d==null)return -1;
	return partOf(s,soff,slen,d,0,len);
}



#ifdef JAVA
public static int nokori(byte[] s,int soff,int slen,String str)
#else
int  BinaryUtil::nokori(byte* s,int soff,int slen,String& str)
#endif
{
	int len=0;
	len=str.length();
#ifdef JAVA
	byte[] d=null;
#else
	byte* d=null;
#endif
	if(str==null)return -1;
	if(len<=0)return -1;
#ifdef JAVA
	try{
#endif
	d=str.getBytes("utf-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(d==null)return -1;
	return nokori(s,soff,slen,d,0,len);
}


#ifdef JAVA
public static int indexOf(byte[] s,int soff,int slen,byte[] d,int doff,int dlen)
#else
int  BinaryUtil::indexOf(byte* s,int soff,int slen,byte* d,int doff,int dlen)
#endif
{
	int ret=-1;
	int i,j,f=0,ct;

	if(s==null || d==null)return ret;
	if(soff<0 || doff<0)return ret;
	if(slen<=0 || dlen<=0)return ret;
	if(slen<dlen)return ret;

	ct=slen-dlen+1;
	for(i=0;i<ct;i++){
		f=1;
		for(j=0;j<dlen;j++)if(s[soff+i+j]!=d[doff+j]){
			f=0;
			break;
		}
		if(f==1){
			return soff+i;
		}
	}
	return ret;
}


#ifdef JAVA
public static int lastIndexOf(byte[] s,int soff,int slen,byte[] d,int doff,int dlen)
#else
int  BinaryUtil::lastIndexOf(byte* s,int soff,int slen,byte* d,int doff,int dlen)
#endif
{
	int ret=-1;
	int i,j,f=0,ct;

	if(s==null || d==null)return ret;
	if(soff<0 || doff<0)return ret;
	if(slen<=0 || dlen<=0)return ret;
	if(slen<dlen)return ret;

	ct=slen-dlen+1;
	for(i=ct-1;i>=0;i--){
		f=1;
		for(j=0;j<dlen;j++)if(s[soff+i+j]!=d[doff+j]){
			f=0;
			break;
		}
		if(f==1){
			return soff+i;
		}
	}
	return ret;
}


#ifdef JAVA
public static int partOf(byte[] s,int soff,int slen,byte[] d,int doff,int dlen)
#else
int  BinaryUtil::partOf(byte* s,int soff,int slen,byte* d,int doff,int dlen)
#endif
{
	int ret=-1;
	int i,j,f=0,ct;

	if(s==null || d==null)return ret;
	if(soff<0 || doff<0)return ret;
	if(slen<=0 || dlen<=0)return ret;
	if(slen<dlen)return ret;

	ct=slen-dlen+1;
	for(i=dlen-1;i>=0;i--){
		f=1;
		
		for(j=0;j<i+1;j++)if(s[soff+slen-1-i+j]!=d[doff+j]){
			f=0;
			break;
		}
		if(f==1){
			return soff+slen-1-i;
		}
	}
	return ret;
}

#ifdef JAVA
public static int nokori(byte[] s,int soff,int slen,byte[] d,int doff,int dlen)
#else
int  BinaryUtil::nokori(byte* s,int soff,int slen,byte* d,int doff,int dlen)
#endif
{
	int idx=0;
	idx=partOf(s,soff,slen,d,doff,dlen);
	if(idx==-1)return 0;
	return slen-idx;
}


#ifdef JAVA
public static String readLine(byte[] s,int soff,int slen)
#else
String BinaryUtil::readLine(byte* s,int soff,int slen)
#endif
{
	int i;
	String ret=null;
	if(s==null || soff<0 || slen<=0)return ret;
	i=indexOf(s,soff,slen,"\n");
	if(i==-1){
#ifdef JAVA
		try{
#endif
		ret=new String(s,soff,slen,"utf-8");
#ifdef JAVA
		}catch(Exception e){}
#endif
		ret=ret.trim();
		return ret;
	}
#ifdef JAVA
	try{
#endif
	ret=new String(s,soff,i-soff,"utf-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(ret==null)return ret;
	ret=ret.trim();
	return ret;
}

#ifdef JAVA
public static int getLineSize(byte[] s,int soff,int slen)
#else
int BinaryUtil::getLineSize(byte* s,int soff,int slen)
#endif
{
	int ret=-1;
	int i;
	if(s==null || soff<0 || slen<=0)return ret;
	i=indexOf(s,soff,slen,"\n");
	if(i==-1){
		return slen;
	}
	return i;
}




#ifdef JAVA
}
#endif


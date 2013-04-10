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
import java.io.*;

#endif

#ifndef JAVA
#include "String_.h"
#include "InputUtil.h"
#include "InputStream.h"
#include "BinaryUtil.h"
#endif


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef JAVA
#define println(a) System.out.println(a)
#else
#define println(a) printf("%s\n",(char*)(a))
#endif

#ifndef JAVA
#define null 0
#define byte char
#define true 1
#define false 0
#endif


#ifdef JAVA
public class InputUtil{
#endif

#ifdef JAVA
	byte[] data=null;
	int len=0;
	int read_size=0;
#endif


#ifdef JAVA
InputUtil()
#else
InputUtil::InputUtil()
#endif
{
#ifndef JAVA
	m_null=false;
	data=null;
	len=0;
	read_size=0;
#endif
}

#ifndef JAVA
InputUtil::InputUtil(int id)
{
	if(id==0)m_null=true;
	data=null;
	len=0;
	read_size=0;
}
#endif

#ifndef JAVA
InputUtil::~InputUtil()
{
	if(data)delete[] data;
}
#endif

#ifndef JAVA
class InputUtil& InputUtil::operator =(class InputUtil *f)
{
	if(f==NULL)goto end;
	m_null=f->m_null;
	data=f->data;
	f->data=null;
	len=f->len;
	f->len=0;
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
bool InputUtil::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif


#ifndef JAVA
bool InputUtil::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif

#ifndef JAVA
InputUtil::InputUtil(const class InputUtil &f)
{
	m_null=f.m_null;
	data=f.data;
	len=f.len;
	//f.data=null;
	((class InputUtil&)f).data=null;
	((class InputUtil&)f).len=0;
}
#endif



#ifdef JAVA
public void unread(byte[] s,int soff,int slen,int nokori)
#else
void InputUtil::unread(byte* s,int soff,int slen,int nokori)
#endif
{
	int i;
	if(nokori==0)return;
	if(data!=null)return;
	if(s==null || soff<0 || slen<=0)return;
	data=new byte[nokori];
	for(i=0;i<nokori;i++){
		data[i]=s[soff+slen-nokori+i];
	}
	len=nokori;
}

#ifdef JAVA
public int read(InputStream is,byte[] s,int soff,int slen)
#else
int InputUtil::read(InputStream& is,byte* s,int soff,int slen)
#endif
{
	int i;
	int ret=-1;
	if(data!=null){
		if(slen<len)return ret;
		for(i=0;i<len;i++){
			s[soff+i]=data[i];
		}
		soff+=len;
		slen-=len;
		ret=len;
#ifndef JAVA
		delete[] data;
#endif
		data=null;
		len=0;

	}
	if(slen==0)return ret;
	while(slen>0){
		i=-1;
#ifdef JAVA
		try{
#endif
		i=is.read(s,soff,slen);
//		i=is.read(s,0,10);
//		break;
#ifdef JAVA
		}catch(Exception e){}
#endif
		if(i<=0)break;

		soff+=i;
		slen-=i;
		if(ret==-1)ret=0;
		ret+=i;
	}
#ifdef JAVA
//	String sss=null;
//	try{
//	sss=new String(s,0,10,"utf-8");
//	}catch(Exception e){}
//	println("sss="+sss);
#endif
	return ret;
}

#ifdef JAVA
public int getReadSize()
#else
int InputUtil::getReadSize()
#endif
{
	return read_size;
}

#ifdef JAVA
public String readLine(InputStream is,byte[] b,int off,int len)
#else
String InputUtil::readLine(InputStream& is,byte* b,int off,int len)
#endif
{
	int i,l;
	String ret=null;
	read_size=0;

	l=read(is,b,off,len);
	if(l<=0)return ret;
	i=BinaryUtil.indexOf(b,off,l,"\n");
	if(i==-1){
		unread(b,off,l,l);
		return ret;
	}
	i++;
	read_size=i;
	unread(b,off,l,l-i);
#ifdef JAVA
	try{
#endif
	ret=new String(b,0,i,"utf-8");
	ret=ret.trim();
#ifdef JAVA
	}catch(Exception e){}
#endif
	return ret;
}


#ifdef JAVA
}
#endif


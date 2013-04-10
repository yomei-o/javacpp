#ifdef JAVA

package com.yomei.myssdp;
import java.io.*;
import java.lang.*;

#else 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyListener.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif


#ifndef JAVA
#define null 0
#define byte char
#define true 1
#define false 0
#endif

#ifdef JAVA 
#define print(a) System.out.println(a)
#define printf System.out.printf
#else
#define print(a) printf("%s\n",(char*)(a))
#endif


#ifdef JAVA
public class MyListener implements TestListener{
#endif

#ifdef JAVA
int id;
#endif

#ifdef JAVA
public MyListener()
#else
MyListener::MyListener()
#endif
{
#ifndef JAVA
	v_const();
	m_null=false;
#endif
}

#ifndef JAVA
MyListener::MyListener(int id)
{
	v_const();
}
#endif

#ifndef JAVA
MyListener::MyListener(const MyListener &f)
{
	v_const();
	m_null=true;

	tl=f.tl;
	((MyListener&)f).tl=NULL;
	if(tl && tl->m_null==false)m_null=false;
}
#endif

#ifndef JAVA
MyListener::~MyListener()
{
	v_dest();
}
#endif

#ifndef JAVA
void MyListener::v_const()
{
	m_null=true;
}
#endif

#ifndef JAVA
void MyListener::v_dest()
{
}
#endif


#ifndef JAVA
MyListener& MyListener::operator =(MyListener *f)
{
	v_const();
	tl=f;
	if(f)m_null=false;
	return *this;


}
#endif

#ifndef JAVA
bool MyListener::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif

#ifndef JAVA
bool MyListener::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif


#ifdef JAVA
public void onTestEvent(TestEvent te)
#else
void MyListener::onTestEvent(TestEvent &te)
#endif
{
	print("MyListener onTestEvent()");
}



#ifdef JAVA
}
#endif



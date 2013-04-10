#ifdef JAVA

package com.yomei.myssdp;
import java.io.*;
import java.lang.*;

#else 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestListener.h"

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
interface TestListener{
#endif


#ifndef JAVA
TestListener::TestListener()
{
	v_const();
	m_null=false;
}
#endif

#ifndef JAVA
TestListener::TestListener(int id)
{
	v_const();
}
#endif

#ifndef JAVA
TestListener::TestListener(const TestListener &f)
{
	v_const();
	m_null=true;

	tl=f.tl;
	((TestListener&)f).tl=NULL;
	if(tl && tl->m_null==false)m_null=false;
}
#endif


#ifndef JAVA
TestListener::~TestListener()
{
	v_dest();
}
#endif

#ifndef JAVA
void TestListener::v_const()
{
	m_null=true;
	tl=NULL;
}
#endif

#ifndef JAVA
void TestListener::v_dest()
{
	if(tl)delete tl;
	tl=NULL;
}
#endif


#ifndef JAVA
TestListener& TestListener::operator =(TestListener *f)
{
	v_const();
	tl=f;
	if(f)m_null=false;
	return *this;
}
#endif

#ifndef JAVA
TestListener& TestListener::operator =(TestListener &f)
{
	if(tl)delete tl;
	m_null=true;

	tl=f.tl;
	f.tl=NULL;
	if(tl && tl->m_null==false)m_null=false;
	return *this;
}
#endif


#ifndef JAVA
bool TestListener::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif

#ifndef JAVA
bool TestListener::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif



#ifdef JAVA
public void onTestEvent(TestEvent te);
#else
void TestListener::onTestEvent(TestEvent &te)
{
	if(tl){
		tl->onTestEvent(te);
		return;
	}
	//print("TestListener onTestEvent()");
}
#endif



#ifdef JAVA
}
#endif



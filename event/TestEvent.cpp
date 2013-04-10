#ifdef JAVA

package com.yomei.myssdp;
import java.io.*;
import java.lang.*;

#else 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestEvent.h"

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
public class TestEvent{
#endif

#ifdef JAVA
int id;
#endif

#ifdef JAVA
public TestEvent()
#else
TestEvent::TestEvent()
#endif
{
#ifndef JAVA
	v_const();
	m_null=false;
#endif
}

#ifndef JAVA
TestEvent::TestEvent(int id)
{
	v_const();
}
#endif

#ifndef JAVA
TestEvent::~TestEvent()
{
	v_dest();
}
#endif

#ifndef JAVA
void TestEvent::v_const()
{
	m_null=true;
	id=0;
}
#endif

#ifndef JAVA
void TestEvent::v_dest()
{
}
#endif

#ifndef JAVA
void TestEvent::v_copy(const TestEvent& te)
{
	m_null=te.m_null;
	id=te.id;
}
#endif

#ifndef JAVA
TestEvent& TestEvent::operator =(TestEvent *f)
{
	v_const();
	if(f!=NULL)v_copy(*f);
	delete f;
	return *this;
}
#endif

#ifndef JAVA
bool TestEvent::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}
#endif

#ifndef JAVA
bool TestEvent::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}
#endif


#ifdef JAVA
public void setID(int _id)
#else
void TestEvent::setID(int _id)
#endif
{
	id=_id;
}

#ifdef JAVA
public int getID()
#else
int TestEvent::getID()
#endif
{
	return id;
}



#ifdef JAVA
}
#endif



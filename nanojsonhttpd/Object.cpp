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
#include "Object.h"
#include "Thread.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
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
#define null NULL
#define byte char
#define true 1
#define false 0
#endif








#ifdef JAVA
Object()
#else
Object::Object()
#endif
{
	isnull=false;
}

#ifndef JAVA
Object::Object(int id)
{
	isnull=true;
}
#endif

#ifndef JAVA
Object::~Object()
{
}
#endif


#ifndef JAVA
Object& Object::operator =(Object *f)
{
	if(f==NULL)goto end;
	isnull=f->isnull;
	delete f;
end:
	return *this;
}
#endif


#ifndef JAVA
bool Object::operator ==(int a)
{
	if(isnull)return true;
	return false;
}
#endif

#ifndef JAVA
bool Object::operator !=(int a)
{
	if(isnull)return false;
	return true;
}
#endif



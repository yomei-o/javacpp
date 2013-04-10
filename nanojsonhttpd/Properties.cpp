/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA

import java.io.*;
import java.lang.*;
import java.util.*;

#else 

#include "String_.h"
#include "Properties.h"
#include "OutputStream.h"
#include "InputStream.h"
#include "Enumeration.h"
#include "mymap.h"


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
#define null 0
#define byte char
#define true 1
#define false 0
#endif


#ifdef _WIN32
#pragma warning (disable: 4786) 
#endif




Properties::Properties()
{
	mmap=mymap_alloc();
}

Properties::Properties(int id)
{
	mmap=mymap_alloc();
}
Properties::~Properties()
{
	if(mmap)mymap_delete((MYMAP*)mmap);
	mmap=NULL;
}


Properties& Properties::operator =(Properties *f)
{
	if(f==NULL)goto end;
	
	if(mmap)mymap_delete((MYMAP*)mmap);
	mmap=NULL;
	mmap=mymap_copy((MYMAP*)(f->mmap));

	delete f;
end:
	return *this;
}


void Properties::setProperty(String& key,String& val)
{
	setProperty((char*)key,(char*)val);
}
void Properties::setProperty(String& key,char* val)
{
	setProperty((char*)key,(char*)val);
}
void Properties::setProperty(char* key,String& val)
{
	setProperty((char*)key,(char*)val);
}
void Properties::setProperty(char* key,char* val)
{
	if(mmap)mymap_put((MYMAP*)mmap,key,val);
}

void Properties::put(String& key,String& val)
{
	put((char*)key,(char*)val);
}
void Properties::put(String& key,char* val)
{
	put((char*)key,(char*)val);
}
void Properties::put(char* key,String& val)
{
	put((char*)key,(char*)val);
}
void Properties::put(char* key,char* val)
{
	if(mmap)mymap_put((MYMAP*)mmap,key,val);
}


String Properties::get(String& key)
{
	return get((char*)key);
}
String Properties::get(char* key)
{
	String s=null;
	char* ret=NULL;
	if(mmap)ret=mymap_get((MYMAP*)mmap,key);
	if(ret)s=new String(ret);
	return s;
}

String Properties::getProperty(String& key)
{
	return get((char*)key);
}
String Properties::getProperty(char* key)
{
	String s=null;
	char* ret=NULL;
	if(mmap)ret=mymap_get((MYMAP*)mmap,key);
	if(ret)s=new String(ret);
	return s;
}

void Properties::store(OutputStream& osd,String& comment)
{	
	store(osd,(char*)comment);
}

int Properties::size()
{	
	return mymap_getNums((MYMAP*)mmap);
}

void Properties::store(OutputStream& osd,char* comment)
{
	int n=mymap_getNums((MYMAP*)mmap);
	int i=0;
	
	String key=null;
	String val=null;
	String ttt=null;
	ttt="=";
	String eee=null;
	eee="\r\n";
	for(i=0;i<n;i++){
		char* tmp;
		key=null;
		tmp=mymap_getIndexOfKey((MYMAP*)mmap,i);
		if(tmp)key=tmp;
		val=null;
		tmp=mymap_getIndexOfValue((MYMAP*)mmap,i);
		if(tmp)val=tmp;
		key=key.replace("\\","\\\\");
		key=key.replace(":","\\:");
		key=key.replace("=","\\=");
		key=key.replace("\r","\\r");
		key=key.replace("\n","\\n");
		key=key.replace(" ","\\ ");

		val=val.replace("\\","\\\\");
		val=val.replace("=","\\=");
		val=val.replace(":","\\:");
		val=val.replace("\r","\\r");
		val=val.replace("\n","\\n");
		val=val.replace(" ","\\ ");

		osd.write((char*)key,0,(int)strlen((char*)key));
		osd.write((char*)ttt,0,(int)strlen((char*)ttt));
		osd.write((char*)val,0,(int)strlen((char*)val));
		osd.write((char*)eee,0,(int)strlen((char*)eee));
	}	

}

void Properties::load(InputStream & is)
{
	int i;
	char tmp[2048];

	while(1){
		i=0;
		tmp[0]=0;
		while(1)
		{
			int len;
			char ttmp;
			len=is.read(&ttmp,0,1);
			if(len==0){
				tmp[i]=0;
				break;
			}
			if(ttmp=='\r')continue;
			if(ttmp=='\n'){
				tmp[i]=0;
				break;
			}
			tmp[i]=ttmp;
			i++;
			if(i+1>=sizeof(tmp))
			{
				tmp[i]=0;
				break;
			}
		}
		if(i==0)break;
		if(tmp[0]=='#')continue;
		char*p=tmp;
more:
		p+=1;
		p=strchr(p,'=');
		if(p==NULL)continue;
		if(*(p-1)=='\\')goto more;

		*p=0;

		String key=null;
		String val=null;

		//printf(">>%s<<>>%s<<\n",tmp,p+1);
		key=tmp;
		val=p+1;

		key=key.replace("\\:",":");
		key=key.replace("\\=","=");
		key=key.replace("\\r","\r");
		key=key.replace("\\n","\n");
		key=key.replace("\\ "," ");
		key=key.replace("\\\\","\\");
		
		val=val.replace("\\:",":");
		val=val.replace("\\=","=");
		val=val.replace("\\r","\r");
		val=val.replace("\\n","\n");
		val=val.replace("\\ "," ");
		val=val.replace("\\\\","\\");

		mymap_put((MYMAP*)mmap,(char*)key,(char*)val);
	}
}


Enumeration Properties::keys()
{
	Enumeration m=null;
	m=new Enumeration();
	int c,i;
	c=mymap_getNums((MYMAP*)mmap);
	for(i=0;i<c;i++){
		m.add(mymap_getIndexOfKey((MYMAP*)mmap,i));
	}


	return m;
}

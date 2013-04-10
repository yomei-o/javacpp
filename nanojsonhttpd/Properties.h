/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_PROPERTIES_H__
#define D_PROPERTIES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "Enumeration.h"
class Enumeration;
class OutputStream;
class InputStream;


class Properties{
public :
	Properties();
	Properties(int id);
	virtual ~Properties();

	Properties& operator =(Properties *rhs);

	void setProperty(String &key,String& val);
	void setProperty(String &key,char* val);
	void setProperty(char* key,String& val);
	void setProperty(char* key,char* val);

	void put(String &key,String& val);
	void put(String &key,char* val);
	void put(char* key,String& val);
	void put(char* key,char* val);

	String getProperty(String &key);
	String getProperty(char* key);

	String get(String &key);
	String get(char*key);
	int size();

	Enumeration keys();


	void store(OutputStream& os,String& comment);
	void store(OutputStream& os,char* comment);
	void load(InputStream& is);

public:
	void* mmap;
};



#endif /* D_PROPERTIES_H__ */



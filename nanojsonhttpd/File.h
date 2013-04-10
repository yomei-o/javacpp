/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_FILE_H__
#define D_FILE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String_.h"


#ifndef longlong

#ifdef JAVA
#define longlong long
#else
#if defined(_WIN32) && _MSC_VER <=1200
#define longlong _int64
#else
#define longlong long long
#endif /* _MSC_VER */
#endif /* JAVA */
#endif /* longlong */



class File{
public :
	File();
	File(int id);
	File(char* str);
	File(String & str);
	File(const File & f);
	virtual ~File();

	String getName();
	longlong length();
	bool exists();
	bool isFile();
	bool isDirectory();
	bool deleteFile();
	bool mkdir();
	bool renameTo(File& f);
	longlong lastModified() ;
	String** list();

	File& operator =(File *rhs);
	File& operator =(File rhs);

	bool operator ==(int);
	bool operator !=(int);

public:
	String fn;
};



#endif /* D_FILE_H__ */



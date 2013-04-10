/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_FILEOUTPUTSTREAM_H__
#define D_FILEOUTPUTSTREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "OutputStream.h"

class String;
class File;

class FileOutputStream:public OutputStream{
public :
	FileOutputStream();
	FileOutputStream(int id);
	FileOutputStream(String & str);
	FileOutputStream(char* str);
	FileOutputStream(File & ff);
	FileOutputStream(char* str,bool append);
	FileOutputStream(String & str,bool append);
	//FileOutputStream(const FileOutputStream & f);
	virtual ~FileOutputStream();


	
	
	static void* s_open(void*);
	static void* s_open2(void*);
	static void* s_dup(void*);
	static void* s_dup2(void*);
	static void s_flush(void*);
	static void s_close(void*);
	static int s_write(void*,char*,int ,int);

	
	FileOutputStream& operator =(FileOutputStream *rhs);
	//FileOutputStream& operator =(FileOutputStream& rhs);

public:
	bool isappend;
};


#endif /* D_FILEOUTPUTSTREAM_H__ */




/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_FILEINPUTSTREAM_H__
#define D_FILEINPUTSTREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "InputStream.h"
class String;
class File;

class FileInputStream:public InputStream{
public :
	FileInputStream();
	FileInputStream(int id);
	FileInputStream(String & str);
	FileInputStream(char* str);
	FileInputStream(File & ff);
//	FileInputStream(const FileInputStream & f);
	virtual ~FileInputStream();

	
	
	static void* s_open(void*);
	static void* s_dup(void*);
	static void s_reset(void*);
	static void s_close(void*);
	static int s_read(void*,char*,int ,int);
	static int s_skip(void*,int);


	FileInputStream& operator =(FileInputStream *rhs);
	//FileInputStream& operator =(FileInputStream& rhs);

public:
};


#endif /* D_FILEINPUTSTREAM_H__ */




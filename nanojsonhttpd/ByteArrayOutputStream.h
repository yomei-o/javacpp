/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_BYTEARRAYOUTPUTSTREAM_H__
#define D_BYTEARRAYOUTPUTSTREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "OutputStream.h"

class String;

class ByteArrayOutputStream:public OutputStream{
public :
	ByteArrayOutputStream();
	ByteArrayOutputStream(int id);
	ByteArrayOutputStream(char*);
	virtual ~ByteArrayOutputStream();
	
	int	size();
	char* toByteArray();

	static void* s_open(int sz);
	static void* s_dup(void*);
	static void s_flush(void*);
	static void s_close(void*);
	static int s_write(void*,char*,int ,int);

	
	ByteArrayOutputStream& operator =(ByteArrayOutputStream *rhs);
	//FileOutputStream& operator =(FileOutputStream& rhs);

public:
};


#endif /* D_BYTEARRAYOUTPUTSTREAM_H__ */




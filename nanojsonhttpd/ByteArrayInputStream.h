/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_BYTEARRAYINPUTSTREAM_H__
#define D_BYTEARRAYINPUTSTREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "InputStream.h"

class String;

class ByteArrayInputStream:public InputStream{
public :
	ByteArrayInputStream();
	ByteArrayInputStream(int id);
	ByteArrayInputStream(char* dd,int off,int ss);
	virtual ~ByteArrayInputStream();

	
	
	static void* s_open(void*,int sz);
	static void* s_dup(void*);
	static void s_reset(void*);
	static void s_close(void*);
	static int s_read(void*,char*,int ,int);
	static int s_skip(void*,int);


	ByteArrayInputStream& operator =(ByteArrayInputStream *rhs);

public:

};


#endif /* D_BYTEARRAYINPUTSTREAM_H__ */




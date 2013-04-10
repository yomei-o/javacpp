/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_WRITER_H__
#define D_WRITER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


class String;

class Writer{
public :
	Writer();
	Writer(int id);
	Writer(const Writer & f);
	virtual ~Writer();

//	void flush();
	void close();
	void write(int c);
	void write(String & c);


	void* (*p_dup)(void*);
	void (*p_close)(void*);
	int (*p_write)(void*,char* buf,int off,int sz);
	
	
	static void* s_dup(void*);
	static void s_close(void*);
	static int s_write(void*,char* buf,int off,int sz);
	
	Writer& operator =(Writer *rhs);
	Writer& operator =(Writer& rhs);

public:
	
	void* handle;

};



#endif /* D_WRITER_H__ */



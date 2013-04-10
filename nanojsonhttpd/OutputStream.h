/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_OUTPUTSTREAM_H__
#define D_OUTPUTSTREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class OutputStream{
public :
	OutputStream();
	OutputStream(int id);
	OutputStream(const OutputStream & f);
	virtual ~OutputStream();

	void flush();
	void close();
	int write(char* p,int offset,int byte);


	void* (*p_open)(void*);
	void* (*p_dup)(void*);
	void (*p_flush)(void*);
	void (*p_close)(void*);
	int (*p_write)(void*,char*,int ,int);
	
	
	static void* s_open(void*);
	static void* s_dup(void*);
	static void s_flush(void*);
	static void s_close(void*);
	static int s_write(void*,char*,int ,int);
	
	OutputStream& operator =(OutputStream *rhs);
	//OutputStream& operator =(OutputStream& rhs);
	OutputStream& operator =(OutputStream rhs);

	bool operator ==(int id);
	bool operator !=(int id);

public:
	
	void* handle;

};



#endif /* D_OUTPUTSTREAM_H__ */



/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_READER_H__
#define D_READER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class Reader{
public :
	Reader();
	Reader(int id);
	Reader(const Reader & f);
	virtual ~Reader();

//	void reset();
	void close();
	int read();


	void* (*p_dup)(void*);
	void (*p_close)(void*);
	int (*p_read)(void*,char*,int,int);
	
	
	static void* s_dup(void*);
	static void s_close(void*);
	static int s_read(void*,char*,int,int);
	
	Reader& operator =(Reader *rhs);
	Reader& operator =(Reader &rhs);

public:
	
	void* handle;

};



#endif /* D_READER_H__ */



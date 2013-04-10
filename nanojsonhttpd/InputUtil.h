/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_InputUtil_H__
#define D_InputUtil_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class InputStream;


class InputUtil{
public :
	InputUtil();
	InputUtil(int id);
	virtual ~InputUtil();

	InputUtil(const InputUtil &a);

	InputUtil& operator =(InputUtil *rhs);
	InputUtil& operator =(char* *rhs);


	int read(InputStream& is,char* s,int soff,int slen);
	void unread(char* s,int soff,int slen,int modoru);
	String readLine(InputStream& is,char* data,int off,int len);
	int getReadSize();

	bool operator ==(int);
	bool operator !=(int);

public:
	int read_size;
	bool m_null;
	char* data;
	int len;
};

#endif /* D_InputUtil_H__ */



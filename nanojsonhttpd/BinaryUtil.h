/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_BinaryUtil_H__
#define D_BinaryUtil_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class BinaryUtil{
public :
	BinaryUtil();
	BinaryUtil(int id);
	virtual ~BinaryUtil();

	BinaryUtil(const BinaryUtil &a);

	BinaryUtil& operator =(BinaryUtil *rhs);
	BinaryUtil& operator =(char* *rhs);

	static int indexOf(char* s,int soff,int slen,char* d,int doff,int dlen);
	static int indexOf(char* s,int soff,int slen,char* d);
	static int indexOf(char* s,int soff,int slen,String &str);
	static int lastIndexOf(char* s,int soff,int slen,char* d,int doff,int dlen);
	static int lastIndexOf(char* s,int soff,int slen,char* d);
	static int lastIndexOf(char* s,int soff,int slen,String &str);

	static int partOf(char* s,int soff,int slen,char* d,int doff,int dlen);
	static int partOf(char* s,int soff,int slen,char* d);
	static int partOf(char* s,int soff,int slen,String &str);

	static int nokori(char* s,int soff,int slen,char* d,int doff,int dlen);
	static int nokori(char* s,int soff,int slen,char* d);
	static int nokori(char* s,int soff,int slen,String &str);

	static String readLine(char* s,int soff,int slen);
	static int getLineSize(char* s,int soff,int slen);


	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
};

static BinaryUtil BinaryUtil(0);

#endif /* D_BinaryUtil_H__ */



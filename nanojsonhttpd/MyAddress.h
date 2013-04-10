/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_MYADDRESS_H__
#define D_MYADDRESS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class MyAddress{
public :
	MyAddress();
	MyAddress(int id);
	virtual ~MyAddress();
	MyAddress(const MyAddress& o);

	MyAddress& operator =(MyAddress *rhs);
	MyAddress& operator =(MyAddress rhs);

	bool operator ==(int);
	bool operator !=(int);

	int getType(void);
	void setType(int type);
	void clearType(void);

	int getPort(void);
	void setPort(int port);
	void clearPort(void);

	int getLength(void);
	void setLength(int port);
	void clearLength(void);

	char* getAddress(void);
	void setAddress(char* add,int off ,int len);
	void clearAddress(void);

public:
	bool isnull;
	int type;
	int len;
	int port;
	char address[16];
};



#endif /* D_MYADDRESS_H__ */



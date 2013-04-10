/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_INETADDRESS_H__
#define D_INETADDRESS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Class;

class InetAddress{
public :
	InetAddress();
	InetAddress(int id);
	virtual ~InetAddress();

	InetAddress(const InetAddress &a);

	InetAddress& operator =(InetAddress *rhs);
	//InetAddress& operator =(InetAddress& rhs);
	InetAddress& operator =(InetAddress rhs);
	InetAddress& operator =(char* rhs);

	Class getClass();
	char* getAddress();

	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;

	int type;
	int len;
	char address[16];
};



#endif /* D_INETADDRESS_H__ */



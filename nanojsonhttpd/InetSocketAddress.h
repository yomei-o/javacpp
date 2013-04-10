/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_INETSOCKETADDRESS_H__
#define D_INETSOCKETADDRESS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String_.h"

class InetAddress;

class InetSocketAddress{
public :
	InetSocketAddress();
	InetSocketAddress(int id);
	InetSocketAddress(String& host,int port);
	InetSocketAddress(char* host,int port);
	InetSocketAddress(InetAddress& ina,int port);
	virtual ~InetSocketAddress();

	InetSocketAddress& operator =(InetSocketAddress *rhs);

	InetAddress getAddress();
public:
	String host;
	int port;

};



#endif /* D_INETSOCKETADDRESS_H__ */



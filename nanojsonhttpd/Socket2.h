/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_SOCKET2_H__
#define D_SOCKET2_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sock2_local.h"
#include "OutputStream.h"
#include "InputStream.h"

#define Socket Socket2

class InetSocketAddress;


class String;
class InetAddress;

class Socket2{
public :
	Socket2();
	Socket2(int id);
	virtual ~Socket2();

	Socket2& operator =(Socket2 *rhs);
	bool operator ==(int id);
	bool operator !=(int id);

	OutputStream 	getOutputStream();
	InputStream 	getInputStream();

	void connect(InetSocketAddress& isa);
	void connect(InetSocketAddress& isa,int timeout);

	void close();
	bool isClosed();
	bool isConnected();
	void internal_setSoTimeout(int timeout);
	void setSoTimeout(int timeout);

	static int s_write(void*,char*,int ,int);
	static int s_read(void*,char*,int ,int);

public:
	SOCKET s;
	int timeout;
	bool isconnected;
	bool create;
};



#endif /* D_SOCKET_H__ */



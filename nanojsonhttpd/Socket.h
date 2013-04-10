/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_SOCKET_H__
#define D_SOCKET_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sock2_local.h"
#include "OutputStream.h"
#include "InputStream.h"

class InetSocketAddress;
//class OutputStream;


class String;
class InetAddress;

class Socket{
public :
	Socket();
	Socket(int id);
	Socket(const Socket & f);
	virtual ~Socket();

	Socket& operator =(Socket *rhs);
	//Socket& operator =(Socket &rhs);
	Socket& operator =(Socket rhs);
	bool operator ==(int id);
	bool operator !=(int id);

	OutputStream 	getOutputStream();
	InputStream 	getInputStream();

	//void connect(InetSocketAddress& isa);
	void close();
	bool isClosed();
	void setSoTimeout(int timeout);

	static void* s_dup(void*);
	static void s_close(void*);
	static int s_write(void*,char*,int ,int);
	static int s_read(void*,char*,int ,int);

	InetAddress getInetAddress();
	InetAddress getLocalAddress();

public:
	SOCKET s;
	int timeout;

	int local_address_type;
	int local_address_len;
	char local_address[16];

	int inet_address_type;
	int inet_address_len;
	char inet_address[16];

};



#endif /* D_SOCKET_H__ */



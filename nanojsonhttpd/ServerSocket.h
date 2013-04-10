/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_SERVERSOCKET_H__
#define D_SERVERSOCKET_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sock2_local.h"

#include "Socket.h"


class String;
class InetAddress;

class ServerSocket{
public :
	ServerSocket();
	ServerSocket(int id);
	virtual ~ServerSocket();

	ServerSocket& operator =(ServerSocket *rhs);
	//ServerSocket& operator =(ServerSocket &rhs);
	ServerSocket& operator =(ServerSocket rhs);
	bool operator ==(int id);
	bool operator !=(int id);

	Socket accept();
	void close();
	bool isClosed();
	void setSoTimeout(int timeout);

	InetAddress getInetAddress();

public:
	SOCKET s;
	SOCKET s6;
	int port;
	int timeout;

	int local_address_type;
	int local_address_len;
	char local_address[16];
};



#endif /* D_SERVERSOCKET_H__ */



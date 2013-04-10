/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_DATAGRAMPACKET_H__
#define D_DATAGRAMPACKET_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class InetSocketAddress;
class InetAddress;


class DatagramPacket{
public :
	DatagramPacket();
	DatagramPacket(int id);

	DatagramPacket(char*,int off,int len);
	DatagramPacket(char*,int len);

	virtual ~DatagramPacket();

	DatagramPacket& operator =(DatagramPacket *rhs);

	bool operator ==(int);
	bool operator !=(int);


	void setSocketAddress(InetSocketAddress& ina);
	InetSocketAddress getSocketAddress();
	InetAddress getAddress();

	void setPort(int port);
	int getPort();

	int	 getOffset();
	int getLength();

public:
	bool isnull;

	int port;
	String host;

	char* data;
	int data_len;
	int data_off;
};



#endif /* D_DATAGRAMPACKET_H__ */



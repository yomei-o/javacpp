/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_MULTICASTSOCKET_H__
#define D_MULTICASTSOCKET_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sock2_local.h"

class String;
class InetSocketAddress;
class NetworkInterface;
class DatagramPacket;

class MulticastSocket{
public :
	// new Object();
	MulticastSocket();

	// Object a=null;
	MulticastSocket(int id);

	// return a;
	MulticastSocket(const MulticastSocket &a);

	virtual ~MulticastSocket();

	// a=new Object();
	MulticastSocket& operator =(MulticastSocket *rhs);

	// a=func()
	MulticastSocket& operator =(MulticastSocket rhs);

	// a==null
	bool operator ==(int id);
	// a!=null
	bool operator !=(int id);

	void close();
	bool isClosed();
	bool isBound();
	void setSoTimeout(int timeout);

	void joinGroup(InetSocketAddress& isa,NetworkInterface & nif);
	void leaveGroup(InetSocketAddress& isa,NetworkInterface & nif);
	void setReuseAddress(bool a);
	bool getReuseAddress();

	void setLoopbackMode(bool disable);
	bool getLoopbackMode();

	int getTimeToLive();
	void setTimeToLive(int ttl);

	int getReceiveBufferSize();
	void setReceiveBufferSize(int sz);

	int getSendBufferSize();
	void setSendBufferSize(int sz);
	
	void bind(InetSocketAddress& isa);

	void receive(DatagramPacket& p);	
	void  send(DatagramPacket& p);
	void autocreate();

	void setNetworkInterface(NetworkInterface& netIf);

public:
	SOCKET s;
	int timeout;
	bool isconnected;
	bool isbind;
	bool isauto;
};



#endif /* D_SOCKET_H__ */



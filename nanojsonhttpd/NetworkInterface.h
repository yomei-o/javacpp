/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_NETWORKINTERFACE_H__
#define D_NETWORKINTERFACE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Enumeration;
class List;

class NetworkInterface{
public :
	NetworkInterface();
	NetworkInterface(int id);
	virtual ~NetworkInterface();

	NetworkInterface(const NetworkInterface &a);

	NetworkInterface& operator =(NetworkInterface *rhs);
	//NetworkInterface& operator =(NetworkInterface& rhs);
	NetworkInterface& operator =(NetworkInterface rhs);
	NetworkInterface& operator =(char* rhs);


	List getInterfaceAddresses();
	Enumeration getInetAddresses();
	static Enumeration getNetworkInterfaces();
	char* getHardwareAddress();

	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
	char* m;
};



#endif /* D_NETWORKINTERFACE_H__ */



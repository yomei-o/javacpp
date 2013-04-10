/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_INTERFACEADDRESS_H__
#define D_INTERFACEADDRESS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class InetAddress;

class InterfaceAddress{
public :
	InterfaceAddress();
	InterfaceAddress(int id);
	virtual ~InterfaceAddress();
	InterfaceAddress(const InterfaceAddress &a);

	InterfaceAddress& operator =(InterfaceAddress *rhs);
	//InterfaceAddress& operator =(InterfaceAddress& rhs);
	InterfaceAddress& operator =(InterfaceAddress rhs);
	InterfaceAddress& operator =(char* rhs);

	InetAddress getAddress();
	int getNetworkPrefixLength();

	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
	char* m;
};



#endif /* D_INTERFACEADDRESS_H__ */



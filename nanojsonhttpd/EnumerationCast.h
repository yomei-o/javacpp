/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_ENUMERATIONCAST_H__
#define D_ENUMERATIONCAST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "String_.h"
//#include "NetworkInterface.h"

class String;
class NetworkInterface;
class InetAddress;


class EnumerationCast{
public :
	EnumerationCast();
	EnumerationCast(int id);
	EnumerationCast(const EnumerationCast &a);

	virtual ~EnumerationCast();

	//EnumerationCast& operator =(EnumerationCast *rhs);
	EnumerationCast& operator =(char*);

	operator String();
	operator NetworkInterface();
	operator InetAddress();

	bool operator ==(int);
	bool operator !=(int);

public:
	void* m;
};



#endif /* D_ENUMERATIONCAST_H__ */



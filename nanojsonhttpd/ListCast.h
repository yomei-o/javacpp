/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_LISTCAST_H__
#define D_LISTCAST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "String_.h"
//#include "NetworkInterface.h"

class String;
class InterfaceAddress;


class ListCast{
public :
	ListCast();
	ListCast(int id);
	ListCast(const ListCast &a);

	virtual ~ListCast();

	//ListCast& operator =(ListCast *rhs);
	ListCast& operator =(char*);

	operator String();
	operator InterfaceAddress();

	bool operator ==(int);
	bool operator !=(int);

public:
	void* m;
};



#endif /* D_LISTCAST_H__ */



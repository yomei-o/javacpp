/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_ENUMERATION_H__
#define D_ENUMERATION_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String_.h"
#include "EnumerationCast.h"


class Enumeration{
public :
	Enumeration();
	Enumeration(int id);
	Enumeration(const Enumeration &a);
	virtual ~Enumeration();

	Enumeration& operator =(Enumeration *rhs);
	//Enumeration& operator =(Enumeration &rhs);
	Enumeration& operator =(Enumeration rhs);

	bool operator ==(int);
	bool operator !=(int);

	bool hasMoreElements();
	EnumerationCast nextElement();

	void add(String &);
	void add(char*);
public:
	void* m;
};



#endif /* D_ENUMERATION_H__ */



/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_LIST_H__
#define D_LIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "String_.h"
class String;
class ListCast;


class List{
public :
	List();
	List(int id);
	List(const List &a);
	virtual ~List();

	List& operator =(List *rhs);
	//List& operator =(List &rhs);
	List& operator =(List rhs);

	bool operator ==(int);
	bool operator !=(int);

	//bool hasMoreElements();
	//String 	nextElement();
	void add(String &);
	void add(char*);

	int size();
	ListCast get(int n);

public:
	void* m;
};



#endif /* D_LIST_H__ */



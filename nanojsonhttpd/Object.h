/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_OBJECT_H__
#define D_OBJECT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class Object{
public :
	Object();
	Object(int id);
	virtual ~Object();

	//Object(const Object& o);

	Object& operator =(Object *rhs);
	//Object& operator =(Object rhs);

	bool operator ==(int);
	bool operator !=(int);

public:
	bool isnull;
};



#endif /* D_OBJECT_H__ */



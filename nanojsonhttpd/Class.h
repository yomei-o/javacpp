/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_CLASS_H__
#define D_CLASS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class Class{
public :
	Class();
	Class(int id);
	virtual ~Class();

	Class(const Class &a);

	Class& operator =(Class *rhs);
	Class& operator =(char* *rhs);

	String getName();

	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
	char* name;
};



#endif /* D_CLASS_H__ */



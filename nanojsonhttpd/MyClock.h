/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_MyClock_H__
#define D_MyClock_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class MyClock{
public :
	MyClock();
	MyClock(int id);
	virtual ~MyClock();

	MyClock(const MyClock &a);

	MyClock& operator =(MyClock *rhs);
	MyClock& operator =(char* *rhs);

	static int get();

	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
};

static MyClock MyClock(0);

#endif /* D_MyClock_H__ */



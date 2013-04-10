/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_CTime_H__
#define D_CTime_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class CTime{
public :
	CTime();
	CTime(int id);
	virtual ~CTime();

	CTime(const CTime &a);

	CTime& operator =(CTime *rhs);
	CTime& operator =(char* *rhs);

	static int get();

	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
};

static CTime CTime(0);

#endif /* D_CTime_H__ */



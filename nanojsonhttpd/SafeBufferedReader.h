/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_SAFEBUFFEREDREADER_H__
#define D_SAFEBUFFEREDREADER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BufferedReader.h"
#include "InputStreamReader.h"
#include "String_.h"


class SafeBufferedReader:public BufferedReader{
public :
	SafeBufferedReader(int id);
	SafeBufferedReader(const SafeBufferedReader & f);
	SafeBufferedReader(Reader & f);
	virtual ~SafeBufferedReader();

	String readLine();
	void setMaximum(int n);
	
	SafeBufferedReader& operator =(SafeBufferedReader *rhs);
	SafeBufferedReader& operator =(SafeBufferedReader &rhs);

public:
	int maxn;
};



#endif /* D_BUFFEREDREADER_H__ */



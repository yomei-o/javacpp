/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_BUFFEREDREADER_H__
#define D_BUFFEREDREADER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Reader.h"
#include "InputStreamReader.h"
#include "String_.h"


class BufferedReader:public InputStreamReader{
public :
	BufferedReader(int id);
	BufferedReader(const BufferedReader & f);
	BufferedReader(Reader & f);
	virtual ~BufferedReader();

	String readLine();
	
	BufferedReader& operator =(BufferedReader *rhs);
	BufferedReader& operator =(BufferedReader &rhs);

public:
};



#endif /* D_BUFFEREDREADER_H__ */



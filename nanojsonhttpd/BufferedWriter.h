/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_BUFFEREDRWRITER_H__
#define D_BUFFEREDRWRITER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Writer.h"
#include "OutputStreamWriter.h"
#include "String_.h"


class BufferedWriter:public OutputStreamWriter{
public :
	BufferedWriter(int id);
	BufferedWriter(const BufferedWriter & f);
	BufferedWriter(Writer & f);
	virtual ~BufferedWriter();

	void newLine();
	
	BufferedWriter& operator =(BufferedWriter *rhs);
	BufferedWriter& operator =(BufferedWriter &rhs);

public:
};



#endif /* D_BUFFEREDRWRITER_H__ */



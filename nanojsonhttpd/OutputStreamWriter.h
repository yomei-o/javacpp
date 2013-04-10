/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_OUTPUTSTREAMWRITER_H__
#define D_OUTPUTSTREAMWRITER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Writer.h"
#include "OutputStream.h"


class OutputStreamWriter:public Writer{
public :
	OutputStreamWriter();
	OutputStreamWriter(int id);
	OutputStreamWriter(const OutputStreamWriter & f);
	OutputStreamWriter(OutputStream & f);
	virtual ~OutputStreamWriter();
	
	OutputStreamWriter& operator =(OutputStreamWriter *rhs);
	OutputStreamWriter& operator =(OutputStreamWriter &rhs);

public:
};



#endif /* D_OUTPUTSTREAMWRITER_H__ */



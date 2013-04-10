/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_INPUTSTREAMREADER_H__
#define D_INPUTSTREAMREADER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Reader.h"
#include "InputStream.h"


class InputStreamReader:public Reader{
public :
	InputStreamReader();
	InputStreamReader(int id);
	InputStreamReader(const InputStreamReader & f);
	InputStreamReader(InputStream & f);
	virtual ~InputStreamReader();
	
	InputStreamReader& operator =(InputStreamReader *rhs);
	InputStreamReader& operator =(InputStreamReader &rhs);

public:
};



#endif /* D_INPUTSTREAMREADER_H__ */



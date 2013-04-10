/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_NanoJsonHttpdError_H__
#define D_NanoJsonHttpdError_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


class NanoJsonHttpdError{
public :
	NanoJsonHttpdError();
	NanoJsonHttpdError(int id);
	NanoJsonHttpdError(const NanoJsonHttpdError & f);
	virtual ~NanoJsonHttpdError();

	NanoJsonHttpdError& operator =(NanoJsonHttpdError *rhs);

	static void setError();
	static bool isError();

};

static NanoJsonHttpdError NanoJsonHttpdError;


#endif /* D_HTTPSESSION_H__ */



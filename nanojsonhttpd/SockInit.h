/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_SOCKINIT_H__
#define D_SOCKINIT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sock2_local.h"

class SockInit{
public :
	SockInit();
	SockInit(int id);
	virtual ~SockInit();

	SockInit& operator =(SockInit *rhs);

public:
};



#endif /* D_SOCKINIT_H__ */



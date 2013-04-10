/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_RUNNABLE_H__
#define D_RUNNABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


class Runnable{
public :
	Runnable();
	virtual ~Runnable();

	virtual void run();

	static void s_run(void* arg);
	void (*prun)(void*);
	int flag;

public:
};



#endif /* D_RUNNABLE_H__ */



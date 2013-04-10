/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_ThreadManager_H__
#define D_ThreadManager_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


class ThreadManager{
public :
	ThreadManager();
	ThreadManager(int id);
	ThreadManager(const ThreadManager & f);
	virtual ~ThreadManager();

	ThreadManager& operator =(ThreadManager *rhs);

	static void start();
	static void stop();

};

static ThreadManager ThreadManager;


#endif /* D_HTTPSESSION_H__ */



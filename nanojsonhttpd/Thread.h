/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_THREAD_H__
#define D_THREAD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Runnable.h"


class Thread:public Runnable{
public :
	Thread();
	Thread(int id);
	//Thread(const Thread & f);
	Thread(Runnable& r);
	virtual ~Thread();

	Thread& operator =(Thread *rhs);
	virtual void run();

	bool operator ==(int id);
	bool operator !=(int id);

	void start();
	void join();
	void sleep(int ms);

	static void s_run(void* arg);
	
public:
	//Runnable* r;
	int id;
	bool isnull;
};



#endif /* D_THREAD_H__ */



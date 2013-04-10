/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_NANOJSONHTTPD_H__
#define D_NANOJSONHTTPD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Runnable.h"
#include "ServerSocket.h"


class NanoJsonHttpd:public Runnable{
public :
	NanoJsonHttpd();
	NanoJsonHttpd(int id);
	NanoJsonHttpd(const NanoJsonHttpd & f);
	virtual ~NanoJsonHttpd();

	NanoJsonHttpd& operator =(NanoJsonHttpd *rhs);

	virtual void run();
	void stopAll();
	bool isReady();

	static void s_run(void* arg);

	bool operator ==(int id);
	bool operator !=(int id);

	
public:
	bool isnull;
	static int is_ready;
	static int stop_req;
	ServerSocket s;
	int port;
};



#endif /* D_NANOJSONHTTPD_H__ */



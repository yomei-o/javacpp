/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"
#include "Runnable.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif






Runnable::Runnable()
{
	prun=s_run;
	flag=0;
}

Runnable::~Runnable()
{
}


void Runnable::run()
{
	printf("Runnable::run()\n");
}


void Runnable::s_run(void* arg)
{
	Runnable* r=new Runnable();
	((Runnable*)arg)->flag=1;
	r->run();
	delete r;
}


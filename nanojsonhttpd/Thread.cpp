/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"
#include "Thread.h"
#include "Runnable.h"
#include "ThreadPool.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


Thread::Thread()
{
	id=-1;
	prun=s_run;
	isnull=false;
//	r=this;
}

Thread::Thread(int id)
{
	id=-1;
	prun=s_run;
	isnull=true;
//	r=this;
}

Thread::~Thread()
{
}


Thread& Thread::operator =(Thread *f)
{
	isnull=true;
	if(f==NULL)goto end;
	//r=f->r;
	id=f->id;
	prun=f->prun;
	flag=f->flag;
	isnull=f->isnull;

	delete f;
end:
	return *this;
}


Thread::Thread(Runnable& rr)
{
//	r=&rr;
	id=-1;
	prun=rr.prun;
	isnull=false;
}


void Thread::s_run(void* arg)
{
	Thread* r=new Thread();
	((Runnable*)arg)->flag=1;
	r->run();
	((Runnable*)arg)->flag=2;
	delete r;
}

void Thread::run()
{
	printf("Thread::run()\n");
}

void Thread::sleep(int ms)
{
	ThreadPool::sleep(ms);
}


void Thread::start()
{
	flag=0;
	id=ThreadPool::create((void*)prun,this);
	while(flag==0)ThreadPool::sleep(10);
}
void Thread::join()
{
	ThreadPool::join(id);
}


#ifndef JAVA
bool Thread::operator ==(int id)
{
	if(isnull)return true;
	return false;
}
#endif

#ifndef JAVA
bool Thread::operator !=(int id)
{
	if(isnull)return false;
	return true;
}
#endif

/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__


#ifdef unix
/* define if use pthread */
#define HAVE_PTHREAD_H
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#include <string.h>
#else
#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#include <process.h>
#endif
#endif


#ifdef HAVE_PTHREAD_H
typedef pthread_t hthread_t;
#else
#ifdef _WIN32
typedef HANDLE hthread_t;
#endif
#endif



typedef struct _thread
{
	hthread_t hthread;
	void* func;
	void* arg;
} mythread_t;


#ifdef __cplusplus
extern "C"
{
#endif

mythread_t* mythread_create(void* func, void *arg);
void mythread_join(mythread_t* t);
void mythread_exit(mythread_t* t);

#ifdef __cplusplus
}
#endif

#endif /* __MYTHREAD_H__ */

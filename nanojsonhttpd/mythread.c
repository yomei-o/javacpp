/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#include <stdio.h>
#include <stdlib.h>
#include "mythread.h"



#ifdef HAVE_PTHREAD_H
#define PTHREAD_CREATE(thread, attr, func, arg)                          \
	(int)pthread_create((pthread_t *)(thread), (pthread_attr_t *)(attr), \
    (void * (*)(void *))(func), (void *)(arg))
#else
#ifdef _WIN32
#define BEGINTHREAD(src, stack, func, arg, flag, id)         \
	(HANDLE)_beginthreadex((void *)(src), (unsigned)(stack), \
	(unsigned (_stdcall *)(void *))(func), (void *)(arg),    \
	(unsigned)(flag), (unsigned *)(id))
#endif
#endif



/* yomei fixed: translate __stdcall to __cdecl  */
#ifdef _WIN32
static unsigned __stdcall internal_start_thread( void * vp)
{
	mythread_t *t;
	if(vp==NULL)return 0;

	t=(mythread_t *)vp;
	return (unsigned)(((void * (*)(void *))(t->func))(t->arg));
}
#endif


mythread_t*
mythread_create(void* func, void* arg)
{
	mythread_t *t;
	
	t = (mythread_t *)malloc(sizeof(mythread_t));
	if (!t)
	{
		goto fail0;
	}

	t->func = func;
	t->arg = arg;

#ifdef HAVE_PTHREAD_H
	if (PTHREAD_CREATE(&t->hthread, 0, func, arg))
	{
		goto fail1;
	}
#else
#ifdef _WIN32
	{
		int id;
		HANDLE hnd;
		/* yomei fixed: this thread function must be a standard call.  */
		hnd = BEGINTHREAD(0, 0, internal_start_thread, t, 0, &id);
		if (!hnd)
		{
			goto fail1;
		}
		t->hthread = hnd;
	}
#endif
#endif
	return t;

fail1:
	if (t)
	{
		free(t);
		t = NULL;
	}
fail0:
	return t;
}



void
mythread_join(mythread_t* t)
{
	if (!t)
	{
		goto fail;
	}
#ifdef HAVE_PTHREAD_H
	pthread_join(t->hthread, NULL);
	free(t);
#else
#ifdef _WIN32
	WaitForSingleObject(t->hthread, INFINITE);
	CloseHandle(t->hthread);
	free(t);
#endif
#endif

fail:
	return;
}

void
mythread_exit(mythread_t* t)
{
	if (!t)
	{
		goto fail;
	}
#ifdef HAVE_PTHREAD_H
	pthread_detach(t->hthread);
	pthread_exit(NULL);
	free(t);
#else
#ifdef _WIN32
	_endthreadex(0);
	free(t);
#endif
#endif

fail:
	return;
}


/* usage */
#if 0
//#include "ysleep.h"
void func(char *s)
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		printf(s);
		Sleep(1000);
	}
}

int main()
{
	thread_t *s, *t;

#ifdef unix
	fflush(stdout);
	setbuf(stdout,NULL);
#endif

	s = thread_create(func, "0");
	
	Sleep(50);
	t = thread_create(func, "1");
	Sleep(50);
	
	
	thread_join(s);
	thread_join(t);
	Sleep(1000);
	return 0;
}
#endif


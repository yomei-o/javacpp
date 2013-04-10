/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mythread.h"
#include "ysleep.h"

#include "ThreadPool.h"



#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#define MAX_THREAD 10


void** ThreadPool::m_func=NULL;
void** ThreadPool::m_arg=NULL;
void** ThreadPool::m_list=NULL;
int* ThreadPool::m_flag=NULL;

ThreadPool::ThreadPool()
{
	m_func=(void**)malloc(sizeof(void*)*MAX_THREAD);
	m_list=(void**)malloc(sizeof(void*)*MAX_THREAD);
	m_arg=(void**)malloc(sizeof(void*)*MAX_THREAD);
	m_flag=(int*)malloc(sizeof(int)*MAX_THREAD);
	int i;
	for(i=0;i<MAX_THREAD;i++){
		m_func[i]=NULL;
		m_list[i]=NULL;
		m_arg[i]=NULL;
		m_flag[i]=0;
	}
}

ThreadPool::~ThreadPool()
{
	endall();

	if(m_func)free(m_func);
	m_func=NULL;
	if(m_arg)free(m_arg);
	m_arg=NULL;
	if(m_list)free(m_list);
	m_list=NULL;
	if(m_flag)free(m_flag);
	m_flag=NULL;

}


int ThreadPool::create(void* func,void* arg)
{
	int i;
	for(i=0;i<MAX_THREAD;i++){
		if(m_flag[i]==0 && m_list[i]!=NULL){
			mythread_join((mythread_t*)(m_list[i]));
			m_list[i]=NULL;
			m_flag[i]=0;
		}
	}
	for(i=0;i<MAX_THREAD;i++){
		if(m_flag[i]==0 && m_list[i]==NULL){
			char* p=NULL;
			m_flag[i]=1;
			m_arg[i]=arg;
			m_func[i]=func;
			p+=i;
			//m_list[i]=mythread_create((void*)run,(void*)i);
			m_list[i]=mythread_create((void*)run,(void*)p);
			return i;
		}
	}
	return -1;
}


int ThreadPool::join(int i)
{
	if(i==-1)return -1;
	if(m_flag[i]==0 || m_list[i]==NULL)return -1;

	mythread_join((mythread_t*)(m_list[i]));
	m_list[i]=NULL;
	m_flag[i]=0;
	return i;
}

void ThreadPool::sleep(int ms)
{
	ymsleep(ms);
}

void ThreadPool::endall()
{
	int i;
	for(i=0;i<MAX_THREAD;i++){
		if(m_list[i]!=NULL){
			mythread_join((mythread_t*)(m_list[i]));
			m_list[i]=NULL;
			m_flag[i]=0;
		}
	}
}

int ThreadPool::run(void* id)
{
	int i;
	char *p=NULL;
	//i=(int)id;
	i=(int)(((char*)id)-p);
	((void (*)(void*)) (m_func[i]))(m_arg[i]);
	m_flag[i]=0;
	return 0;
}

static ThreadPool threadpool;




#if 0

int f(char* arg)
{
	printf("%s start\n",arg);
	ThreadPool::sleep(5000);
	printf("%s end\n",arg);
	return 0;
}




main()
{
#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif
	printf("main start\n");
	ThreadPool::create((void*)f,"000"); 
	int id=ThreadPool::create((void*)f,"123"); 
	printf("id=%d\n",id);
	ThreadPool::join(id);

	printf("main end\n");
	return 0;
}

#endif

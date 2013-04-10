/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mylist.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif

struct mylist{
	char* key;
	MYLIST* next;
	MYLIST* now;
};

MYLIST* mylist_open()
{
	MYLIST* ret;
	ret=(MYLIST*)malloc(sizeof(MYLIST));
	memset(ret,0,sizeof(MYLIST));
	ret->now=ret;
	return ret;
}
void  mylist_close(MYLIST* o)
{
	MYLIST* tmp;
	while(1){
	if(o==NULL)break;
	if(o->key)free(o->key);
		tmp=o->next;
		free(o);
		o=tmp;
	}
}

void mylist_add(MYLIST* o,char *key)
{
	int sz;
	
	if(o==NULL || key==NULL)return;
	while(o->next!=NULL)o=o->next;
	sz=(int)strlen(key)+1;
	o->key=(char*)malloc(sz);
	strncpy(o->key,key,sz);
	o->next=(MYLIST*)malloc(sizeof(MYLIST));
	memset(o->next,0,sizeof(MYLIST));
}

static int mylist_hasmore(MYLIST* o)
{
	if(o==NULL)return 0;
	if(o->now==NULL)return 0;
	if(o->now->key)return 1;
	return 0;
}
static char* mylist_next(MYLIST* o)
{
	char *ret;
	if(o==NULL)return NULL;
	if(o->now==NULL)return NULL;
	ret=o->now->key;
	o->now=o->now->next;
	return ret;

}

MYLIST* mylist_dup(MYLIST* o)
{
	MYLIST* d=NULL;
	MYLIST* ret=NULL;
	if(o==NULL)return NULL;
	d=(MYLIST*)malloc(sizeof(MYLIST));
	memset(d,0,sizeof(MYLIST));
	d->now=d;
	ret=d;
	while(1){
		if(o->key)
		{
			int sz;
			sz=(int)strlen(o->key)+1;
			d->key=(char*)malloc(sz);
			strncpy(d->key,o->key,sz);
		}
		if(o->next==NULL)break;
		d->next=(MYLIST*)malloc(sizeof(MYLIST));
		memset(d->next,0,sizeof(MYLIST));
		d=d->next;
		o=o->next;
	}
	return ret;
}

int mylist_size(MYLIST* o)
{
	int ret=0;

	if(o==NULL)return ret;
	while(1){
		if(o->next==NULL)break;
		o=o->next;
		ret++;
	}
	return ret;
}

char* mylist_get(MYLIST* o,int n)
{
	int ct=0;
	if(o==NULL)return NULL;
	while(1){
		if(ct==n){
			return o->key;
		}
		if(o->next==NULL)break;
		o=o->next;
		ct++;
	}
	return NULL;
}

#if 0

main(){
	MYLIST *m,*n;


#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif



	m=mylist_open();

	mylist_add(m,"123");
	mylist_add(m,"456");
	mylist_add(m,"789");
	n=mylist_dup(m);


	printf("m hasmore=%d\n",mylist_hasmore(m));
	printf("m next=%s\n",mylist_next(m));
	printf("\n");
	printf("m hasmore=%d\n",mylist_hasmore(m));
	printf("m next=%s\n",mylist_next(m));
	printf("\n");
	printf("m hasmore=%d\n",mylist_hasmore(m));
	printf("m next=%s\n",mylist_next(m));
	printf("\n");
	printf("m hasmore=%d\n",mylist_hasmore(m));
	printf("m next=%s\n",mylist_next(m));
	printf("\n");

	printf("\n");
	printf("\n");

	printf("n hasmore=%d\n",mylist_hasmore(n));
	printf("n next=%s\n",mylist_next(n));
	printf("\n");
	printf("n hasmore=%d\n",mylist_hasmore(n));
	printf("n next=%s\n",mylist_next(n));
	printf("\n");
	printf("n hasmore=%d\n",mylist_hasmore(n));
	printf("n next=%s\n",mylist_next(n));
	printf("\n");
	printf("n hasmore=%d\n",mylist_hasmore(n));
	printf("n next=%s\n",mylist_next(n));
	printf("\n");

	mylist_close(m);
	mylist_close(n);
}

#endif


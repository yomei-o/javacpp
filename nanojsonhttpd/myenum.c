/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "myenum.h"


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


struct myenum{
	char* key;
	MYENUM* next;
	MYENUM* now;
};

MYENUM* myenum_open()
{
	MYENUM* ret;
	ret=(MYENUM*)malloc(sizeof(MYENUM));
	memset(ret,0,sizeof(MYENUM));
	ret->now=ret;
	return ret;
}
void  myenum_close(MYENUM* o)
{
	MYENUM* tmp;
	while(1){
	if(o==NULL)break;
	if(o->key)free(o->key);
		tmp=o->next;
		free(o);
		o=tmp;
	}
}

void myenum_add(MYENUM* o,char *key)
{
	int sz;
	if(o==NULL || key==NULL)return;
	while(o->next!=NULL)o=o->next;
	sz=(int)strlen(key)+1;
	o->key=(char*)malloc(sz);
	strncpy(o->key,key,sz);
	o->next=(MYENUM*)malloc(sizeof(MYENUM));
	memset(o->next,0,sizeof(MYENUM));
}
int myenum_hasmore(MYENUM* o)
{
	if(o==NULL)return 0;
	if(o->now==NULL)return 0;
	if(o->now->key)return 1;
	return 0;
}
char* myenum_next(MYENUM* o)
{
	char *ret;
	if(o==NULL)return NULL;
	if(o->now==NULL)return NULL;
	ret=o->now->key;
	o->now=o->now->next;
	return ret;

}

MYENUM* myenum_dup(MYENUM* o)
{
	MYENUM* d=NULL;
	MYENUM* ret=NULL;
	if(o==NULL)return NULL;
	d=(MYENUM*)malloc(sizeof(MYENUM));
	memset(d,0,sizeof(MYENUM));
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
		d->next=(MYENUM*)malloc(sizeof(MYENUM));
		memset(d->next,0,sizeof(MYENUM));
		d=d->next;
		o=o->next;
	}
	return ret;
}

#if 0

main(){
	MYENUM *m,*n;


#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif



	m=myenum_open();

	myenum_add(m,"123");
	myenum_add(m,"456");
	myenum_add(m,"789");
	n=myenum_dup(m);


	printf("m hasmore=%d\n",myenum_hasmore(m));
	printf("m next=%s\n",myenum_next(m));
	printf("\n");
	printf("m hasmore=%d\n",myenum_hasmore(m));
	printf("m next=%s\n",myenum_next(m));
	printf("\n");
	printf("m hasmore=%d\n",myenum_hasmore(m));
	printf("m next=%s\n",myenum_next(m));
	printf("\n");
	printf("m hasmore=%d\n",myenum_hasmore(m));
	printf("m next=%s\n",myenum_next(m));
	printf("\n");

	printf("\n");
	printf("\n");

	printf("n hasmore=%d\n",myenum_hasmore(n));
	printf("n next=%s\n",myenum_next(n));
	printf("\n");
	printf("n hasmore=%d\n",myenum_hasmore(n));
	printf("n next=%s\n",myenum_next(n));
	printf("\n");
	printf("n hasmore=%d\n",myenum_hasmore(n));
	printf("n next=%s\n",myenum_next(n));
	printf("\n");
	printf("n hasmore=%d\n",myenum_hasmore(n));
	printf("n next=%s\n",myenum_next(n));
	printf("\n");

	myenum_close(m);
	myenum_close(n);
}

#endif


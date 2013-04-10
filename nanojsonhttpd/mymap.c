/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#include "mymap.h"

struct mymap{
	char* key;
	char* val;
	MYMAP* next;
};

MYMAP* mymap_alloc()
{
	MYMAP* ret=(MYMAP*)malloc(sizeof(MYMAP));
	if(ret==NULL)return NULL;
	memset(ret,0,sizeof(MYMAP));
	return ret;
}

MYMAP* mymap_delTop(MYMAP* m)
{
	MYMAP* ret=NULL;
	if(m==NULL)return NULL;
	ret=m->next;
	if(m->key)free(m->key);
	if(m->val)free(m->val);
	free(m);
	return ret;
}

void mymap_addTail(MYMAP* m,char* key,char* val)
{
	int sz;
	if(m==NULL || key==NULL || val==NULL)return;
	while(m->next!=NULL)m=m->next;

	sz=(int)strlen(key)+1;
	m->key=(char*)malloc(sz);
	strncpy(m->key,key,sz);

	sz=(int)strlen(val)+1;
	m->val=(char*)malloc(sz);
	strncpy(m->val,val,sz);
	m->next=(MYMAP*)malloc(sizeof(MYMAP));
	memset(m->next,0,sizeof(MYMAP));
}

void mymap_delete(MYMAP* m)
{
	while(1){
		if(m==NULL)return;
		m=mymap_delTop(m);
	}
}

void mymap_put(MYMAP* m,char* key,char* val)
{
	int sz;
	if(m==NULL || key==NULL || val==NULL)return;
	while(m->next)
	{
		if(strcmp(key,m->key)==0){
			free(m->val);

			sz=(int)strlen(val)+1;
			m->val=(char*)malloc(sz);
			strncpy(m->val,val,sz);
			return;
		}
		m=m->next;
	}
	mymap_addTail(m,key,val);
}

char* mymap_get(MYMAP* m,char* key)
{
	if(m==NULL || key==NULL)return NULL;
	while(m->next)
	{
		if(strcmp(key,m->key)==0){
			return m->val;
		}
		m=m->next;
	}
	return NULL;
}


MYMAP* mymap_copy(MYMAP* m)
{
	MYMAP* ret;
	if(m==NULL)return NULL;
	ret=mymap_alloc();

	while(m->next)
	{
		mymap_addTail(ret,m->key,m->val);
		m=m->next;
	}
	return ret;
}

int mymap_getNums(MYMAP* m)
{
	int ret=0;
	if(m==NULL)return ret;
	while(m->next)
	{
		ret++;
		m=m->next;
	}
	return ret;
}

char* mymap_getIndexOfKey(MYMAP* m,int n)
{
	if(m==NULL|| n<0)return NULL;
	while(m->next){
		if(n==0)
		{
			return m->key;
		}
		n--;
		m=m->next;
	}
	return NULL;
}
char* mymap_getIndexOfValue(MYMAP* m,int n)
{
	if(m==NULL|| n<0)return NULL;
	while(m->next){
		if(n==0)
		{
			return m->val;
		}
		n--;
		m=m->next;
	}
	return NULL;
}


#if 0
main(int argc,char* argv[]){
	
	MYMAP* m;
	MYMAP* n;

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	m=mymap_alloc();
	mymap_put(m,"111","aaaaa");
	mymap_put(m,"222","aaaaabbb");
	mymap_put(m,"222","aaaaabbb");
	mymap_put(m,"222","aaaaabbb");
	mymap_put(m,"222","aaaaaxxx");
	mymap_put(m,"333","aaaaabbbwssdsdsds3333");
	mymap_put(m,"555","aaaaabbb444444");
	mymap_put(m,"444","aaaaabbb555555");
	mymap_put(m,"111","bbb");
	printf("%s\n",mymap_get(m,"222"));
	printf("%s\n",mymap_get(m,"111"));
	printf("%s\n",mymap_get(m,"333"));
	printf("%s\n",mymap_get(m,"559"));
	n=mymap_copy(m);
	printf("%d\n",mymap_getNums(m));
	printf("%d  %s  %s\n",0,mymap_getIndexOfKey(m,0),mymap_getIndexOfValue(m,0));
	printf("%d  %s  %s\n",1,mymap_getIndexOfKey(m,1),mymap_getIndexOfValue(m,1));
	printf("%d  %s  %s\n",2,mymap_getIndexOfKey(m,2),mymap_getIndexOfValue(m,2));
	printf("%d  %s  %s\n",3,mymap_getIndexOfKey(m,3),mymap_getIndexOfValue(m,3));
	printf("%d  %s  %s\n",5,mymap_getIndexOfKey(m,5),mymap_getIndexOfValue(m,5));

	mymap_delete(m);
	mymap_delete(n);
}
#endif

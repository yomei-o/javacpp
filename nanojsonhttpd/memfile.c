/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memfile.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define DEF_BUF_SZ 1024*32
//#define DEF_BUF_SZ 32


struct memfile{
	int auto_resize;
	int buf_size;
	int size;
	int pos;
	unsigned char* data;

};


MEMFILE* memfile_open(int sz)
{
	MEMFILE* ret;
	ret=(MEMFILE*)malloc(sizeof(MEMFILE));
	memset(ret,0,sizeof(MEMFILE));

	ret->buf_size=sz;
	if(ret->buf_size<=0){
		ret->auto_resize=1;
		ret->buf_size=DEF_BUF_SZ;
	}
	ret->data=(unsigned char*)malloc(ret->buf_size);
	
	return ret;
}

void memfile_close(MEMFILE* m)
{
	if(m==NULL)return;
	free(m->data);
	free(m);
}

void memfile_write(MEMFILE* m,void* buf,int sz)
{
	if(m==NULL)return;
	if(m->pos+sz>m->buf_size)
	{
		if(m->auto_resize==0)sz=m->buf_size-m->pos;
		else{
			m->buf_size=m->pos+m->buf_size+DEF_BUF_SZ-1;
			m->buf_size&=~(DEF_BUF_SZ-1);
			//printf("realloc %d\n",m->buf_size);
			m->data=(unsigned char*)realloc(m->data,m->buf_size);
		}
	}
	if(sz>0){
		//printf("write %d\n",sz);
		memcpy(m->data+m->pos,buf,sz);
		m->pos+=sz;
		if(m->size<m->pos)m->size=m->pos;
	}
}

void memfile_seek(MEMFILE* m,int pos)
{
	if(m==NULL)return;
	if(pos>=m->buf_size)pos=m->buf_size;
	m->pos=pos;
}

int memfile_tell(MEMFILE* m)
{
	if(m==NULL)return -1;
	return m->pos;
}

int memfile_size(MEMFILE* m)
{
	if(m==NULL)return -1;
	return m->size;
}

int memfile_read(MEMFILE* m,void* buf,int sz)
{
	if(m==NULL)return -1;
	if(m->pos+sz>m->size)sz=m->size-m->pos;
	if(sz>0){
		//printf("read %d\n",sz);
		memcpy(buf,m->data+m->pos,sz);
		m->pos+=sz;
	}
	return sz;
}

void* memfile_data(MEMFILE* m)
{
	if(m==NULL)return NULL;
	return m->data;
}


MEMFILE* memfile_copy(char* p,int sz)
{
	MEMFILE* ret;
	ret=(MEMFILE*)malloc(sizeof(MEMFILE));
	memset(ret,0,sizeof(MEMFILE));

	ret->buf_size=sz;
	ret->size=sz;
	ret->data=(unsigned char*)malloc(ret->buf_size);
	memcpy(ret->data,p,sz);	
	return ret;
}


MEMFILE* memfile_dup(MEMFILE* m)
{
	MEMFILE* ret;

	if(m==NULL)return NULL;

	ret=(MEMFILE*)malloc(sizeof(MEMFILE));
	memset(ret,0,sizeof(MEMFILE));

	ret->buf_size=m->buf_size;
	ret->size=m->size;
	ret->pos=m->pos;

	ret->data=(unsigned char*)malloc(ret->buf_size);
	memcpy(ret->data,m->data,m->size);	

	ret->auto_resize=m->auto_resize;

	return ret;
}


#if 0
main(){

	MEMFILE* m=NULL,*n=NULL;
	char p[]={0,1,2,3,4,5,6,7,8,9,10};
	int ret=0;

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif



	m=memfile_open(0);
	memfile_write(m,p,5);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	memfile_write(m,p,10);	
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	memfile_write(m,p,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	memfile_write(m,p,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	memfile_write(m,p,1);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	memfile_seek(m,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	memfile_write(m,p,5);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));

	ret=memfile_read(m,p,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	ret=memfile_read(m,p,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	ret=memfile_read(m,p,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));
	ret=memfile_read(m,p,10);
	printf("sz=%d\n",memfile_size(m));
	printf("tell=%d\n",memfile_tell(m));



	memfile_close(m);
}
#endif




#if 0
main(){

	MEMFILE* m=NULL,*n=NULL;
	char p[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0};
	int ret=0;

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif



	m=memfile_open(0);
	memfile_write(m,p,5);
	memfile_write(m,p,11);

	n=memfile_dup(m);

	
	printf(">>%s\n<<",memfile_data(m));

	memfile_close(m);
	memfile_close(n);
}
#endif





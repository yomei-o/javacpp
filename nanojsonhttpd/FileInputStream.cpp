/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>

#include "String_.h"
#include "File.h"

#include "FileInputStream.h"
#include "fdup2.h"

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


FileInputStream::FileInputStream()
{
	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;

}

FileInputStream::FileInputStream(int id)
{
	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;
}

FileInputStream::FileInputStream(String&  str)
{
	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;

	if(p_open)handle=p_open((char*)str);
}

FileInputStream::FileInputStream(char*  str)
{
	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;

	if(p_open)handle=p_open((char*)str);
}


FileInputStream::FileInputStream(File&  ff)
{
	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;
	if(p_open)handle=p_open((char*)(ff.fn));
}


void* FileInputStream::s_open(void* vp)
{
	FILE* fp=NULL;
	if(vp==NULL)return NULL;
//	printf("FileInputStream::s_open\n");
	fp=fopen((char*)vp,"rb");
	return fp;
}

void* FileInputStream::s_dup(void* vp)
{
	void* fd;
//	printf("FileInputStream::s_dup\n");
	fd=fdup((FILE*)vp,"rb");
	return fd;
}

void FileInputStream::s_close(void* vp)
{
//	printf("FileInputStream::s_close\n");
	if(vp==NULL)return;
	fclose((FILE*)vp);
}

void FileInputStream::s_reset(void* vp)
{
	if(vp==NULL)return;
	fseek((FILE*)vp,0,SEEK_SET);
}

int FileInputStream::s_read(void* vp,char* buf,int off,int sz)
{
	if(vp==NULL)return 0;
	return (int)fread(buf+off,1,sz,(FILE*)vp);
}

int FileInputStream::s_skip(void* vp,int sz)
{
	int ret=0;
	if(vp==NULL)return 0;
	ret=fseek((FILE*)vp,sz,SEEK_CUR);
	if(ret==-1)return 0;
	return sz;
}


FileInputStream& FileInputStream::operator =(FileInputStream *ff)
{
	p_open=ff->s_open;
	p_close=ff->s_close;
	p_read=ff->s_read;
	p_reset=ff->s_reset;
	p_dup=ff->s_dup;
	handle=ff->handle;
	p_skip=ff->s_skip;
	if(p_dup)handle=p_dup(handle);
	delete ff;
	return *this;
}




FileInputStream::~FileInputStream()
{
}

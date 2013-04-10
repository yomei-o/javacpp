/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>

#include "String_.h"
#include "File.h"

#include "FileOutputStream.h"
#include "fdup2.h"

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


FileOutputStream::FileOutputStream()
{
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	isappend=false;
}

FileOutputStream::FileOutputStream(int id)
{
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	isappend=false;
}

FileOutputStream::FileOutputStream(String&  str)
{
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	isappend=false;

	if(p_open)handle=p_open((char*)str);
}

FileOutputStream::FileOutputStream(char*  str)
{
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	isappend=false;

	if(p_open)handle=p_open((char*)str);
}


FileOutputStream::FileOutputStream(File&  ff)
{
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	isappend=false;
	if(p_open)handle=p_open((char*)(ff.fn));
}

FileOutputStream::FileOutputStream(char*  str,bool append)
{
	isappend=append;
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	if(isappend){
		p_open=s_open2;
		p_dup=s_dup2;
	}

	if(p_open)handle=p_open((char*)str);
}

FileOutputStream::FileOutputStream(String&  str,bool append)
{
	isappend=append;
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	if(isappend){
		p_open=s_open2;
		p_dup=s_dup2;
	}

	if(p_open)handle=p_open((char*)str);
}

void* FileOutputStream::s_open(void* vp)
{
	FILE* fp=NULL;
	if(vp==NULL)return NULL;
//	printf("FileOutputStream::s_open\n");
	fp=fopen((char*)vp,"wb");
	return fp;
}

void* FileOutputStream::s_open2(void* vp)
{
	FILE* fp=NULL;
	if(vp==NULL)return NULL;
//	printf("FileOutputStream::s_open\n");
	fp=fopen((char*)vp,"ab");
	return fp;
}
void* FileOutputStream::s_dup(void* vp)
{
	void* fd;
//	printf("FileOutputStream::s_dup\n");
	fd=fdup((FILE*)vp,"wb");
	return fd;
}
void* FileOutputStream::s_dup2(void* vp)
{
	void* fd;
//	printf("FileOutputStream::s_dup\n");
	fd=fdup((FILE*)vp,"ab");
	return fd;
}


void FileOutputStream::s_flush(void* vp)
{
}

void FileOutputStream::s_close(void* vp)
{
//	printf("FileOutputStream::s_close\n");
	if(vp==NULL)return;
	fclose((FILE*)vp);
}


int FileOutputStream::s_write(void* vp,char* buf,int off,int sz)
{
	if(vp==NULL)return -1;
	fwrite(buf+off,1,sz,(FILE*)vp);
	return sz;
}


FileOutputStream& FileOutputStream::operator =(FileOutputStream *ff)
{
	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	isappend=ff->isappend;
	if(isappend){
		p_open=s_open2;
		p_dup=s_dup2;
	}
	handle=ff->handle;
	if(p_dup)handle=p_dup(handle);
	delete ff;
	return *this;
}


FileOutputStream::~FileOutputStream()
{
}

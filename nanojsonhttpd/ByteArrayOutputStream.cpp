/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>


#include "ByteArrayOutputStream.h"
#include "memfile.h"

ByteArrayOutputStream::ByteArrayOutputStream()
{
//	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	handle=s_open(0);
}

ByteArrayOutputStream::ByteArrayOutputStream(int id)
{
//	p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	if(id<=0)
	{
		handle=NULL;
	}else{
		handle=s_open(id);
	}
}




ByteArrayOutputStream::~ByteArrayOutputStream()
{
}

int ByteArrayOutputStream::size()
{
	if(handle==NULL)return -1;
	return memfile_size((MEMFILE*)handle);
}

char* ByteArrayOutputStream::toByteArray()
{
	int sz;
	char* p=NULL;
	
	if(handle==NULL)return NULL;
	
	sz=memfile_size((MEMFILE*)handle);
	p=new char[sz];
	memcpy(p,memfile_data((MEMFILE*)handle),sz);
	return p;
}

void* ByteArrayOutputStream::s_open(int sz)
{
	return memfile_open(sz);
}

void* ByteArrayOutputStream::s_dup(void* vp)
{
	if(vp==NULL)return NULL;
	return memfile_dup((MEMFILE*)vp);
}


void ByteArrayOutputStream::s_flush(void* vp)
{
}

void ByteArrayOutputStream::s_close(void* vp)
{
	if(vp==NULL)return;
	memfile_close((MEMFILE*)vp);
}


int ByteArrayOutputStream::s_write(void* vp,char* buf,int off,int sz)
{
	if(vp==NULL)return -1;
	memfile_write((MEMFILE*)vp,(void*)(buf+off),sz);
	return sz;
}


ByteArrayOutputStream& ByteArrayOutputStream::operator =(ByteArrayOutputStream *ff)
{
	//p_open=s_open;
	p_close=s_close;
	p_write=s_write;
	p_flush=s_flush;
	p_dup=s_dup;
	handle=ff->handle;
	if(p_dup)handle=p_dup(handle);
	delete ff;
	return *this;
}



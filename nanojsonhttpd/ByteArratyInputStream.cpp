/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>

#include "ByteArrayInputStream.h"
#include "memfile.h"

ByteArrayInputStream::ByteArrayInputStream()
{
	handle=NULL;
//	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;
}

ByteArrayInputStream::ByteArrayInputStream(int id)
{
	handle=NULL;
//	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;
}

ByteArrayInputStream::ByteArrayInputStream(char* dd,int oo,int ss)
{
//	p_open=s_open;
	p_close=s_close;
	p_read=s_read;
	p_reset=s_reset;
	p_dup=s_dup;
	p_skip=s_skip;

	handle=s_open(((char*)dd)+oo,ss);
}

ByteArrayInputStream::~ByteArrayInputStream()
{
}


void* ByteArrayInputStream::s_open(void* vp,int sz)
{
	if(vp==NULL || sz<=0)return NULL;
	return memfile_copy((char*)vp,sz);
}

void* ByteArrayInputStream::s_dup(void* vp)
{
	if(vp==NULL)return NULL;
	return memfile_dup((MEMFILE*)vp);
}

void ByteArrayInputStream::s_close(void* vp)
{
	if(vp==NULL)return;
	memfile_close((MEMFILE*)vp);
}

void ByteArrayInputStream::s_reset(void* vp)
{
}

int ByteArrayInputStream::s_skip(void* vp,int sz)
{
	return 0;
}

int ByteArrayInputStream::s_read(void* vp,char* buf,int off,int sz)
{
	if(vp==NULL)return -1;
	return memfile_read((MEMFILE*)vp,(void*)(buf+off),sz);
}


ByteArrayInputStream& ByteArrayInputStream::operator =(ByteArrayInputStream *ff)
{
	//p_open=ff->s_open;
	p_close=ff->s_close;
	p_read=ff->s_read;
	p_reset=ff->s_reset;
	p_dup=ff->s_dup;
	p_skip=ff->s_skip;
	handle=ff->handle;
	if(p_dup)handle=p_dup(handle);
	delete ff;
	return *this;
}





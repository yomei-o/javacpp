/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "dirtoolutf.h"

#include "File.h"
#include "String_.h"

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#define null 0

File::File():fn(0)
{
}

File::File(int id):fn(0)
{
}

File::File(char* p):fn(p)
{
}

File::File(String&  str):fn(0)
{
	fn=str;
}

File::File(const File&  f):fn(0)
{
	fn=f.fn;
}


File& File::operator =(File *f)
{
	if(f==NULL)goto end;
	fn=f->fn;
	delete f;
end:
	return *this;
}


File& File::operator =(File f)
{
	fn=f.fn;
	return *this;
}

#ifndef JAVA
bool File::operator ==(int a)
{
	if(fn==NULL)return true;
	return false;
}
#endif

#ifndef JAVA
bool File::operator !=(int a)
{
	if(fn==NULL)return false;
	return true;
}
#endif


File::~File()
{
}

longlong File::lastModified(){
	char* p=fn;
	MYSTAT ms;
	int l;
	longlong ret=0;

	if(fn==NULL)return ret;
	if(p[0]==0)return ret;
	l=my_stat(p,&ms);
	if(l==-1)return ret;
	ret=ms.mtime;
	ret*=1000;
	
	return ret;
}

longlong File::length()
{
	char* p=fn;

	long sz=0;
	FILE* fp;

	if(fn==NULL)return 0;
	if(p[0]==0)return 0;

	fp=fopen(p,"rb");
	if(fp==NULL)return 0;

	fseek(fp,0,SEEK_END);
	sz=ftell(fp);
	fclose(fp);


	return (longlong)sz;
}


bool File::exists()
{
	char* p=fn;
	MYSTAT ms;
	int ret;

	if(fn==NULL)return false;
	if(p[0]==0)return false;
	ret=my_stat(p,&ms);
	if(ret==-1)return false;
	return true;

}

bool File::isFile()
{
	char* p=fn;
	MYSTAT ms;
	int ret;

	if(fn==NULL)return false;
	if(p[0]==0)return false;
	ret=my_stat(p,&ms);
	if(ret==-1)return false;
	if((ms.mode & MYS_IFDIR)==0)return true;
	return false;
}

bool File::isDirectory()
{
	char* p=fn;
	MYSTAT ms;
	int ret;

	if(fn==NULL)return false;
	if(p[0]==0)return false;
	ret=my_stat(p,&ms);
	if(ret==-1)return false;
	if((ms.mode & MYS_IFDIR)!=0)return true;
	return false;
}


bool File::deleteFile()
{
	char* p=fn;
	MYSTAT ms;
	int ret;

	if(fn==NULL)return false;
	if(p[0]==0)return false;
	ret=my_stat(p,&ms);
	if(ret==-1)return false;
	if((ms.mode & MYS_IFDIR)!=0){
		ret=my_rmdir(p);
	}else{
		ret=my_rm(p);
	}
	if(ret==-1)return false;
	return true;
}

String File::getName()
{
	return fn;
}


bool File::mkdir()
{
	char* p=fn;
	int ret;

	if(fn==NULL)return false;
	if(p[0]==0)return false;
	ret=my_mkdir(p);
	if(ret==-1)return false;
	return true;
}

bool File::renameTo(File & f)
{
	char* p=fn;
	char* q=NULL;
	int ret;

	if(fn==NULL)return false;
	if(p[0]==0)return false;
	
	if(f.fn==NULL)return false;
	q=f.fn;
	if(q[0]==0)return false;

	ret=myrename(p,q);
	if(ret==-1)return false;
	return true;
}

String** File::list()
{
	String** ret=NULL;
	char buf[2048];
	int len=0;
	int st=0,i=0,ct=0;
	MYDIR* d=NULL;
	char* p=fn;
	String str=null;

	str="hoge";

	if(fn==NULL)return ret;
	if(p[0]==0)return ret;

	d=my_open_dir(p);
	if(d==NULL)return ret;
	do{
		buf[0]=0;
		st=my_read_dir(d,buf,sizeof(buf));
		if(st==0)break;
		if(buf[0]=='.' && buf[1]==0)continue;
		if(buf[0]=='.' && buf[1]=='.' && buf[2]==0)continue;
		len++;
	}while(true);
	my_close_dir(d);
	if(len==0)return ret;

	d=my_open_dir(p);
	if(d==NULL)return ret;

	ret=new String*[len+1];	
	for(i=0;i<len+1;i++)ret[i]=NULL;

	for(i=0,ct=0;ct<len;i++){
		buf[0]=0;
		st=my_read_dir(d,buf,sizeof(buf));
		if(st==0)break;
		if(buf[0]=='.' && buf[1]==0)continue;
		if(buf[0]=='.' && buf[1]=='.' && buf[2]==0)continue;
		ret[ct]=new String(buf);
		ct++;
	}
	my_close_dir(d);
	return ret;
}

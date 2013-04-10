/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#define _DIRTOOL_C_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <sys/utime.h>
#endif
#ifdef unix
#include <utime.h>
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "dirtoolutf.h"
//#include "kanji.h"

static void multibytetoutf8(char* d,int dlen,char* s){
#ifdef _WIN32
	wchar_t tmp[1024];
	if(d==NULL || s==NULL)return;
	*d=0;

	memset(tmp,0,1024*sizeof(wchar_t));
	memset(d,0,dlen);

	MultiByteToWideChar(CP_OEMCP,0,s,-1,tmp,1024-1);
	WideCharToMultiByte(CP_UTF8,0,tmp,-1,d,dlen-1,NULL,NULL);
#else
	strncpy(d,s,dlen);
	d[dlen-1]=0;
#endif
}

static void utf8tomultibyte(char* d,int dlen,char* s){
#ifdef _WIN32
	wchar_t tmp[1024];
	if(d==NULL || s==NULL)return;
	*d=0;

	memset(tmp,0,1024*sizeof(wchar_t));
	memset(d,0,dlen);

	MultiByteToWideChar(CP_UTF8,0,s,-1,tmp,1024-1);
	WideCharToMultiByte(CP_OEMCP,0,tmp,-1,d,dlen-1,NULL,NULL);
#else
	strncpy(d,s,dlen);
	d[dlen-1]=0;
#endif
}



MYDIR* my_open_dir(char* filen)
{
	MYDIR* vp=NULL;

#ifdef _WIN32	
	MYDIR a;
	char my_path_local[1024];
	char tmp[1024];
	intptr_t ret;

	if(filen==NULL)return NULL;
	strncpy(my_path_local,filen,1010);
	strncat(my_path_local,"/*.*",5);

	//ret=_findfirst(my_path_local,&(a.fileinfo));
	utf8tomultibyte(tmp,sizeof(tmp),my_path_local);
	ret=_findfirst(tmp,&(a.fileinfo));

	if(ret==-1)return NULL;

	a.flag=MYDIR_FLAG_FIRST;
	a.h=ret;

	vp=malloc(sizeof(MYDIR));
	if(vp==NULL)
	{
		_findclose(ret);
		return NULL;
	}
	*vp=a;
#endif

#ifdef unix
	DIR* d;
	if(filen==NULL)return NULL;
	d=(DIR*)((void*)opendir(filen));
	if(d==NULL)return NULL;
	vp=(MYDIR*)malloc(sizeof(MYDIR));
	if(vp==NULL)
	{
		closedir(d);
		return NULL;
	}
	vp->dir=d;
	vp->flag=0;
#endif
	return vp;
}



void my_close_dir(MYDIR* vp)
{
	if(vp==NULL)return;
#ifdef _WIN32
	_findclose(vp->h);
#endif

#ifdef unix
	closedir( vp->dir);
#endif
	free(vp);
}



int my_read_dir2(MYDIR* vp,char* buf,int len,int *flag)
{
#ifdef _WIN32
	int ret;
	char tmp[1024];

	if(vp==NULL || buf==NULL)return 0;
	if(vp->flag==MYDIR_FLAG_FIRST)
	{
		goto next;
	}
	ret=_findnext( vp->h , &(vp->fileinfo));
	if(ret==-1)return 0;
next:
	multibytetoutf8(tmp,sizeof(tmp),vp->fileinfo.name);
	if((int)strlen(tmp) +1 >len)return 0;

	vp->flag=MYDIR_FLAG_NEXT;
	strncpy(buf,tmp,len);

	if(flag)
	{
		if(vp->fileinfo.attrib & _A_SUBDIR)*flag=1;
		else *flag=0;
	}
	return 1;
#endif

#ifdef unix
	struct dirent *de;
	struct dirent* pde=NULL;
	char tmp[4096];

	de = (struct dirent *)tmp;
	
	readdir_r(vp->dir, de, &pde);
	if(flag)
	{
	if(de->d_type==DT_DIR)*flag=1;
	else *flag=0;
	}
	if(pde==NULL)return 0;
	if((int)strlen(de->d_name) + 1 > len) return 0;
	strncpy(buf,de->d_name,len);
	return 1;
#endif
}

int my_read_dir(MYDIR* vp,char* buf,int len)
{
	return my_read_dir2(vp,buf,len,NULL);
}




int my_isown_dir(MYDIR *vp,char* buf)
{
	if(strcmp(buf,".")==0)return 1;
	return 0;
}

int my_isparent_dir(MYDIR *vp,char*buf)
{
	if(strcmp(buf,"..")==0)return 1;
	return 0;
}

int my_ischid_dir(MYDIR *vp,char*buf)
{
	if(strcmp(buf,".")==0)return 0;
	if(strcmp(buf,"..")==0)return 0;
	return 1;
}

int my_mkdir( char *dirname )
{
	/* success:0  fail:-1 */

#if defined(_WIN32)
	char tmp[1024];
	utf8tomultibyte(tmp,sizeof(tmp),dirname);
	return _mkdir( tmp );
#endif

#ifdef unix
//	printf("unix_mkdir(%s)\n", dirname);
	return mkdir( dirname, 0777 );
#endif
}


/* directoryの削除 */
/* 0:success, 1-1:failure-> errno */
int my_rmdir( char *dirname )
{
	/* success:0  fail:-1 */

#if defined(_WIN32)
	char tmp[1024];
	utf8tomultibyte(tmp,sizeof(tmp),dirname);
	return _rmdir( tmp );
#endif

#ifdef unix
//	printf("unix_mkdir(%s)\n", dirname);
	return rmdir( dirname );
#endif
}



/* 指定された絶対パスはディレクトリかどうか */
/* DIRの時は1, fileは0, 失敗は-1 を返す */
int my_isdir( char *path )
{
	struct stat sbuf;     /*  ステータス情報 */
	char tmp[4096];
	utf8tomultibyte(tmp,sizeof(tmp),path);

	if( stat( tmp, &sbuf) != 0 ){
		return -1;
	}
#ifdef unix
	if( S_ISDIR(sbuf.st_mode) ){
		return 1;
	}
#endif
#ifdef _WIN32
	if( sbuf.st_mode & _S_IFDIR ){
		return 1;
	}
#endif
	return 0;
}

/* 作業ディレクトリの変更に成功すると 0 を返します。
エラーが発生すると -1 を返し、グローバル変数 errno に
ENOENT を設定して、指定されたパス名が見つからなかったことを示します。 */
int my_chdir( char *dirname )
{
#ifdef _WIN32
	char tmp[4096];
	utf8tomultibyte(tmp,sizeof(tmp),dirname);
	return _chdir( tmp );
#endif
#ifdef unix
	return chdir( dirname );
#endif
}

/* path文字列のディレクトリを１つ上げる */
/* 戻り値 success:0 failure:1 */
int my_dirupper( char *dirname )
{
	char *p;

	if( !dirname ){
		return 1;
	}
		
	p = dirname;

	/* 最後が '/'または'\\'の場合は消しておく */
	while( *p != '\0' ){
		p++;
	}
	if( (p - dirname) <= 1 ){
		return 1;
	}
		
	if( ( *(p-1) == '/' ) || ( *(p-1) == '\\' ) ){
#ifdef _WIN32
		if( ( (p - dirname) > 1 ) && ( *(p-2) == ':' ) ){
			return 1;
		}else{
#endif
		
			*(p-1) = '\0';
			p--;
#ifdef _WIN32
		}
#endif
	}

	while( p > dirname ){
		if( (*p == '/') || (*p == '\\') ){
			if( p != dirname ){
#ifdef _WIN32
				if( (( p - dirname ) >= 1 ) && ( *(p-1) == ':' ) ){
					break;
				}
#endif
				if( ( (*(p-1) == '/') || (*(p-1) == '\\') ) && ( *(p-2) == ':') ){
					break;
				}
				*p = '\0';
			}
			break;
		}
		*p = '\0';
		p--;
	}
	return 0;
}

/* stat()の共用関数 */
/* 戻り値 success:0 failure:-1 */
int my_stat( char *path, MYSTAT *buf )
{
	int ret = -1;
	char tmp[4096];

#ifdef _WIN32
	struct _stat stt;
#endif
#ifdef unix
	struct stat stt;
#endif

	if( !path || !buf ){
		fprintf(stderr, "error:[%s]:L%d -%s\n", __FILE__, __LINE__, __DATE__ );
		return ret;
	}

	utf8tomultibyte(tmp,sizeof(tmp),path);
	
#ifdef _WIN32
	ret = _stat( tmp, &stt );
#endif

#ifdef unix
	ret = stat( tmp, &stt); 
#endif

	buf->mode = (unsigned short)(stt.st_mode);
	buf->size = (unsigned int)(stt.st_size);
	buf->atime = (unsigned int)(stt.st_atime);
	buf->mtime = (unsigned int)(stt.st_mtime);
	buf->ctime = (unsigned int)(stt.st_ctime);
	
	return ret;
}	

/* fstat()の共用関数 */
/* 戻り値 success:0 failure:-1 */
int my_fstat( int filedes, MYSTAT *buf )
{
	int ret;
#ifdef _WIN32
	struct _stat stt;
	
	ret = _fstat( filedes, &stt );
#endif

#ifdef unix
	struct stat stt;
	
	ret = fstat( filedes, &stt); 
#endif

	buf->mode = (unsigned short)(stt.st_mode);
	buf->size = (unsigned int)(stt.st_size);
	buf->atime = (unsigned int)(stt.st_atime);
	buf->mtime = (unsigned int)(stt.st_mtime);
	buf->ctime = (unsigned int)(stt.st_ctime);

	return ret;
}

/* fileの削除 */
int my_rm( char *filename )
{
	/* success:0  fail:-1 */
#ifdef _WIN32
	char tmp[4096];
	utf8tomultibyte(tmp,sizeof(tmp),filename);
	return remove( tmp );
#endif

#ifdef unix
	return remove( filename );
#endif
}

/* fileの名前・位置変更 */
int myrename( char *oldname, char *newname )
{
#ifdef _WIN32
	char tmp_o[4096];
	char tmp_n[4096];
	utf8tomultibyte(tmp_o,sizeof(tmp_o),oldname);
	utf8tomultibyte(tmp_n,sizeof(tmp_n),newname);
	return rename( tmp_o, tmp_n);
#endif

#ifdef unix
	return rename( oldname, newname );
#endif
}



#if 0

main()
{

	MYDIR* md;
	char buf[256];
	char buf2[256];
	int f;
	MYSTAT ms;

	my_stat("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x8a.txt",&ms);
	
	multibytetoutf8(buf,256,"\x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8");
	utf8tomultibyte(buf2,256,buf);

	my_mkdir("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x88");
	my_rmdir("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x88");

	f=my_isdir("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x8a");
	printf("my_isdir=%d\n",f);
	f=my_isdir("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x8a.ttt");
	printf("my_isdir=%d\n",f);
	f=my_isdir("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x8a.txt");
	printf("my_isdir=%d\n",f);

	md=my_open_dir("\xe3\x81\x82\xe3\x81\x84\xe3\x81\x86\xe3\x81\x88\xe3\x81\x8a");
	if(md==NULL)return;
	
 	while(my_read_dir2(md,buf,256,&f))
	{
		printf(">>%04x<<>>%s<< %02x\n",f,buf,buf[0]&255);
	}
	
	my_close_dir(md);



}
#endif

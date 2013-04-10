/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef _DIRTOOL_H_
#define _DIRTOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#endif

#ifdef unix
#include <sys/types.h>
#include <sys/stat.h> 
#include <dirent.h>

#include <unistd.h>
#include <sys/param.h>
#endif

#include <time.h>
#include <stdint.h>

#define MYDIR_FLAG_FIRST 1
#define MYDIR_FLAG_NEXT  0

struct mydir
{
	int flag;
#ifdef _WIN32
	intptr_t h;
	struct _finddata_t fileinfo;
#endif
#ifdef unix
	DIR* dir;
#endif
};

typedef struct mydir MYDIR;
typedef struct mydir* LPMYDIR;

struct mystat
{
	unsigned short	mode;
	unsigned int	size;
	unsigned int	atime;
	unsigned int	mtime;
	unsigned int	ctime;
};
typedef struct mystat MYSTAT;

struct myutimbuf
{
	unsigned int	actime;
	unsigned int	modtime;
};
typedef struct myutimbuf MYUTIMBUF;

/* mystat.modeの定義 */
#ifdef _WIN32	 
#define MYS_IFMT	_S_IFMT		/* ファイル種別を示すビット領域を表すビットマスク */
#define MYS_IFDIR	_S_IFDIR	/* ディレクトリ */
#define MYS_IFCHR	_S_IFCHR	/* キャラクター・デバイス */
#define MYS_IFIFO	_S_IFIFO	/* FIFO */
#define MYS_IFREG	_S_IFREG	/* 通常のファイル */
#define MYS_IRUSR	_S_IREAD	/* 所有者の読み込み許可 */
#define MYS_IWUSR	_S_IWRITE	/* 所有者の書き込み許可 */
#define MYS_IXUSR	_S_IEXEC	/* 所有者の実行許可 */
#endif
#ifdef unix
#define MYS_IFMT	S_IFMT		/* ファイル種別を示すビット領域を表すビットマスク */
#define MYS_IFDIR	S_IFDIR		/* ディレクトリ */
#define MYS_IFCHR	S_IFCHR		/* キャラクター・デバイス */
#define MYS_IFIFO	S_IFIFO		/* FIFO */
#define MYS_IFREG	S_IFREG		/* 通常のファイル */
#define MYS_IRUSR	S_IRUSR		/* 所有者の読み込み許可 */
#define MYS_IWUSR	S_IWUSR		/* 所有者の書き込み許可 */
#define MYS_IXUSR	S_IXUSR		/* 所有者の実行許可 */
#endif

	 
/* mystat.modeのマクロ */
#define	MYS_ISTYPE(mode, mask)	(((mode) & MYS_IFMT) == (mask))
#define	MYS_ISDIR(mode)	 MYS_ISTYPE((mode), MYS_IFDIR)	/* ディレクトリか?    */
#define	MYS_ISCHR(mode)	 MYS_ISTYPE((mode), MYS_IFCHR)	/* キャラクター・デバイスか? */
#define	MYS_ISREG(mode)	 MYS_ISTYPE((mode), MYS_IFREG)	/* 通常のファイルか?  */
#define MYS_ISFIFO(mode)	MYS_ISTYPE((mode), MYS_IFIFO)	/* FIFO (名前付きパイプ) か? */

	 
#ifdef __cplusplus
extern "C"
{
#endif


MYDIR* my_open_dir(char* filen);
void my_close_dir(MYDIR* vp);
int my_read_dir(MYDIR* vp,char* buf,int len);
int my_read_dir2(MYDIR* vp,char* buf,int len,int* flag);
int my_isown_dir(MYDIR *vp,char* buf);
int my_isparent_dir(MYDIR *vp,char*buf);
int my_ischid_dir(MYDIR *vp,char*buf);
int my_mkdir( char *dirname );
int my_rmdir( char *dirname );

int my_isdir( char *path );
int my_chdir( char *dirname );
int my_dirupper( char *dirname );
int my_stat( char *path, MYSTAT *buf );
int my_fstat( int filedes, MYSTAT *buf );

int my_rm( char *filename );
int myrename( char *oldname, char *newname );

#ifdef __cplusplus
}
#endif


#endif /* _DIRTOOL_H_ */

/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef DF_MEMFILE_H_
#define DF_MEMFILE_H_



#ifdef __cplusplus
extern "C"
{
#endif


typedef struct memfile MEMFILE;


MEMFILE* memfile_open(int sz);
void memfile_close(MEMFILE* m);
void memfile_write(MEMFILE* m,void* buf,int sz);
void memfile_seek(MEMFILE* m,int pos);
int memfile_tell(MEMFILE* m);
int memfile_size(MEMFILE* m);
int memfile_read(MEMFILE* m,void* buf,int sz);
void* memfile_data(MEMFILE* m);
MEMFILE* memfile_copy(char* p,int sz);
MEMFILE* memfile_dup(MEMFILE* m);


#ifdef __cplusplus
}
#endif


#endif /* DF_MEMFILE_H_ */



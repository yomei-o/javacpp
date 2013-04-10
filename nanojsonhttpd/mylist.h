/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef DF_MYLIST_H_
#define DF_MYLIST_H_

typedef struct mylist MYLIST;




#ifdef __cplusplus
extern "C"
{
#endif


MYLIST* mylist_open();
void mylist_add(MYLIST* o,char *key);
//int mylist_hasmore(MYLIST* o);
//char* mylist_next(MYLIST* o);
void  mylist_close(MYLIST* o);
MYLIST*  mylist_dup(MYLIST* o);
int  mylist_size(MYLIST* o);
char* mylist_get(MYLIST* o,int n);



#ifdef __cplusplus
}
#endif



#endif /* DF_MYLIST_H_ */



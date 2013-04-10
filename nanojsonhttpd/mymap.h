/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef DF_MYMAP_H_
#define DF_MYMAP_H_




#ifdef __cplusplus
extern "C"
{
#endif


typedef struct mymap MYMAP;

MYMAP* mymap_alloc();
MYMAP* mymap_delTop(MYMAP* m);
void mymap_addTail(MYMAP* m,char* key,char* val);
void mymap_delete(MYMAP* m);
void mymap_put(MYMAP* m,char* key,char* val);
char* mymap_get(MYMAP* m,char* key);
MYMAP* mymap_copy(MYMAP* m);
int mymap_getNums(MYMAP* m);
char* mymap_getIndexOfKey(MYMAP* m,int n);
char* mymap_getIndexOfValue(MYMAP* m,int n);

#ifdef __cplusplus
}
#endif


#endif /* DF_MYMAP_H_ */



/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef DF_MYENUM_H_
#define DF_MYENUM_H_

typedef struct myenum MYENUM;




#ifdef __cplusplus
extern "C"
{
#endif


MYENUM* myenum_open();
void myenum_add(MYENUM* o,char *key);
int myenum_hasmore(MYENUM* o);
char* myenum_next(MYENUM* o);
void  myenum_close(MYENUM* o);
MYENUM*  myenum_dup(MYENUM* o);



#ifdef __cplusplus
}
#endif



#endif /* DF_MYENUM_H_ */



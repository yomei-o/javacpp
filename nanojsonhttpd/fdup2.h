/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/
 
#ifndef _FDUP2_H_
#define _FDUP2_H_

#include <stdio.h>


#ifdef __cplusplus
extern "C"
{
#endif


FILE* fdup(FILE* fp,char*mode);
FILE *fdup2( FILE *oldfp, FILE *newfp );


#ifdef __cplusplus
}
#endif


#endif /* _FDUP2_H_ */



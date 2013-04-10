/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef df_STRTAG_H
#define df_STRTAG_H



#ifdef __cplusplus
extern "C"
{
#endif

char* strtag_find(char*p,char*str);
void strtag_decode(char*p,char*buf);
void strtag_get(char* m,char* name1,char* name2,char* tmp,int sz);

#ifdef __cplusplus
}
#endif


#endif /* df_STRTAG_H */




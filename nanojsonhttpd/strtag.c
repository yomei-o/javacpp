/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strtag.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


char* strtag_find(char*p,char*str){
	p=strstr(p,str);
	if(p==NULL)return NULL;
	p=strstr(p,">");
	if(p==NULL)return NULL;
	p++;
	return p;
}

void strtag_decode(char*p,char*buf){
	while(*p && *p<=' ')p++;
		while(1){
		if(*p==0 || *(p+1)==0)return;
		if( ((*p>='0' && *p<='9')||
			(*p>='A' && *p<='F')||
			(*p>='a' && *p<='f'))&&
			((*(p+1)>='0' && *(p+1)<='9')||
			(*(p+1)>='A' && *(p+1)<='F')||
			(*(p+1)>='a' && *(p+1)<='f')))
		{
			char tmp[4];
			int k;
			tmp[0]=*p;
			tmp[1]=*(p+1);
			tmp[2]=0;
			sscanf(tmp,"%x",&k);
			*buf++=(char)k;
		}
		else break;
		p+=2;
	}
	return;
}

void strtag_get(char* m,char* name1,char* name2,char* tmp,int sz)
{
	char *p=NULL,*q=NULL;
	int len=0;

	tmp[0]=0;
	p=strstr((char*)m,name1);
	if(p==NULL)goto end;
	p++;
	p=strstr(p,">");
	if(p==NULL)goto end;
	p++;
	while(*p && *p<=' ')p++;
	
	q=strstr(p,name2);
	if(q==NULL)goto end;

	len=(int)(q-p);
	if(len<=0 || len+1>sz)goto end;
	memcpy(tmp,p,len);
	tmp[len]=0;
end:
	return;
}




/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#include "networkif.h"
#include "networkifv6_internal.h"


// for Visual Studio 6 , Visual Studio 2002 ,Visual Studio 2003
#ifndef JAVA
#if defined(_MSC_VER) && (_MSC_VER<1700)
static int snprintf(char * buf,size_t n,const char *format,...)
{
	int ret;
	va_list ap;
    va_start(ap, format);
    ret = vsprintf(buf,format, ap);
    va_end(ap);
	return ret;
}
#endif
#endif


int networkifv6_internal_enum(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
{
	networkifv6_internal_enum_windows(p,f);
	networkifv6_internal_enum_linux(p,f);
	//networkifv6_internal_enum_default(p,f);
	return 1;
}


int networkifv6_internal_enum_default(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
{
	{
		MYIPADDRESSINFO ip={
			MYIPADDRESS_TYPE_IPV4,
			{MYIPADDRESS_TYPE_IPV4,{127,0,0,1},4},
			{MYIPADDRESS_TYPE_IPV4,{255,0,0,0},4},
			{MYIPADDRESS_TYPE_ETHERNET,{1,2,3,4,5,6},6}
		};
		if(p==NULL || f==NULL)return 0;
		(*f)(p,&ip);
	}
	return 1;
}


static char* get_type_string(int n){
	switch(n){
	case 1:
		return (char*)"IPV4";
	case 2:
		return (char*)"IPV6";
	case 3:
		return (char*)"ETHERNET";
	}
	return (char*)"Unknown";
}

int networkifv6_internal_print(MYNETWORKIF * p,MYIPADDRESSINFO* pipaddress)
{
	int i;
	if(p==NULL || pipaddress==NULL)return 0;

	printf("IPADDRESSINFO\n");
	printf("    type=%s\n",get_type_string(pipaddress->type));

	printf("    ipAddress.type=%s\n",get_type_string(pipaddress->ipAddress.type));
	printf("    ipAddress.len=%d\n",pipaddress->ipAddress.len);
	printf("    ipAddress=");
	for(i=0;i<pipaddress->ipAddress.len;i++){
		int c=(pipaddress->ipAddress.type==1)?'.':':';

		if(i+1==pipaddress->ipAddress.len)c=' ';
		printf((pipaddress->ipAddress.type==1)?"%d%c":"%02x%c",pipaddress->ipAddress.address[i]&255,c);
	}
	printf("\n");

	printf("    netMask.type=%s\n",get_type_string(pipaddress->netMask.type));
	printf("    netMask.len=%d\n",pipaddress->netMask.len);
	printf("    netMask=");
	for(i=0;i<pipaddress->netMask.len;i++){
		int c='.';
		if(i+1==pipaddress->netMask.len)c=' ';
		printf("%d%c",pipaddress->netMask.address[i],c);
	}
	printf("\n");
	
	printf("    phyAddress.type=%s\n",get_type_string(pipaddress->phyAddress.type));
	printf("    phyAddress.len=%d\n",pipaddress->phyAddress.len);
	printf("    phyAddress=");
	for(i=0;i<pipaddress->phyAddress.len;i++){
		int c=':';
		if(i+1==pipaddress->phyAddress.len)c=' ';
		printf("%02x%c",pipaddress->phyAddress.address[i],c);
	}
	printf("\n");

	printf("\n");
	return 1;
}


#if 0

int main(){

	MYNETWORKIF* p=(MYNETWORKIF*)0x10000;		
	networkifv6_internal_enum(p,networkifv6_internal_print);

}


#endif




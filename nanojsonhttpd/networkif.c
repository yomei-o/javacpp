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

#if defined(_WIN32) && !defined(__GNUC__)
#pragma comment( lib, "iphlpapi.lib" )
#pragma comment( lib, "wsock32.lib" )
#endif

#include "networkifv6_internal.h"
#include "networkif.h"

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif

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


MYNETWORKIF* networkif_alloc()
{
	MYNETWORKIF* ret;
	ret=(MYNETWORKIF*)malloc(sizeof(MYNETWORKIF));
	memset(ret,0,sizeof(MYNETWORKIF));
	return ret;
}

int networkif_free(MYNETWORKIF*p)
{
	int  i;

	if(p==NULL)return 0;
	if(p->address){
		for(i=0;i<p->num;i++){
			free(p->address[i]);
		}
		free(p->address);
	}
	free(p);
	return 1;
}
int networkif_add(MYNETWORKIF * p,MYIPADDRESSINFO* pipaddress)
{
	if(p==NULL || pipaddress==NULL)return 0;
	p->address=(MYIPADDRESSINFO**)realloc(p->address,(p->num+1)*sizeof(void*));
	p->address[p->num]=(MYIPADDRESSINFO*)malloc(sizeof(MYIPADDRESSINFO));
	*(p->address[p->num])=*pipaddress;
	p->num++;
	return 1;
}

int networkif_num(MYNETWORKIF* p)
{
	if(p==NULL)return -1;
	return p->num;
}
int networkif_get(MYNETWORKIF*p,int i,MYIPADDRESSINFO* pipaddress)
{
	if(p==NULL || pipaddress==NULL)return 0;
	if(i<0 || p->num<=i)return 0;
	*pipaddress=*(p->address[i]);
	return 1;
}

MYNETWORKIF* networkif_enumall(){
	MYNETWORKIF* ret;
	ret=networkif_alloc();
	networkifv6_internal_enum(ret,networkif_add);
	return ret;
}


static char* get_type_string(int n){
	switch(n){
	case 1:
		return "IPV4";
	case 2:
		return "IPV6";
	case 3:
		return "ETHERNET";
	}
	return "Unknown";
}

int networkif_print(MYIPADDRESSINFO* pipaddress)
{
	int i;
	if(pipaddress==NULL)return 0;

	printf("IPADDRESSINFO\n");
	printf("    type=%s\n",get_type_string(pipaddress->type));

	printf("    ipAddress.type=%s\n",get_type_string(pipaddress->ipAddress.type));
	printf("    ipAddress.len=%d\n",pipaddress->ipAddress.len);
	printf("    ipAddress=");
	for(i=0;i<pipaddress->ipAddress.len;i++){
		int c='.';
		if(i+1==pipaddress->ipAddress.len)c=' ';
		printf("%d%c",pipaddress->ipAddress.address[i],c);
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

int networkif_toString(MYIPADDRESSINFO* pipaddress,char* str,int sz)
{
	int i;
	char tmp[128];
	if(pipaddress==NULL || str==NULL)return 0;

	str[0]=0;

	strncat(str,"<ipaddressinfo>\n",100);
	snprintf(tmp,128,"<type>%d</type>\n",pipaddress->type);
	strncat(str,tmp,100);

	strncat(str,"<ipAddress>\n",100);
    snprintf(tmp,128,"<type>%d</type>\n",pipaddress->ipAddress.type);
	strncat(str,tmp,100);
	snprintf(tmp,128,"<len>%d</len>\n",pipaddress->ipAddress.len);
	strncat(str,tmp,100);
	strncat(str,"<address>",100);
	for(i=0;i<pipaddress->ipAddress.len;i++){
		snprintf(tmp,128,"%02x",pipaddress->ipAddress.address[i]);
		strncat(str,tmp,100);
	}
	strncat(str,"</address>\n",100);
	strncat(str,"</ipAddress>\n",100);

	strncat(str,"<netMask>\n",100);
    snprintf(tmp,128,"<type>%d</type>\n",pipaddress->netMask.type);
	strncat(str,tmp,100);
	snprintf(tmp,128,"<len>%d</len>\n",pipaddress->netMask.len);
	strncat(str,tmp,100);
	strncat(str,"<address>",100);
	for(i=0;i<pipaddress->netMask.len;i++){
		snprintf(tmp,128,"%02x",pipaddress->netMask.address[i]);
		strncat(str,tmp,100);
	}
	strncat(str,"</address>\n",100);
	strncat(str,"</netMask>\n",100);

	strncat(str,"<phyAddress>\n",100);
    snprintf(tmp,128,"<type>%d</type>\n",pipaddress->phyAddress.type);
	strncat(str,tmp,100);
	snprintf(tmp,128,"<len>%d</len>\n",pipaddress->phyAddress.len);
	strncat(str,tmp,100);
	strncat(str,"<address>",100);
	for(i=0;i<pipaddress->phyAddress.len;i++){
		snprintf(tmp,128,"%02x",pipaddress->phyAddress.address[i]);
		strncat(str,tmp,100);
	}
	strncat(str,"</address>\n",100);
	strncat(str,"</phyAddress>\n",100);

	strncat(str,"</ipaddressinfo>\n",100);
	return 1;
}

static char* find(char*p,char*str){
	p=strstr(p,str);
	if(p==NULL)return NULL;
	p=strstr(p,">");
	if(p==NULL)return NULL;
	p++;
	return p;
}
static void decode(char*p,char*buf){
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

int networkif_fromString(MYIPADDRESSINFO* pipaddress,char* str,int sz)
{
	//int i;
	//char tmp[128];
	char*p,*q,*s;

	if(pipaddress==NULL || str==NULL)return 0;

	memset(pipaddress,0,sizeof(MYIPADDRESSINFO));

	q=find(str,"<ipaddressinfo");
	if(q==NULL)return 0;

	p=find(q,"<type");
	if(p)sscanf(p,"%d",&(pipaddress->type));

	s=strstr(q,"<netMask");
	if(s){
		p=find(s,"<type");
		if(p)sscanf(p,"%d",&(pipaddress->netMask.type));
		p=find(s,"<len");
		if(p)sscanf(p,"%d",&(pipaddress->netMask.len));
		p=find(s,"<address");
		if(p)decode(p,(char*)(pipaddress->netMask.address));
	}
	s=strstr(q,"<ipAddress");
	if(s){
		p=find(s,"<type");
		if(p)sscanf(p,"%d",&(pipaddress->ipAddress.type));
		p=find(s,"<len");
		if(p)sscanf(p,"%d",&(pipaddress->ipAddress.len));
		p=find(s,"<address");
		if(p)decode(p,(char*)(pipaddress->ipAddress.address));
	}
	s=strstr(q,"<phyAddress");
	if(s){
		p=find(s,"<type");
		if(p)sscanf(p,"%d",&(pipaddress->phyAddress.type));
		p=find(s,"<len");
		if(p)sscanf(p,"%d",&(pipaddress->phyAddress.len));
		p=find(s,"<address");
		if(p)decode(p,(char*)(pipaddress->phyAddress.address));
	}
	return 1;
}


#if 0
main(){

	MYNETWORKIF* a;
	MYIPADDRESSINFO ip;
	int i;
	char buf[1024];
#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif


	//a=networkif_alloc();
	//networkif_free(a);
	//a=networkif_alloc();
	//memset(&ip,0x11,sizeof(MYIPADDRESS));
	//networkif_add(a,&ip);
	//memset(&ip,0x22,sizeof(MYIPADDRESS));
	//networkif_add(a,&ip);
	//memset(&ip,0x33,sizeof(MYIPADDRESS));
	//networkif_add(a,&ip);

	//memset(&ip,0,sizeof(MYIPADDRESS));
	//printf("num=%d\n",networkif_num(a));
	//networkif_get(a,3,&ip);
	//networkif_free(a);

	a=networkif_enumall();
	printf("num=%d\n",networkif_num(a));
	for(i=0;i<networkif_num(a);i++){
		memset(&ip,0,sizeof(MYIPADDRESS));
		networkif_get(a,i,&ip);
		networkif_print(&ip);
		networkif_toString(&ip,buf,1024);
		printf("string=>>\n%s<<\n",buf);

		memset(&ip,0,sizeof(MYIPADDRESS));
		networkif_fromString(&ip,buf,1024);
		networkif_print(&ip);

	}
	networkif_free(a);
}

#endif

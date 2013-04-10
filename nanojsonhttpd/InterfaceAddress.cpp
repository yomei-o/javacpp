/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String_.h"
#include "InterfaceAddress.h"
#include "InetAddress.h"
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

#define print(a) printf("%s\n",a)

#define null 0
#define byte char
#define true 1
#define false 0


InterfaceAddress::InterfaceAddress()
{
	m_null=false;
	m=NULL;
}

InterfaceAddress::InterfaceAddress(int id)
{
	if(id==0)m_null=true;
	m=NULL;
}

InterfaceAddress::~InterfaceAddress()
{
	if(m)free(m);
	m=NULL;
}

InterfaceAddress& InterfaceAddress::operator =(char* f)
{
	if(m)free(m);
	m=NULL;

	if(f==NULL){
		m_null=true;
		goto end;
	}
	m_null=false;
	if(f){
		int len=0;
		len=(int)strlen(f)+1;
		m=(char*)malloc(len);
		strncpy(m,f,len);
	}
end:
	return *this;
}

InterfaceAddress::InterfaceAddress(const InterfaceAddress &f)
{
	int len=0;
	m_null=f.m_null;
	m=null;
	if(f.m){
		len=(int)strlen(f.m)+1;
		m=(char*)malloc(len);
		strncpy(m,f.m,len);
	}
}

InterfaceAddress& InterfaceAddress::operator =(InterfaceAddress *f)
{
	if(m)free(m);
	m=NULL;

	if(f==NULL)goto end;
	m_null=f->m_null;
	if(f->m){
		int len=0;
		len=(int)strlen(f->m)+1;
		m=(char*)malloc(len);
		strncpy(m,f->m,len);
	}

	delete f;
end:
	return *this;
}
#if 0
InterfaceAddress& InterfaceAddress::operator =(InterfaceAddress& f)
{
	//printf("oprerator=(NetworkUnterface& f) this=%p f=%p\n",this,&f);

	if(m)free(m);
	m=NULL;

	m_null=f.m_null;
	if(f.m){
		int len=0;
		len=strlen(f.m)+1;
		m=(char*)malloc(len);
		strncpy(m,f.m,len);
	}
//end:
	return *this;
}
#endif
InterfaceAddress& InterfaceAddress::operator =(InterfaceAddress f)
{
	//printf("oprerator=(NetworkUnterface& f) this=%p f=%p\n",this,&f);

	if(m)free(m);
	m=NULL;

	m_null=f.m_null;
	if(f.m){
		int len=0;
		len=(int)strlen(f.m)+1;
		m=(char*)malloc(len);
		strncpy(m,f.m,len);
	}
//end:
	return *this;
}


bool InterfaceAddress::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}

bool InterfaceAddress::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}


InetAddress InterfaceAddress::getAddress()
{
	char tmp[128];
	InetAddress ret=null;

	if(m==NULL)goto end;
	
	strtag_get((char*)m,"<ipAddress","</ipAddress",tmp,sizeof(tmp));
	if(tmp[0]==0)goto end;
	ret=(char*)tmp;
end:
	return ret;
}


int InterfaceAddress::getNetworkPrefixLength()
{
	int ret=0;
	int len=0;
	int type=0;
	char tmp[128];
	char address[16];
	char*p;
	int i,j;

	if(m==NULL)goto end;
	
	strtag_get((char*)m,"<netMask","</netMask",tmp,sizeof(tmp));

	if(tmp[0]==0)goto end;
	p=strtag_find(tmp,"<type");
	if(p)sscanf(p,"%d",&type);
	if(type!=1 && type!=2)goto end;

	p=strtag_find(tmp,"<len");
	if(p)sscanf(p,"%d",&len);
	if(len<1 || len>16)goto end;

	memset(address,0,16);
	p=strtag_find(tmp,"<address");
	if(p)strtag_decode(p,address);

	for(i=0;i<len;i++){
		int k=address[i]&255;
		for(j=0;j<8;j++){
			if((k&1)==1)ret++;
			k>>=1;
		}
	}
end:
	return ret;
}


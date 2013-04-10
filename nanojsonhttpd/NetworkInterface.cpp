/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"
#include "NetworkInterface.h"
#include "Enumeration.h"
#include "List.h"
#include "networkif.h"
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

NetworkInterface::NetworkInterface()
{
	m_null=false;
	m=NULL;
	//printf("NetworkInterface() %p\n",this);
}

NetworkInterface::NetworkInterface(int id)
{
	if(id==0)m_null=true;
	m=NULL;
	//printf("NetworkInterface(int) %p\n",this);
}

NetworkInterface::~NetworkInterface()
{
	//printf("~NetworkInterface() %p\n",this);
	if(m)free(m);
	m=NULL;
}

NetworkInterface::NetworkInterface(const NetworkInterface &f)
{
	//printf("NetworkInterface(const NetworkUnterface) %p\n",this);
	int len=0;
	m_null=f.m_null;
	len=(int)strlen(f.m)+1;
	m=(char*)malloc(len);
	strncpy(m,f.m,len);

}

NetworkInterface& NetworkInterface::operator =(NetworkInterface *f)
{
	//printf("oprerator=(NetworkUnterface* f) this=%p f=%p\n",this,f);

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

NetworkInterface& NetworkInterface::operator =(NetworkInterface f)
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
#if 0
NetworkInterface& NetworkInterface::operator =(NetworkInterface& f)
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

NetworkInterface& NetworkInterface::operator =(char *f)
{
	//printf("oprerator=(char* f) this=%p f=%p\n",this,f);

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

bool NetworkInterface::operator ==(int a)
{
	if(m_null==true && a==0)return true;
	return false;
}

bool NetworkInterface::operator !=(int a)
{
	if(m_null==true && a==0)return false;
	return true;
}


List NetworkInterface::getInterfaceAddresses()
{
	List ret=null;
	if(m==NULL){
		return ret;
	}

	ret=new List();
	ret.add((char*)m);
	return ret;
}

Enumeration NetworkInterface::getInetAddresses()
{
	char buf[256];
	Enumeration ret=null;
	if(m==NULL){
		return ret;
	}
	buf[0]=0;
	strtag_get((char*)m,"<ipAddress","</ipAddress",buf,sizeof(buf));
	if(buf[0]==0)goto end;

	ret=new Enumeration();
	ret.add((char*)buf);
end:
	return ret;
}

Enumeration NetworkInterface::getNetworkInterfaces()
{
	MYNETWORKIF* p;
	MYIPADDRESSINFO ip;
	char buf[1024];
	int i;
	Enumeration ret=null;

	p=networkif_enumall();
	if(p==null)return ret;
	if(networkif_num(p)==0){
		networkif_free(p);
		return ret;
	}
	ret=new Enumeration();
	for(i=0;i<networkif_num(p);i++){
		memset(&ip,0,sizeof(MYIPADDRESSINFO));
		networkif_get(p,i,&ip);
		buf[0]=0;
		networkif_toString(&ip,buf,sizeof(buf));
		ret.add(buf);
	}
	networkif_free(p);
	return ret;
}



char* NetworkInterface::getHardwareAddress()
{
	char* ret=null;
	char*p;
	char buf[256];
	int type=0;
	int len=0;

	if(m==null)goto end;

	strtag_get((char*)m,"<phyAddress","</phyAddress",buf,sizeof(buf));
	if(buf[0]==0)goto end;

	p=strtag_find((char*)buf,"<type");
	if(p)sscanf(p,"%d",&type);

	p=strtag_find((char*)buf,"<len");
	if(p)sscanf(p,"%d",&len);

	p=strtag_find((char*)buf,"<address");
	if(p==NULL)goto end;

	if(type!=3 || len!=6)goto end;

	ret=new char[16];
	memset(ret,0,16);
	strtag_decode(p,ret);
end:
	return ret;
}


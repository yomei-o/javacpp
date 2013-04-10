/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (defined linux)&&!(defined __CYGWIN__)
#include <sys/ioctl.h>	/*ioctl()*/
#include <net/if.h>		/* struct ifreq */
#include <netinet/in.h> /* struct in_addr */
#include <errno.h>
#endif

/* Win32 specified header */
#if defined(_WIN32) || defined(__CYGWIN__) 
#include <windows.h>
#include <Iphlpapi.h>
#endif

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#if defined(_WIN32) && !defined(__GNUC__)
#pragma comment( lib, "iphlpapi.lib" )
#pragma comment( lib, "wsock32.lib" )
#endif

#ifdef unix
#include <unistd.h>
#endif

#ifdef __CYGWIN__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "networkif.h"
#include "networkif_internal.h"



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


int networkif_internal_enum(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
{
	networkif_internal_enum_windows(p,f);
	networkif_internal_enum_linux(p,f);
	networkif_internal_enum_default(p,f);
	return 1;
}

int networkif_internal_enum_windows(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
{
#ifdef _WIN32
	int lngLen,lngRes,szAI;
	IP_ADAPTER_INFO* AdapterMem;
	unsigned int k;

	if(p==NULL || f==NULL)return 0;

	/* get num of adaperts */
	lngLen=0;
	lngRes=GetAdaptersInfo(NULL,(DWORD*)(&lngLen));
	szAI=sizeof(IP_ADAPTER_INFO);

	AdapterMem=(IP_ADAPTER_INFO*)malloc(lngLen);
	if(AdapterMem){
		IP_ADAPTER_INFO* ppp=AdapterMem;

		lngRes=GetAdaptersInfo(AdapterMem,(DWORD*)(&lngLen));
		while(ppp){
			if(ppp->Type==MIB_IF_TYPE_ETHERNET){
				MYIPADDRESSINFO ip;
				memset(&ip,0,sizeof(MYIPADDRESSINFO));
				ip.type=MYIPADDRESS_TYPE_IPV4;

				memcpy(ip.phyAddress.address,ppp->Address,6);
				ip.phyAddress.type=MYIPADDRESS_TYPE_ETHERNET;
				ip.phyAddress.len=6;

				k=inet_addr((char*)(ppp->IpAddressList.IpAddress.String));
				memcpy(ip.ipAddress.address,&k,4);
				ip.ipAddress.type=MYIPADDRESS_TYPE_IPV4;
				ip.ipAddress.len=4;

				k=inet_addr((char*)(ppp->IpAddressList.IpMask.String));
				memcpy(ip.netMask.address,&k,4);
				ip.netMask.type=MYIPADDRESS_TYPE_IPV4;
				ip.netMask.len=4;

				(*f)(p,&ip);
				ppp=ppp->Next;
			}
		}
	}
	free(AdapterMem);
	return 1;
#endif /* _WIN32 */
	return 0;
}


int networkif_internal_enum_linux(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
{
#ifdef linux
	int i,ret;
	int fd;
	struct ifreq ifr;
	unsigned char* pp;

	//enumlate wired LAN
	for(i=0;i<10;i++){
		MYIPADDRESSINFO ip;
		memset(&ip,0,sizeof(MYIPADDRESSINFO));
		ip.type=MYIPADDRESS_TYPE_IPV4;


		fd = socket(AF_INET, SOCK_DGRAM, 0);

		//device check
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "eth%d",i);
		ret=ioctl(fd, SIOCGIFFLAGS, &ifr);
		if(ret== -1)goto end;

		// get IP Address
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "eth%d",i);
		ioctl(fd, SIOCGIFADDR, &ifr);
		//printf("ipAddress=%s\n", (char*)inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		pp=(unsigned char*)&(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
		memcpy(ip.ipAddress.address,pp,4);
		ip.ipAddress.type=MYIPADDRESS_TYPE_IPV4;
		ip.ipAddress.len=4;
	

		// get NetMask
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "eth%d",i);
		ioctl(fd, SIOCGIFNETMASK, &ifr);
		//printf("netMask=%s\n", (char*)inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		pp=(unsigned char*)&(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
		memcpy(ip.netMask.address,pp,4);
		ip.netMask.type=MYIPADDRESS_TYPE_IPV4;
		ip.netMask.len=4;

		// get MAC
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "eth%d",i);
		ioctl(fd, SIOCGIFHWADDR, &ifr);

		pp = (unsigned char *)&ifr.ifr_hwaddr.sa_data;
		 //printf("mac=%02x:%02x:%02x:%02x:%02x:%02x\n", *pp, *(pp+1), *(pp+2), *(pp+3), *(pp+4), *(pp+5));
		memcpy(ip.phyAddress.address,pp,6);
		ip.phyAddress.type=MYIPADDRESS_TYPE_ETHERNET;
		ip.phyAddress.len=6;

		//invoke
		(*f)(p,&ip);

		//end
end:
		close(fd);
	}

	//enumlate wireless LAN
	for(i=0;i<10;i++){
		MYIPADDRESSINFO ip;
		memset(&ip,0,sizeof(MYIPADDRESSINFO));
		ip.type=MYIPADDRESS_TYPE_IPV4;


		fd = socket(AF_INET, SOCK_DGRAM, 0);

		//device check
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "ath%d",i);
		ret=ioctl(fd, SIOCGIFFLAGS, &ifr);
		if(ret== -1)goto end2;

		// get IP Address
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "ath%d",i);
		ioctl(fd, SIOCGIFADDR, &ifr);
		//printf("ipAddress=%s\n", (char*)inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		pp=(unsigned char*)&(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
		memcpy(ip.ipAddress.address,pp,4);
		ip.ipAddress.type=MYIPADDRESS_TYPE_IPV4;
		ip.ipAddress.len=4;
	

		// get NetMask
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "ath%d",i);
		ioctl(fd, SIOCGIFNETMASK, &ifr);
		//printf("netMask=%s\n", (char*)inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		pp=(unsigned char*)&(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
		memcpy(ip.netMask.address,pp,4);
		ip.netMask.type=MYIPADDRESS_TYPE_IPV4;
		ip.netMask.len=4;

		// get MAC
		memset(&ifr,0,sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name,16, "ath%d",i);
		ioctl(fd, SIOCGIFHWADDR, &ifr);

		pp = (unsigned char *)&ifr.ifr_hwaddr.sa_data;
		 //printf("mac=%02x:%02x:%02x:%02x:%02x:%02x\n", *pp, *(pp+1), *(pp+2), *(pp+3), *(pp+4), *(pp+5));
		memcpy(ip.phyAddress.address,pp,6);
		ip.phyAddress.type=MYIPADDRESS_TYPE_ETHERNET;
		ip.phyAddress.len=6;

		//invoke
		(*f)(p,&ip);

		//end
end2:
		close(fd);
	}

	return 1;
#endif
	return 0;
}

int networkif_internal_enum_default(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
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

int networkif_internal_print(MYNETWORKIF * p,MYIPADDRESSINFO* pipaddress)
{
	int i;
	if(p==NULL || pipaddress==NULL)return 0;

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


#if 0

int main(){

	MYNETWORKIF* p=(MYNETWORKIF*)0x10000;		
	networkif_internal_enum(p,networkif_internal_print);
}


#endif

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
#include <ifaddrs.h>
#include <sys/socket.h>
#endif

#if defined(unix) && !defined(__CYGWIN__)
#include <unistd.h>
#endif



#include "networkif.h"
#include "networkifv6_internal.h"

#define IPV4_DEFAULT_PREFIX 8
#define IPV6_DEFAULT_PREFIX 48


int networkifv6_internal_enum_linux(MYNETWORKIF* p,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*))
{
#ifdef linux
	int i,n,ret;
	int fd;

	struct ifreq ifr;
	unsigned char* pp;
	MYIPADDRESSINFO ip;

	struct ifaddrs *ifa_list;
	struct ifaddrs *ifa;

	n = getifaddrs(&ifa_list);

	if (n != 0)return 0;

	for(ifa = ifa_list; ifa != NULL; ifa=ifa->ifa_next) {
		//printf("%s\n", ifa->ifa_name);
		//memset(addrstr, 0, sizeof(addrstr));
		//memset(netmaskstr, 0, sizeof(netmaskstr));
		memset(&ip,0,sizeof(ip));

		if (ifa->ifa_addr->sa_family == AF_INET) {

			ip.type=MYIPADDRESS_TYPE_IPV4;
			fd = socket(AF_INET, SOCK_DGRAM, 0);

			pp=(unsigned char*)(&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr);
			memcpy(ip.ipAddress.address,pp,4);
			ip.ipAddress.type=MYIPADDRESS_TYPE_IPV4;
			ip.ipAddress.len=4;

			pp=(unsigned char*)(&((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr);
			memcpy(ip.netMask.address,pp,4);
			ip.netMask.type=MYIPADDRESS_TYPE_IPV4;
			ip.netMask.len=4;

			// get MAC
			memset(&ifr,0,sizeof(struct ifreq));
			ifr.ifr_addr.sa_family = AF_INET;
			snprintf(ifr.ifr_name,16, "%s",ifa->ifa_name);
			ioctl(fd, SIOCGIFHWADDR, &ifr);

			pp = (unsigned char *)&ifr.ifr_hwaddr.sa_data;
			memcpy(ip.phyAddress.address,pp,6);
			ip.phyAddress.type=MYIPADDRESS_TYPE_ETHERNET;
			ip.phyAddress.len=6;

			close(fd);
			//invoke
			(*f)(p,&ip);
		}
		if (ifa->ifa_addr->sa_family == AF_INET6) {

			ip.type=MYIPADDRESS_TYPE_IPV6;
			fd = socket(AF_INET6, SOCK_DGRAM, 0);

			pp=(unsigned char*)(&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr);
			memcpy(ip.ipAddress.address,pp,16);
			ip.ipAddress.type=MYIPADDRESS_TYPE_IPV6;
			ip.ipAddress.len=16;

			pp=(unsigned char*)(&((struct sockaddr_in6 *)ifa->ifa_netmask)->sin6_addr);
			memcpy(ip.netMask.address,pp,16);
			ip.netMask.type=MYIPADDRESS_TYPE_IPV6;
			ip.netMask.len=16;

			// get MAC
			memset(&ifr,0,sizeof(struct ifreq));
			ifr.ifr_addr.sa_family = AF_INET6;
			snprintf(ifr.ifr_name,16, "%s",ifa->ifa_name);
			ioctl(fd, SIOCGIFHWADDR, &ifr);

			pp = (unsigned char *)&ifr.ifr_hwaddr.sa_data;
			memcpy(ip.phyAddress.address,pp,6);
			ip.phyAddress.type=MYIPADDRESS_TYPE_ETHERNET;
			ip.phyAddress.len=6;

			close(fd);
			//invoke
			(*f)(p,&ip);

			//inet_ntop(AF_INET6,&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr,addrstr, sizeof(addrstr));
			//inet_ntop(AF_INET6,&((struct sockaddr_in6 *)ifa->ifa_netmask)->sin6_addr,netmaskstr, sizeof(netmaskstr));
			//printf("  IPv6: %s netmask %s\n", addrstr, netmaskstr);
    	}
	}
	freeifaddrs(ifa_list);
	//invoke

#if 0
	//enumlate wired LAN
	memset(&ip,0,sizeof(MYIPADDRESSINFO));
	ip.type=MYIPADDRESS_TYPE_IPV4;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

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
	close(fd);
#endif
	
	return 1;
#endif
	return 0;
}



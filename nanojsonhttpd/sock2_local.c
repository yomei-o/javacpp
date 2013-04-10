/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/
 
#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#include "sock2_local.h"

#ifdef unix
#include <sys/ioctl.h>
#ifndef __CYGWIN__
#include <net/if_arp.h>
#include <linux/sockios.h>	/* SIOCDEVPRIVATE */
#endif /* __CYGWIN__ */
#include <signal.h>
#endif



#ifdef unix
#define NIFNAME		"eth0"	/* NetworkInterFaceNAME */
#define NIFNAMESIZE 4
#define PROCNETROUTE_PATH		"/proc/net/route"
#define PROCNETROUTE_LINE_SIZE	1024 /* /proc/net/route file の 1 line の長さ分 */
#define PROCNETROUTE_SEP		" \t"
#define PROCNETDEV_PATH			"/proc/net/dev"
#define PROCNETDEV_LINE_SIZE	512 /* /proc/net/dev file の 1 line の長さ分 */
#define PROCNETDEV_SEP			" :" /* token 切り出しのセパレータ */
#define RESOLVCONF_PATH			"/etc/resolv.conf"
#define OLD_SIOCGMIIPHY			0x8947
#define OLD_SIOCGMIIREG			0x8948
#define NEW_SIOCGMIIPHY			SIOCDEVPRIVATE
#define NEW_SIOCGMIIREG			(SIOCDEVPRIVATE+1)
#endif
#define SL_SIZE_OF_MAC 6



//#define I_USE_WINDOWS_SDK

/*
**
** ここでDEBUGでprintfを使うかどうかセットしてください。
**
*/
//#define YO_USER_DEBUG

#ifdef YO_USER_DEBUG
  #define  DPRINT printf
#else
  #define  DPRINT(a) do; while(0)
#endif


#if defined(_WIN32) && !defined(__GNUC__)

#pragma comment( lib, "ws2_32.lib" )

#ifdef I_USE_WINDOWS_SDK
#pragma comment( lib, "iphlpapi.lib" )
#endif

#endif

/*
**
** Winsockの初期化(Windowsの場合のみ)
**
*/
void winsock_init(void)
{
#ifdef _WIN32

  WSADATA wsaData;
  int err;

  err = WSAStartup(MAKEWORD(2,0), &wsaData );
  if ( err != 0 )
  {
    DPRINT("WSAStartup Error\n");
    exit(1);
  }
#endif
#ifdef unix
	signal(SIGPIPE, SIG_IGN);
#endif
}

/*
**
** Winsockの終了(Windowsの場合のみ)
**
*/
void winsock_done(void)
{
#ifdef _WIN32
    WSACleanup( );
#endif
}



/*
**
** ソケットを非同期転送モードに設定します
**
*/

void winsock_asyncmode(SOCKET s)
{
  int arg;
  arg=1;
#ifdef _WIN32
  ioctlsocket(s,FIONBIO,(void*)(&arg));
#endif
#if (defined _SH2)||(defined _SH4)
  tfIoctl(s,FIONBIO,&arg);
#endif
#ifdef unix
  ioctl(s,FIONBIO,&arg);
#endif
}

/*
**
** ソケットを同期転送モードに設定します
**
*/

void winsock_syncmode(SOCKET s)
{
  int arg;
  arg=0;
#ifdef _WIN32
  ioctlsocket(s,FIONBIO,(void*)(&arg));
#endif
#if (defined _SH2)||(defined _SH4)
  tfIoctl(s,FIONBIO,&arg);
#endif
#ifdef unix
  ioctl(s,FIONBIO,&arg);
#endif
}


/*
**
** ソケットバッファにはいっているデータの長さを取得します
**
*/


int winsock_getwaitingbytes(SOCKET s)
{
  int arg;
  arg=1;
#ifdef _WIN32
  ioctlsocket(s,FIONREAD,(void*)(&arg));
#endif
#if (defined _SH2)||(defined _SH4)
  tfIoctl(s,FIONREAD,&arg);
#endif
#ifdef unix
  ioctl(s,FIONREAD,&arg);
#endif
  return arg;
}





int winsock_getipnettable(LPSTMACADDRESS mac_address,unsigned int ip_address){
#ifdef _WIN32
#ifdef I_USE_WINDOWS_SDK
  MIB_IPNETTABLE* m;

  static char buf[65536];

  int len;
  int i;

  len=sizeof(buf);
  m=(MIB_IPNETTABLE*)buf;
  memset(buf,0,sizeof(buf));

  GetIpNetTable(m,&len,0);

  for(i=0;i<(int)m->dwNumEntries;i++)
  {
    if(m->table[i].dwAddr==ip_address)
    {

      unsigned int w;


      w=(unsigned char)(m->table[i].bPhysAddr[0]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[1]);
      mac_address->hi=w;

      w=(unsigned char)(m->table[i].bPhysAddr[2]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[3]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[4]);
      w<<=8;
      w|=(unsigned char)(m->table[i].bPhysAddr[5]);

      mac_address->lo=w;

      return 1;
    }
  }
  return 0;
#else
  return 0;
#endif
#endif
#if (defined _SH2)||(defined _SH4)
  char buf[6];
  int ret;
  unsigned int w;

  ret=tfGetArpEntryByIpAddr(ip_address,buf,sizeof(buf));
  if(ret)return 0;

  w=(unsigned char)buf[0];
  w<<=8;
  w|=(unsigned char)buf[1];
  mac_address->hi=w;

  w=(unsigned char)buf[2];
  w<<=8;
  w|=(unsigned char)buf[3];
  w<<=8;
  w|=(unsigned char)buf[4];
  w<<=8;
  w|=(unsigned char)buf[5];

  mac_address->lo=w;

  return 1;
#endif
#if (defined linux)&&!(defined __CYGWIN__)
  int sock;
  struct arpreq req;
  struct sockaddr_in * sin;
  unsigned int w, i;
  unsigned char * ptr;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if( sock < 0 ){
	  close( sock );
	  return 0;
  }

  memset(&req, 0, sizeof(struct arpreq));
  strncpy(req.arp_dev, NIFNAME, NIFNAMESIZE+1); //device name

  sin = (struct sockaddr_in *)&req.arp_pa;
  memset(sin, 0, sizeof(struct sockaddr_in));

  sin->sin_family = AF_INET; //Address Familiy
  memcpy( &sin->sin_addr, &ip_address, sizeof(struct in_addr)); //IP

  if( ioctl(sock, SIOCGARP, &req) < 0 ){
	  close(sock);
	  return 0;
  }
  close( sock );

  ptr = (unsigned char*)(&req.arp_ha.sa_data[0]);

  /*MACが 0 ではないことを確認*/
  for( i=0; i<SL_SIZE_OF_MAC; i++){
	  if( *(ptr+i) ){ break; }
  }
  if( SL_SIZE_OF_MAC==i ){ return 0; }

  memset( &w, 0, sizeof(unsigned int));
  w=(unsigned char)*ptr;
  w<<=8;
  w|=(unsigned char)*(ptr+1);
  mac_address->hi=w;

  memset( &w, 0, sizeof(unsigned int));
  w=(unsigned char)*(ptr+2);
  w<<=8;
  w|=(unsigned char)*(ptr+3);
  w<<=8;
  w|=(unsigned char)*(ptr+4);
  w<<=8;
  w|=(unsigned char)*(ptr+5);

  mac_address->lo=w;

  return 1;
#endif

  return 0;
}


/*注意事項
//unix の実装はスレッドセーフではない(タイミングによって値が書き換えられてします)
//かもしれないので注意
*/
#if 0
int winsock_getlasterror(SOCKET s)
{
#ifdef _WIN32
  int tmp;
#endif
  
  int ret=-1;
#ifdef _WIN32
  tmp=WSAGetLastError();
  if(tmp==WSAECONNRESET)ret=(-2);
#endif

#if (defined _SH2)||(defined _SH4)
  tmp=tfGetSocketError(s);
  if(tmp==TM_ESHUTDOWN)ret=(-2);
#endif

#ifdef unix
  if(ECONNRESET == errno){ ret=(-2); }
#endif
  return ret;
}
#endif
/*
**
**  テストコード
**
*/

#if 0

main()
{
  STMACADDRESS ma;
  unsigned int ip;

  memset(&ma, 0, sizeof(STMACADDRESS));

#ifdef unix
  struct in_addr in_val;
  inet_pton(AF_INET, "43.16.61.219", &in_val);
  memcpy(&ip, &in_val, sizeof(struct in_addr));
#else
  ip = 0;
#endif

  winsock_getipnettable(&ma,ip);
  printf("Hi :%04x, Lo :%08x\n", ma.hi, ma.lo);
}

#endif


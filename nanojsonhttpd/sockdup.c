/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "sockdup.h"


SOCKET dupsocket(SOCKET s)
{
	SOCKET ss=-1;
#ifdef unix
	ss=dup(s);
#endif

#ifdef _WIN32

	WSAPROTOCOL_INFO info;
	memset(&info,0,sizeof(info));
//	PROCESS_INFORMATION pi;

	WSADuplicateSocket(s, GetCurrentProcessId(), &info);
	ss = WSASocket(FROM_PROTOCOL_INFO,FROM_PROTOCOL_INFO,FROM_PROTOCOL_INFO,
		&info,0,0);
#endif
	return ss;
}



#if 0

int main()
{
	struct sockaddr_in dstAddr;
	unsigned short port = 80;
	SOCKET s,s2;
	int ret;
	char buf[2048];
	char tmp[2048];
	int sz;
	
	
	winsock_init();
	
	memset(&dstAddr, 0, sizeof(dstAddr));
  	dstAddr.sin_port = htons(port);
  	dstAddr.sin_family = AF_INET;
  	dstAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
  	s = socket(AF_INET, SOCK_STREAM, 0);
  	if(s==(-1)){
		return;
  	}
  	
	ret=connect(s, (struct sockaddr *) &dstAddr, sizeof(dstAddr));
	if(ret==-1)
	{
		closesocket(s);
		return;
	}

	s2=dupsocket(s);


	strncpy(buf,"GET / HTTP1.0\r\n\r\n",100);
	send(s,buf,strlen(buf),0);
	closesocket(s);

	tmp[0]=0;
	sz=recv(s2,tmp,2000,0);
	if(sz>0)tmp[sz]=0;
	if(sz<=0)printf("recv error!");

	printf("%s",tmp);

	closesocket(s2);
		
	winsock_done();



}


#endif


/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef df_NETWORKIF_H
#define df_NETWORKIF_H



#ifdef __cplusplus
extern "C"
{
#endif

#define MYIPADDRESS_ADDRESS_LEN 16

typedef struct st_myipaddress{
	int type;
	unsigned char address[MYIPADDRESS_ADDRESS_LEN];
	int len;
} MYIPADDRESS;
	
	
#define MYIPADDRESS_TYPE_NONE 0
#define MYIPADDRESS_TYPE_IPV4 1
#define MYIPADDRESS_TYPE_IPV6 2
#define MYIPADDRESS_TYPE_ETHERNET 3

typedef struct st_myipaddress_info{
	int type;
	MYIPADDRESS ipAddress;
	MYIPADDRESS netMask;
	MYIPADDRESS phyAddress;
} MYIPADDRESSINFO;



typedef struct st_mynetworkif{
	int num;
	MYIPADDRESSINFO** address;
} MYNETWORKIF;


MYNETWORKIF* networkif_alloc();
int networkif_free(MYNETWORKIF*);
int networkif_add(MYNETWORKIF*,MYIPADDRESSINFO* pipadress);
int networkif_num(MYNETWORKIF*);
int networkif_get(MYNETWORKIF*,int i,MYIPADDRESSINFO* pipadress);
MYNETWORKIF* networkif_enumall();
int networkif_print(MYIPADDRESSINFO* pipaddress);
int networkif_toString(MYIPADDRESSINFO* pipaddress,char*,int sz);
int networkif_fromString(MYIPADDRESSINFO* pipaddress,char* str,int sz);


//int networkif_internal_enum(MYNETWORKIF* ret,int(*f)(MYNETWORKIF*,MYIPADDRESSINFO*));
//int networkif_internal_print(MYNETWORKIF * p,MYIPADDRESSINFO* pipaddress);

#ifdef __cplusplus
}
#endif


#endif /* df_NETWORKIF_H */




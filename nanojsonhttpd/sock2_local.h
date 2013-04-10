/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

/*****************************************************************************
�����I��C�v���v���Z�b�T��`

#define         �v���b�g�t�H�[��:
-------         ----------
ARM_ULIB        Huw Rogers �ɂ�� Acorn Archimedes �p�̃t���[ Unix ���C�u����
AZTEC_C         Aztec_C 5.2a
__CYGWIN__      Cygwin
_DCC            Dice C (AMIGA ��)
__GNUC__        Gnu CC (����� DJGPP)
__EMX__         Gnu C �ڐA�� (gcc/emx 0.8e) (OS/2 2.0 �ւ̈ڐA��)
__HIGHC__       MetaWare High C
__IBMC__        C-Set++ (OS/2 2.1 ��)
_MSC_VER        MS VisualC++ 4.2
MWC             Mark Williams C (COHERENT ��)
__MWERKS__      Metrowerks Compiler; Macintosh ����� WIN32 (?)
_POSIX_SOURCE   ??
_QC             Microsoft QuickC
__STDC__        ANSI C ����
__TURBOC__      Turbo C �� Borland C
__USE_POSIX     ??
__WATCOMC__     Watcom C (MS-DOS ��)
__ZTC__         Zortech C

_AIX            AIX �I�y���[�e�B���O �V�X�e��
__APPLE__       Apple Darwin
AMIGA           SAS/C 5.10 �܂��� Dice C (AMIGA ��)
__amigaos__     Gnu CC (AMIGA ��)
atarist         ATARI-ST under Gnu CC
__FreeBSD__     FreeBSD
GNUDOS          DJGPP (version 1.08 �ł� obsolete)
__GO32__        DJGPP (future?)
hpux            HP-UX
linux           Linux
macintosh       Macintosh (THINK_C and __MWERKS__ define)
MCH_AMIGA       Aztec_c 5.2a (AMIGA ��)
__MACH__        Apple Darwin
MSDOS           Microsoft C 5.10 ����� 6.00A
__MSDOS__       Turbo C, Borland C, DJGPP
nosve           Control Data NOS/VE
SVR2            System V Revision 2.
__SVR4          SunOS
THINK_C         Macintosh �p�̊J����
ultrix          VAX with ULTRIX �I�y���[�e�B���O �V�X�e��
unix            �قƂ�ǂ� Unix ����т��̗ގ��̃V�X�e���A����� DJGPP (!?)
__unix__        Gnu CC �� DJGPP
_UNICOS         Cray �I�y���[�e�B���O �V�X�e��
vaxc            VAX C �R���p�C��
VAXC            VAX C �R���p�C��
vax11c          VAX C �R���p�C��
VAX11           VAX C �R���p�C��
_Windows        Borland C 3.1 �R���p�C�� for Windows
_WIN32          MS VisualC++ 4.2 �� Cygwin (Win32 API)
vms             (and VMS) VAX-11 C under VMS.

__alpha         DEC Alpha �v���Z�b�T
__alpha__       DEC Alpha �v���Z�b�T
hp9000s800      HP RISC �v���Z�b�T
__i386__        DJGPP
i386            DJGPP
MULTIMAX        Encore computer
ppc             PowerPC
__ppc__         PowerPC
pyr             Pyramid 9810 �v���Z�b�T
__sgi__         Silicon Graphics Inc.
sparc           SPARC �v���Z�b�T
sequent         Sequent computer
tahoe           CCI Tahoe �v���Z�b�T
vax             VAX �v���Z�b�T
*****************************************************************************/


#ifndef SOCK_LOCAL_H
#define SOCK_LOCAL_H


#include <stdio.h>
#include <string.h>

/*�E�C���h�E�Y�n�̏���*/
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <Iphlpapi.h>
#endif	/* _WIN32 */


/*SH�̏���*/
#if (defined _SH2)||(defined _SH4)
#include <trsocket.h>

#define closesocket(s) tfClose(s)
#endif


/*UNIX�n�̏���*/
#if defined(unix) || defined(ANDROID_NDK)
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/tcp.h>

#ifdef __FreeBSD__
#include <sys/filio.h>
#endif	/* __FreeBSD__ */

#if defined(linux) || defined(ANDROID_NDK)
#include <asm/ioctls.h>
#endif	/* linux */


typedef struct in_addr *LPIN_ADDR;
#define closesocket(s) close(s)

#endif	/* unix */


#ifdef _WIN32
typedef int socklen_t;
#endif

/*SH&UNIX�n�̏���*/
#if (defined _SH2) || (defined _SH4) || (defined unix)
#define SOCKET int

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#ifndef	INADDR_ANY
#define INADDR_ANY              (u_long)0x00000000
#endif
#ifndef	INADDR_NONE
#define INADDR_NONE             0xffffffff
#endif

typedef struct sockaddr* LPSOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
#endif


#ifdef __cplusplus
extern "C"
{
#endif

void winsock_init(void);
void winsock_done(void);
void winsock_asyncmode(SOCKET s);
void winsock_syncmode(SOCKET s);
int winsock_getwaitingbytes(SOCKET s);
int winsock_getlasterror(SOCKET s);

struct st_mac_address{
	unsigned int hi;
	unsigned int lo;
};

typedef struct st_mac_address STMACADDRESS;
typedef struct st_mac_address* LPSTMACADDRESS;


int  winsock_getipnettable(LPSTMACADDRESS mac_address,unsigned int ip_address);



#ifdef __cplusplus
}
#endif


#endif /* SOCK_LOCAL_H */

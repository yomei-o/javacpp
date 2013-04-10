/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef MYTIME_H
#define MYTIME_H


#ifdef _WIN32

#include <time.h>
/*1�b������̃N���b�N��*/
#define myclock_sec() (CLK_TCK)

#endif

#ifdef unix

#include <time.h>
#include <sys/time.h>
/*1�b������̃N���b�N��*/
#define myclock_sec() (1000)

#endif

#if (defined _SH2)||(defined _SH4)

#include "timer.h"
/*1�b������̃N���b�N��*/
#define myclock_sec() (TIME1SOF10M000)

#endif


#ifdef __cplusplus
extern "C"
{
#endif

/*�J�E���g�_�E���V�X�e���N���b�N�̃G�~�����[�V����*/
int myclock();

#ifdef __cplusplus
}
#endif


#endif /* MYTIME_H */

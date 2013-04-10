/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef __YSLEEP_H__
#define __YSLEEP_H__


/*******************************************************************************
 * definition
 */


/*******************************************************************************
 * prototype
 */
#ifdef __cplusplus
extern "C"
{
#endif


/* internal prototype (for static function) */
#ifdef __YSLEEP_C__

#endif

/* external prototype (for global function) */
void ysleep(unsigned int s);
void ymsleep(unsigned int ms);
void yusleep(unsigned int us);

#ifdef __cplusplus
}
#endif


#endif /* __YUTIL_H__*/

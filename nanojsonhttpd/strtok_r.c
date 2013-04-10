/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include <stdio.h>
#include <string.h>  /* strchr() */

#include "strtok_r.h"
char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    char *s = str ? str : *saveptr;
    char *p;

	if(s==NULL){
		if(saveptr)*saveptr=NULL;
		return NULL;
	}
    while (*s && (strchr(delim, *s) != NULL)) {
        s++;
    }
	if(*s==0){
		if(saveptr)*saveptr=NULL;
		return NULL;
	}
    p = s;

    while (*p && (strchr(delim, *p) == NULL)) {
        p++;
    }

    if (*p) {
        if(saveptr)*saveptr = p + 1;
        *p = '\0';
    } else {
        if(saveptr)*saveptr = p;
    }
    return s;
}


/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_STRINGTOKENIZER_H__
#define D_STRINGTOKENIZER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "String_.h"


class StringTokenizer{
public :
	StringTokenizer();
	StringTokenizer(int id);
	StringTokenizer(char* ss);
	StringTokenizer(String & ss);
	StringTokenizer(char* ss,char* sseepp);
	StringTokenizer(String & ss,String &sseepp);
	virtual ~StringTokenizer();

	StringTokenizer& operator =(StringTokenizer *rhs);

	bool hasMoreTokens();
	String 	nextToken();
public:
	String str;
	String sep;
	int isfirst;
	char* p;
};



#endif /* D_STRINGTOKENIZER_H__ */



/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef st_NanoJsonHttpdMain_H_
#define st_NanoJsonHttpdMain_H_


class String;

class NanoJsonHttpdMain{

public:
	static void main(int argc,char* argv[]);
	static void print(char* str);
	static void print(String& str);
	static void println(char* str);
	static void println(String& str);
	static void sleep(int ms);
};

#endif


 


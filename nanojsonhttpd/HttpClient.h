/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_HttpClient_H__
#define D_HttpClient_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


class String;
class InputStream;


class HttpClient{
public :
	HttpClient();
	HttpClient(int id);
	virtual ~HttpClient();
	HttpClient& operator =(HttpClient *rhs);

	static String readLine(InputStream & s);
	static void readNull(InputStream & s);
	static String readString(InputStream & s);

	static bool readResponse(InputStream & s);

	static int getStatusCode();
	static void setStatusCode(int);
	static void clearStatusCode();

	static String getLocation();
	static void setLocation(String& str);
	static void clearLocation();

	static String getPath();
	static void setPath(String& str);
	static void clearPath();

	static String getServer();
	static void setServer(String& str);
	static void clearServer();

	static int getPort();
	static void setPort(int port);
	static void clearPort();

	static bool isHttp();
	static void setHttp();
	static void clearHttp();

	static bool parseUrl(String & str);
	static void parseLocationIfNeeded(String & line);


	static String escapeUrlString(String& str);
	static String doGetInHttp(String& url);
	static String doPostFileInHttp(String& url,String& file);

	static String doTest();
public:
};

static HttpClient HttpClient(0);

#endif /* D_HttpClient_H__ */



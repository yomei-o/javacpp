/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_HTTPAPI_H__
#define D_HTTPAPI_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Thread.h"
#include "String_.h"
#include "Socket.h"

class Properties;
class InputStream;
class OutputStream;

class HttpApi{
public :
	HttpApi();
	HttpApi(int id);
	virtual ~HttpApi();
	HttpApi& operator =(HttpApi *rhs);


	static void doGetApi(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	static void doPostApi(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	static void apiJsonp(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	static void apiPostJson(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	static void apiFile(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	static void apiPostPhoto(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	static void apiTest(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);

	static String servJsonp(String& uri,Properties& header,Properties& param,Properties& session);
	static void sendError(OutputStream &os, String& status, String& msg );
	static void sendString(OutputStream &os,String& msg );
	static void sendHTML(OutputStream &os,String& msg );
	static void sendResponse(OutputStream &os,String& status, String& mime, Properties& header, InputStream& data ,int ll);

	static String jsonpGetFileList(String& uri,Properties& header,Properties& param);
	static String getDefaultDirectory();

	static String getMimeString(String& mime);

	static void decodeParms(String& parms, Properties& p );
	static String decodePercent( String& str );

	static String MIME_PLAINTEXT;
	static String MIME_HTML;
	static String MIME_JAVASCRIPT;
	static String MIME_JPEG;
	static String MIME_PNG;
	static String MIME_JSON;

	static String HTTP_OK;
	static String HTTP_REDIRECT;
	static String HTTP_FORBIDDEN;
	static String HTTP_NOTFOUND;
	static String HTTP_BADREQUEST;
	static String HTTP_INTERNALERROR;
	static String HTTP_NOTIMPLEMENTED;
	
};

static HttpApi HttpApi(0);


#endif /* D_HTTPAPI_H__ */



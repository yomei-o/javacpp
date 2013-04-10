/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_HTTPSESSION_H__
#define D_HTTPSESSION_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Thread.h"
#include "String_.h"
#include "Socket.h"

class Properties;
class InputStream;
class OutputStream;

class HttpSession:public Thread{
public :
	HttpSession(Socket& ss);
	HttpSession(int id);
	HttpSession(const HttpSession & f);
	virtual ~HttpSession();

	HttpSession& operator =(HttpSession *rhs);
	virtual void run();
	
	String  serv(String& uri,Properties& header,Properties& param);

	void doGet(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	void doHead(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);
	void doPost(OutputStream &os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session);

	String  readLine(InputStream &is);
	void sendError(OutputStream &os, String& status, String& msg );
	void sendString(OutputStream &os,String& msg );
	void sendResponse(OutputStream &os,String& status, String& mime, Properties& header, InputStream& data ,int ll);

	void decodeParms(String& parms, Properties& p );
	String decodePercent( String& str );

	static void s_run(void* arg);

	static String MIME_PLAINTEXT;
	static String MIME_HTML;
	static String MIME_JAVASCRIPT;
	static String MIME_JPEG;
	static String MIME_PNG;

	static String HTTP_OK;
	static String HTTP_REDIRECT;
	static String HTTP_FORBIDDEN;
	static String HTTP_NOTFOUND;
	static String HTTP_BADREQUEST;
	static String HTTP_INTERNALERROR;
	static String HTTP_NOTIMPLEMENTED;
	
public:
	Socket s;
};



#endif /* D_HTTPSESSION_H__ */



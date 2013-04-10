/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#define I_USE_NEW_CONFIG

#ifdef JAVA
//  JAVA packagename
package com.yomei.myhttpd;

import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;

#else 

#include "HttpSession.h"
#include "String_.h"
#include "OutputStream.h"
#include "InputStream.h"
#include "InputStreamReader.h"
#include "BufferedReader.h"
#include "SafeBufferedReader.h"
#include "StringTokenizer.h"
#include "Properties.h"
#include "ByteArrayInputStream.h"
#include "InetAddress.h"
#include "HttpApi.h"
#include "Enumeration.h"
#include "Class.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#endif /* JAVA*/



#ifdef JAVA 
#define getchar() System.in.read()
#define println(a) System.out.println(a)
#define printf System.out.printf
#else
#define println(a) printf("%s\n",(char*)(a))
#endif

#ifdef JAVA 
#else
#define null 0
#define byte char
#define true 1
#define false 0
#define boolean bool
#endif



#ifdef JAVA
public class HttpSession extends Thread{
#endif


#ifdef JAVA
	Socket s=null;

	static final String MIME_PLAINTEXT = "text/plain";
	static final String MIME_HTML = "text/html";
	static final String MIME_JAVASCRIPT = "text/javascript;charset=utf-8";
	static final String MIME_JPEG = "image/jpeg";
	static final String MIME_PNG = "image/png";

	static final String HTTP_OK = "200 OK";
	static final String HTTP_REDIRECT = "301 Moved Permanently";
	static final String HTTP_FORBIDDEN = "403 Forbidden";
	static final String HTTP_NOTFOUND = "404 Not Found";
	static final String HTTP_BADREQUEST = "400 Bad Request";
	static final String HTTP_INTERNALERROR = "500 Internal Server Error";
	static final String HTTP_NOTIMPLEMENTED = "501 Not Implemented";
#else
	String HttpSession::MIME_PLAINTEXT = "text/plain";
	String HttpSession::MIME_HTML = "text/html";
	String HttpSession::MIME_JAVASCRIPT = "text/javascript;charset=utf-8";
	String HttpSession::MIME_JPEG = "image/jpeg";
	String HttpSession::MIME_PNG = "image/png";

	String HttpSession::HTTP_OK = "200 OK";
	String HttpSession::HTTP_REDIRECT = "301 Moved Permanently";
	String HttpSession::HTTP_FORBIDDEN = "403 Forbidden";
	String HttpSession::HTTP_NOTFOUND = "404 Not Found";
	String HttpSession::HTTP_BADREQUEST = "400 Bad Request";
	String HttpSession::HTTP_INTERNALERROR = "500 Internal Server Error";
	String HttpSession::HTTP_NOTIMPLEMENTED = "501 Not Implemented";
#endif




#ifdef JAVA
HttpSession(Socket ss)
#else
HttpSession::HttpSession(Socket& ss)
#endif
{
#ifndef JAVA
	prun=s_run;
#endif
	s=ss;
}

#ifndef JAVA
HttpSession::HttpSession(int id)
{
#ifndef JAVA
	prun=s_run;
#endif
}
#endif

#ifndef JAVA
HttpSession::~HttpSession()
{
}
#endif


#ifndef JAVA
HttpSession& HttpSession::operator =(HttpSession *f)
{
	if(f==NULL)goto end;
	prun=f->prun;
	s=f->s;
	delete f;
end:
	return *this;
}
#endif

#ifdef JAVA
public void run()
#else
void HttpSession::run()
#endif
{
#ifdef JAVA
	byte[] ad=null;
#else
	byte* ad=null;
#endif
	String strad=null;
	String adcls=null;

#ifdef JAVA
	try{
#endif	
	InetAddress las=null;
	InetAddress ias=null;

	las=s.getLocalAddress();
	ias=s.getInetAddress();

	ad=ias.getAddress();
	adcls=ias.getClass().getName();

	strad="address=";
	strad+=strad.valueOf(ad[0]&255)+".";
	strad+=strad.valueOf(ad[1]&255)+".";
	strad+=strad.valueOf(ad[2]&255)+".";
	strad+=strad.valueOf(ad[3]&255);
	println(strad);

#ifndef JAVA
	delete[] ad;
#endif /* JAVA*/
	ad=null;


	if(las==null)println("local address is null");
	if(ias==null)println("inet address is null");


	//printf("HttpSession::run()\n");
	if(s==null)return;
	//printf("HttpSession::run(2)\n");

	OutputStream os=null;
	InputStream is=null;

	is=s.getInputStream();
	os=s.getOutputStream();



	//Security pach by yomei
	//SafeBufferedReader in = null;

	//InputStreamReader isr=null;

	//isr=new InputStreamReader(is);
	
	//Security pach by yomei
	//in=new SafeBufferedReader(isr);
	//isr=null;

	// Read the request line
	String inLine = null;
	//inLine=in.readLine();
	inLine=readLine(is);
	if (inLine == null){
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	StringTokenizer st = null;
	st=new StringTokenizer( inLine );
	if ( !st.hasMoreTokens())
	{
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	String method = null;
	method=st.nextToken();
	if ( !st.hasMoreTokens()){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	String uri = null;
	uri=st.nextToken();

	Properties parms = null;
	parms=new Properties();
	int qmi = uri.indexOf( '?' );

	if ( qmi >= 0 ){
		String zz=null;
		zz=uri.substring( qmi+1 );
		decodeParms( zz, parms );
		zz=uri.substring( 0, qmi );
		uri = decodePercent(zz);
	}
	else uri = decodePercent(uri);

	Properties header = null;
	Properties session = null;
	header=new Properties();
	session=new Properties();
	session.put("method",method);


	if ( st.hasMoreTokens()){
		String line = null;
		//line=in.readLine();
		line=readLine(is);
		while ( line!=null && line.trim().length() > 0 ){
			int p = line.indexOf( ':' );
			/* security by yomei*/
			if(header.size()<100)
				header.put( line.substring(0,p).trim().toLowerCase(), line.substring(p+1).trim());
			//line = in.readLine();
			line = readLine(is);
		}
	}

	if(method.equals("POST")==false && method.equals("GET")==false && method.equals("HEAD")==false){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	if(method.equals("GET")){
		doGet(os,is,uri,header,parms,session);
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	if(method.equals("POST")){
		doPost(os,is,uri,header,parms,session);
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	if(method.equals("HEAD")){
		//doHead(os,is,uri,header,parms,session);
		//in.close();
		is.close();
		os.flush();
		os.close();
		s.close();
		return;
	}
	//in.close();
	is.close();
	os.flush();
	os.close();
	s.close();
	return;	

#ifdef JAVA
	}catch(Exception e){e.printStackTrace();}
#endif	

}

#ifdef JAVA
public String readLine(InputStream is)
#else
String HttpSession::readLine(InputStream& is)
#endif
{
	int i,l;
	String ret=null;
#ifdef JAVA
	byte[] d=null;
#else
	byte* d=null;
#endif
	d=new byte[2048];
	for(i=0;i<2048;i++){
		l=0;
#ifdef JAVA
		try{
#endif
		l=is.read(d,i,1);
#ifdef JAVA
		}catch(Exception e){}
#endif
		if(l<1)break;
		if(d[i]=='\n')break;
	}
	if(i>0){
#ifdef JAVA
		try{
#endif
		ret=new String(d,0,i,"utf-8");
		ret=ret.trim();
#ifdef JAVA
		}catch(Exception e){}
#endif
	}
#ifndef JAVA
	if(d)delete[] d;
#endif
	return ret;
}

#ifdef JAVA
public void doPost(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpSession::doPost(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
#ifdef JAVA
	try{
#endif
	HttpApi.doPostApi(os,is,uri,header,param,session);
#ifdef JAVA
	}catch(Exception e){}
#endif
	return;
}

#ifdef JAVA
public void doHead(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpSession::doHead(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String sret=null;
	if(sret==null){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		return;
	}
	return;
}

#ifdef JAVA
public void doGet(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpSession::doGet(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	//String sret=null;
	//sret=serv(uri,header,param);
	//if(sret==null){
	//	String msg=null;
	//	msg="Bad Request";
	//	sendError(os, HTTP_BADREQUEST,msg  );
	//	return;
	//}
	//sendString(os,sret);
#ifdef JAVA
	try{
#endif
	HttpApi.doGetApi(os,is,uri,header,param,session);
#ifdef JAVA
	}catch(Exception e){}
#endif
}

#ifdef JAVA
public String serv(String uri,Properties header,Properties param)
#else
String HttpSession::serv(String& uri,Properties& header,Properties& param)
#endif
{
	String ret=null;
	ret="hogehogehogehoge\r\n\r\n";
	return ret;
}


#ifdef JAVA
public void sendString(OutputStream os,String msg )
#else
void HttpSession::sendString(OutputStream& os,String& msg )
#endif
{
#ifdef JAVA
	byte[] ms=null;
#else
	byte* ms=null;
#endif
	String ss=null;
	String status=null;

	status="200 OK";

	ss=msg;
	ss+="\0";

#ifdef JAVA
	try{
#endif
	ms=ss.getBytes("utf-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(ms==null)return;

	int len=0;

	while(ms[len]!=0)len++;

	ByteArrayInputStream bais=null;
	Properties p=null;
	p=new Properties();

	bais=new ByteArrayInputStream(ms,0,len);
	sendResponse(os, status, MIME_PLAINTEXT, p, bais,len);

}



#ifdef JAVA
public void sendError(OutputStream os, String status, String msg )
#else
void HttpSession::sendError(OutputStream& os, String& status, String& msg )
#endif
{
#ifdef JAVA
	byte[] ms=null;
#else
	byte* ms=null;
#endif
	ms=msg.getBytes();
	ByteArrayInputStream bais=null;
	Properties p=null;
	p=new Properties();

	bais=new ByteArrayInputStream(ms,0,msg.length());
	sendResponse(os, status, MIME_JAVASCRIPT, p, bais, msg.length());

}


#ifdef JAVA
public void sendResponse( OutputStream out,String status, String mime, Properties header, InputStream data,int ll )
#else
void HttpSession::sendResponse(OutputStream& out, String& status, String& mime, Properties& header, InputStream& data,int ll )
#endif
{
#ifdef JAVA
	try{
#endif
	if ( status == null )return;

//	OutputStream out = s.getOutputStream();
	
	String pw = null;
	pw= "";
	pw+="HTTP/1.0 " + status + " \r\n";

	if ( mime != null ){
		pw+="Content-Type: " + mime + "\r\n";
	}
	if ( ll>0 ){
		pw+="Content-Length: " + pw.valueOf(ll) + "\r\n";
	}
	pw+="Pragma: no-cache\r\n";
	pw+="Cache-Control: no-cache\r\n";
	pw+="Connection: close\r\n";

	int ct;
	ct=header.size();


	Enumeration e = header.keys();
	while ( e.hasMoreElements()){
		String key = (String)e.nextElement();
		String value = header.getProperty( key );
		pw+=key + ": " + value + "\r\n";
	}

	pw+="\r\n";
	pw+="\0";

#ifdef JAVA
	byte[] b=null;
#else
	byte* b=null;
#endif
	b=pw.getBytes();
	int len=0;
	
	while(b[len]!=0)len++;

	if(len>0){
		out.write(b,0,len);
	}
	pw=null;
	if ( data != null ){
#ifdef JAVA
		byte[] buff = null;
#else
		byte* buff = null;
#endif
		buff=new byte[2048];
		while (true){
			int read;
			read = data.read( buff, 0, 2048 );
			if (read <= 0)break;
			out.write( buff, 0, read );
		}
#ifndef JAVA
		delete[] buff;
#endif
	}
//	out.flush();
//	out.close();
	if ( data != null ){
		data.close();
	}
#ifdef JAVA
	}catch(Exception e ){}
#endif
}


#ifdef JAVA
public void decodeParms( String parms, Properties p )
#else
void HttpSession::decodeParms(String& parms, Properties& p )
#endif
{
	if ( parms == null )return;

	StringTokenizer st = null;
	st=new StringTokenizer( parms, "&" );
	while ( st.hasMoreTokens()){
		String e = null;
		e=st.nextToken();
		int sep = e.indexOf( '=' );


		if ( sep >= 0 ){
			String aa=null;
			String zz=null;
			zz=e.substring( 0, sep );
			aa=decodePercent(zz);
			aa=aa.trim();
			String bb=null;
			zz=e.substring( sep+1 );
			bb=decodePercent(zz);
			//sercurity by yomei
			if(p.size()<100)p.put(aa,bb);
		}
	}
}

#ifdef JAVA
public String decodePercent( String str ) 
#else
String HttpSession::decodePercent( String& str )
#endif
{
	if(str==null){
		String ret=null;
		ret="null";
		return ret;
	}
#ifdef JAVA
	byte[] sb = null;
#else
	byte* sb = null;
#endif
	int strlen=str.length();
	sb=new byte[strlen];
	int sblen=0;
	for( int i=0; i<strlen; i++ ){
		int c = str.charAt( i );
		switch ( c ){
		case '+':
			sb[sblen]=(byte)' ';
			break;
		case '%':
			/* security patch by yomei*/
			if(strlen<i+3)continue;
			sb[sblen]=(byte)Integer.parseInt( str.substring(i+1,i+3), 16 );
			i += 2;
			break;
		default:
			sb[sblen]= (byte)c ;
			break;
		}
		sblen++;
	}
#ifdef JAVA
	byte[] data=null;
#else
	byte* data=null;
#endif
	if(sblen>0){
		data=new byte[sblen];
		for(int i=0;i<sblen;i++)data[i]=sb[i];
	}
	if(data==null){
		data=new byte[1];
		data[0]=0;
	}
    String ret=null;
#ifdef JAVA
	try{
#endif
	ret=new String(data,0,sblen,"UTF-8");
#ifdef JAVA
	}catch(Exception e){}
#endif
#ifndef JAVA
	if(data)delete[] data;
	if(sb)delete[] sb;
#endif
	return ret;
}



#ifndef JAVA
void HttpSession::s_run(void* arg)
{
	HttpSession* r=new HttpSession(((HttpSession*)arg)->s);
	((Runnable*)arg)->flag=1;
	r->run();
	delete r;
}
#endif





#ifdef JAVA
}
#endif

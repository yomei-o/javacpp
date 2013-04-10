/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA
package com.yomei.myhttpd;
import java.io.*;
import java.lang.*;
import java.net.*;
import java.net.Socket;

#else /* JAVA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "String_.h"
#include "Socket2.h"
#include "InetSocketAddress.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "File.h"
#include "FileInputStream.h"

#include "HttpClient.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA */



#ifdef JAVA 
#ifdef ANDROID
#define println(a) System.out.println(a)
#else
#define println(a) System.out.println(a)
#endif
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
#define BEGIN_TRY() try{
#define END_TRY() }catch(Exception e){ e.printStackTrace();}
#else
#define BEGIN_TRY()
#define END_TRY()
#endif



#ifdef JAVA
public class HttpClient{
#endif /* JAVA */


#ifdef JAVA
public static String location=null;
public static String cookie=null;
public static int statusCode=0;
public static int port=0;
public static String server=null;
public static String path=null;
public static boolean f_isHttp=false;
#else
static String location=null;
static String cookie=null;
static int statusCode=0;
static int port=0;
static String server=null;
static String path=null;
static bool f_isHttp=false;
#endif



#ifdef JAVA
public HttpClient()
#else
HttpClient::HttpClient()
#endif
{
}

#ifndef JAVA
HttpClient::HttpClient(int id)
{
}
#endif

#ifndef JAVA
HttpClient::~HttpClient()
{
}
#endif


#ifndef JAVA
class HttpClient& HttpClient::operator =(class HttpClient *f)
{
	if(f==NULL)goto end;
	delete f;
end:
	return *this;
}
#endif




#ifdef JAVA
public static String  readLine(InputStream s)
#else
String HttpClient::readLine(InputStream & s)
#endif
{
	int i=0,len=0;
#ifdef JAVA
	byte[] data=null;
#else
	byte* data=null;
#endif
	data=new byte[1024];

	String ret=null;

	while(true){
		if(i>1000)break;
		len=0;

		BEGIN_TRY();
		len=s.read(data,i,1);
		END_TRY();

		if(len<1)break;
		if(data[i]=='\n')break;
		if(data[i]>0 && data[i]<' ')continue;
		i++;
	}
	if(i==0 && len<1)return ret;
	data[i]=0;

	ret="error";
	BEGIN_TRY();
	ret=new String(data,0,i,"utf-8");
	END_TRY();

#ifndef JAVA
	delete[] data; 
#endif
	return ret;
}


#ifdef JAVA
public static void readNull(InputStream s)
#else
void HttpClient::readNull(InputStream & s)
#endif
{
	int len=0;
	int i=0;
#ifdef JAVA
	byte[] data=null;
#else
	byte* data=null;
#endif
	data=new byte[1024];

	//String ret=null;

	while(true){
		len=0;
		if(i>1000)break;
		BEGIN_TRY();
		len=s.read(data,0,1020);
		END_TRY();
		if(len<1)break;

		//ret=null;
		//BEGIN_TRY();
		//ret=new String(data,0,len,"utf-8");
		//END_TRY();
		//println(ret);
		i++;
	}

#ifndef JAVA
	delete[] data; 
#endif
}

#ifdef JAVA
public static String readString(InputStream s)
#else
String HttpClient::readString(InputStream & s)
#endif
{
	int len=0;
	int off=0;
	int mlen=1024*64-1;
#ifdef JAVA
	byte[] data=null;
#else
	byte* data=null;
#endif
	data=new byte[1024*64];
	
	String ret=null;

	while(true){
		len=0;
		BEGIN_TRY();
		len=s.read(data,off,mlen-off);
		END_TRY();
		if(len<1)break;
		off+=len;
	}
	if(off==0)return ret;

	BEGIN_TRY();
	ret=new String(data,0,off,"utf-8");
	END_TRY();
	//println("ret=>>"+ret+"<<");

#ifndef JAVA
	delete[] data; 
#endif
	return ret;
}




#ifdef JAVA
public static int getStatusCode()
#else
int HttpClient::getStatusCode()
#endif
{
	return statusCode;
}

#ifdef JAVA
public static void setStatusCode(int c)
#else
void HttpClient::setStatusCode(int c)
#endif
{
	statusCode=c;
}

#ifdef JAVA
public static void clearStatusCode()
#else
void HttpClient::clearStatusCode()
#endif
{
	statusCode=0;
}



#ifdef JAVA
public static String getLocation()
#else
String HttpClient::getLocation()
#endif
{
	return location;
}

#ifdef JAVA
public static void setLocation(String c)
#else
void HttpClient::setLocation(String& c)
#endif
{
	location=c;
}

#ifdef JAVA
public static void clearLocation()
#else
void HttpClient::clearLocation()
#endif
{
	location=null;
}

#ifdef JAVA
public static int getPort()
#else
int HttpClient::getPort()
#endif
{
	return port;
}

#ifdef JAVA
public static void setPort(int c)
#else
void HttpClient::setPort(int c)
#endif
{
	port=c;
}

#ifdef JAVA
public static void clearPort()
#else
void HttpClient::clearPort()
#endif
{
	port=0;
}


#ifdef JAVA
public static String getServer()
#else
String HttpClient::getServer()
#endif
{
	return server;
}

#ifdef JAVA
public static void setServer(String c)
#else
void HttpClient::setServer(String& c)
#endif
{
	server=c;
}

#ifdef JAVA
public static void clearServer()
#else
void HttpClient::clearServer()
#endif
{
	server=null;
}


#ifdef JAVA
public static String getPath()
#else
String HttpClient::getPath()
#endif
{
	return path;
}

#ifdef JAVA
public static void setPath(String c)
#else
void HttpClient::setPath(String& c)
#endif
{
	path=c;
}

#ifdef JAVA
public static void clearPath()
#else
void HttpClient::clearPath()
#endif
{
	path=null;
}

#ifdef JAVA
public static boolean isHttp()
#else
bool HttpClient::isHttp()
#endif
{
	return f_isHttp;
}

#ifdef JAVA
public static void setHttp()
#else
void HttpClient::setHttp()
#endif
{
	f_isHttp=true;
}

#ifdef JAVA
public static void clearHttp()
#else
void HttpClient::clearHttp()
#endif
{
	f_isHttp=false;
}



#ifdef JAVA
public static boolean parseUrl(String url)
#else
bool HttpClient::parseUrl(String& url)
#endif
{
	int idx,idx2=-1;
	int port=0;
	String server=null;
	String nokori=null;
	String path=null;

	if(url==null)return false;

	clearHttp();
	
	clearPort();
	clearPath();
	clearServer();

	idx=url.indexOf("http://");
	if(idx!=-1){
		setHttp();
		idx2=idx+7;
		port=80;
	}
	if(idx2==-1)return false;

	nokori=url.substring(idx2);
	idx=nokori.indexOf("/");
	if(idx<=0)return false;

	path=nokori.substring(idx);
	nokori=nokori.substring(0,idx);
	idx=nokori.indexOf(":");
	if(idx!=-1){
		String pt=null;
		pt=nokori.substring(idx+1);
		port=Integer.parseInt(pt);
		nokori=nokori.substring(0,idx);
	}
	server=nokori;

	setPort(port);
	setServer(server);
	setPath(path);

	return true;
}



#ifdef JAVA
public static String escapeUrlString(String str)
#else
String HttpClient::escapeUrlString(String & str)
#endif
{
	String ret=null;
	int len=0;
	int i=0,j=0;
#ifdef JAVA
	byte[] moto=null;
	byte[] saki=null;
#else
	byte* moto=null;
	byte* saki=null;
#endif

	if(str==null)return ret;

	len=str.length();
	if(len==0){
		ret="";
		return ret;
	}

	BEGIN_TRY();
	moto=str.getBytes("utf-8");
	END_TRY();
	if(moto==null){
		ret="error";
		return ret;
	}
	saki=new byte[len*4];
	for(i=0;i<len;i++){
		switch(moto[i]){
		default:
			saki[j++]=moto[i];
			break;
		case ' ':
			saki[j++]=(byte)'%';
			saki[j++]=(byte)'2';
			saki[j++]=(byte)'0';
			break;
		case '+':
			saki[j++]=(byte)'%';
			saki[j++]=(byte)'2';
			saki[j++]=(byte)'B';
			break;
		case '%':
			saki[j++]=(byte)'%';
			saki[j++]=(byte)'2';
			saki[j++]=(byte)'5';
			break;
		case '/':
			saki[j++]=(byte)'%';
			saki[j++]=(byte)'2';
			saki[j++]=(byte)'F';
			break;
		case '=':
			saki[j++]=(byte)'%';
			saki[j++]=(byte)'3';
			saki[j++]=(byte)'D';
			break;
		case '&':
			saki[j++]=(byte)'%';
			saki[j++]=(byte)'2';
			saki[j++]=(byte)'6';
			break;
		}
	}
	BEGIN_TRY();
	ret=new String(saki,0,j,"utf-8");
	END_TRY();
	if(ret==null)ret="error";

#ifndef JAVA
	if(saki)delete[] saki;
#endif

	return ret;
}



#ifdef JAVA
public static boolean readResponse(InputStream is)
#else
bool HttpClient::readResponse(InputStream & is)
#endif
{
	String line=null;
	int idx=-1;

	line=readLine(is);
	if(line==null)return false;
	
	line=line.trim();
	idx=0;
	idx=line.indexOf(" ");
	if(idx<1)return false;
	line=line.substring(idx);
	line=line.trim();
	idx=line.indexOf(" ");
	if(idx<1)return false;
	line=line.substring(0,idx);
	line=line.trim();
	
	int retcode=0;
	retcode=Integer.parseInt(line);
	setStatusCode(retcode);
	return true;
}



#ifdef JAVA
public static void parseLocationIfNeeded(String line)
#else
void HttpClient::parseLocationIfNeeded(String& line)
#endif
{
	int idx;
	idx=line.indexOf(":");
	if(idx>0){
		String mae=null;
		String ato=null;
		mae=line.substring(0,idx);
		ato=line.substring(idx+1);
		mae=mae.trim();
		ato=ato.trim();
		mae=mae.toLowerCase();
		if(mae.equals("location")){
			setLocation(ato);
		}
	}
}


#ifdef JAVA
static String doGetInHttp(String url)
#else
String HttpClient::doGetInHttp(String & url)
#endif
{
	Socket s=null;

	InetSocketAddress isa=null;
	OutputStream os=null;
	InputStream is=null;

	String str=null;

	clearStatusCode();
	clearLocation();

	if(parseUrl(url)==false)return str;
	if(isHttp()==false)return str;
	
	isa=new InetSocketAddress(getServer(),getPort());

	BEGIN_TRY();
	s=new Socket();
	END_TRY();
	if(s==null){
		return str;
	}

	BEGIN_TRY();
	s.setSoTimeout(1000*10);
	END_TRY();


	BEGIN_TRY();
	s.connect(isa,1000*10);	
	//s.connect(isa);	
	END_TRY();


	if(s.isConnected()==false){
		BEGIN_TRY();
		s.close();
		END_TRY();
		return str;
	}

//println("#### doTest connected ####");


	str="GET ";
	str+=getPath();

	str+=" HTTP/1.0\r\n";
	str+="Cache-Control: no-cache\r\n";
	str+="Pragma: no-cache\r\n";
	str+="Connection: close\r\n";

	str+="Host: ";
	str+=server;
	str+="\r\n";

	str+="\r\n";

	println("str=>>"+str+"<<");

	BEGIN_TRY();
	os=s.getOutputStream();
	END_TRY();

	BEGIN_TRY();
	os.write(str.getBytes("utf-8"),0,str.length());
	END_TRY();


	BEGIN_TRY();
	is=s.getInputStream();
	END_TRY();


	String line=null;
	str=null;

	do{
		boolean bodyread=false;
		if(readResponse(is)==false)break;

		while(true){
			line=null;
			line=readLine(is);
			if(line==null)break;
			if(line.equals("")){
				bodyread=true;
				break;
			}
			parseLocationIfNeeded(line);
		}
		if(bodyread){
			//readNull(is);
			str=readString(is);
		}
	}while(false);

	BEGIN_TRY();
	is.close();
	END_TRY();
	BEGIN_TRY();
	os.close();
	END_TRY();
	BEGIN_TRY();
	s.close();
	END_TRY();

	//println("cookiestr="+cookiestr);
	if(getStatusCode()==301 || getLocation()!=null){
		String t=null;
		t=getLocation();
		return doGetInHttp(t);
	}
	return str;
}



#ifdef JAVA
static String doPostFileInHttp(String url,String file)
#else
String HttpClient::doPostFileInHttp(String & url,String& file)
#endif
{
	Socket s=null;

	InetSocketAddress isa=null;
	OutputStream os=null;
	InputStream is=null;
	InputStream fis=null;


	String str=null;
	String boundary=null;
	String dispotion=null;
	String fn=null;
	File f=null;

	int clen=0;
	int idx;
	int wlen=0;

#ifdef JAVA
	byte[] tmp=null;
#else
	byte* tmp=null;
#endif

	clearStatusCode();
	clearLocation();


	if(parseUrl(url)==false)return str;
	if(isHttp()==false)return str;
	if(file==null)return str;

	f=new File(file);
	if(f.exists()==false)return str;
	BEGIN_TRY();
	fis=new FileInputStream(file);
	END_TRY();
	if(fis==null)return str;


	fn=file;
	idx=fn.lastIndexOf("/");
	if(idx>0){
		fn=fn.substring(idx+1);
	}

	isa=new InetSocketAddress(getServer(),getPort());

	BEGIN_TRY();
	s=new Socket();
	END_TRY();
	if(s==null){
		BEGIN_TRY();
		fis.close();
		END_TRY();
		return str;
	}

	BEGIN_TRY();
	s.setSoTimeout(1000*3);
	END_TRY();


	BEGIN_TRY();
	s.connect(isa,1000*3);	
	//s.connect(isa);	
	END_TRY();


	if(s.isConnected()==false){
		BEGIN_TRY();
		fis.close();
		END_TRY();
		BEGIN_TRY();
		s.close();
		END_TRY();
		return str;
	}

	println("#### doPostFileTest connected ####");


	str="POST ";
	str+=getPath();
	str+=" HTTP/1.0\r\n";
	str+="Cache-Control: no-cache\r\n";
	str+="Pragma: no-cache\r\n";
	str+="Connection: close\r\n";

	boundary="AAAAAAAAAABBBBBBBBBBCCCCCCCCCC";
	str+="Content-type: multipart/form-data; boundary="+boundary+"\r\n";

	dispotion="Content-Disposition: form-data; name=\"file\"; filename=\""+fn+"\"\r\n\r\n";

	clen=boundary.length()+4;
	clen+=dispotion.length();
	clen+=(int)(f.length())+2;
	clen+=boundary.length()+6;
	str+="Content-length: "+str.valueOf(clen)+"\r\n";

	str+="\r\n";


	println("str=>>"+str+"<<");

	BEGIN_TRY();
	os=s.getOutputStream();
	END_TRY();

	do{

	wlen=-1;
#ifdef JAVA
	try{
		wlen=1;
		os.write(str.getBytes("utf-8"),0,str.length());
	}catch(Exception e){wlen=-1;}
#else
	wlen=os.write(str.getBytes("utf-8"),0,str.length());
#endif
	if(wlen<=0)break;

	str="--"+boundary+"\r\n";

	wlen=-1;
#ifdef JAVA
	try{
		wlen=1;
		os.write(str.getBytes("utf-8"),0,str.length());
	}catch(Exception e){wlen=-1;}
#else
	wlen=os.write(str.getBytes("utf-8"),0,str.length());
#endif
	if(wlen<=0)break;

	str=dispotion;
	wlen=-1;
#ifdef JAVA
	try{
		wlen=1;
		os.write(str.getBytes("utf-8"),0,str.length());
	}catch(Exception e){wlen=-1;}
#else
	wlen=os.write(str.getBytes("utf-8"),0,str.length());
#endif
	if(wlen<=0)break;

	tmp=new byte[65536];

	while(true){
		int i;
		i=0;
		BEGIN_TRY();
		i=fis.read(tmp,0,65536);
		END_TRY();
		if(i<=0)break;
		wlen=-1;
#ifdef JAVA
		try{
			wlen=1;
			os.write(tmp,0,i);
		}catch(Exception e){wlen=-1;}
#else
		wlen=os.write(tmp,0,i);
#endif
		if(wlen<=0)break;

	}
#ifndef JAVA
	if(tmp)delete[] tmp;
#endif
	if(wlen<=0)break;

	str="\r\n--"+boundary+"--\r\n";
#ifdef JAVA
	try{
		wlen=1;
		os.write(str.getBytes("utf-8"),0,str.length());
	}catch(Exception e){wlen=-1;}
#else
	wlen=os.write(str.getBytes("utf-8"),0,str.length());
#endif
	if(wlen<=0)break;

	BEGIN_TRY();
	is=s.getInputStream();
	END_TRY();


	String line=null;
	str=null;

	do{
		boolean bodyread=false;
		if(readResponse(is)==false)break;

		while(true){
			line=null;
			line=readLine(is);
			if(line==null)break;
			if(line.equals("")){
				bodyread=true;
				break;
			}
			parseLocationIfNeeded(line);
		}
		if(bodyread){
			//readNull(is);
			str=readString(is);
		}
	}while(false);

	}while(false);

	BEGIN_TRY();
	fis.close();
	END_TRY();
	BEGIN_TRY();
	is.close();
	END_TRY();
	BEGIN_TRY();
	os.close();
	END_TRY();
	BEGIN_TRY();
	s.close();
	END_TRY();

	//println("cookiestr="+cookiestr);
	if(getStatusCode()==301 || getLocation()!=null){
		String t=null;
		t=getLocation();
		return doPostFileInHttp(t,file);
	}
	return str;
}


#ifdef JAVA
}
#endif /* JAVA */




/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifdef JAVA
//  JAVA packagename
package com.yomei.myhttpd;

import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;

#else 

#include "HttpApi.h"
#include "String_.h"
#include "OutputStream.h"
#include "InputStream.h"
#include "Properties.h"
#include "ByteArrayInputStream.h"
#include "File.h"
#include "FileInputStream.h"
#include "MySort.h"
#include "InputUtil.h"
#include "BinaryUtil.h"
#include "FileOutputStream.h"
#include "CTime.h"
#include "Enumeration.h"
#include "StringTokenizer.h"

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

#ifndef longlong
#ifdef JAVA
#define longlong long
#else
#if defined(_WIN32) && _MSC_VER <=1200
#define longlong _int64
#else
#define longlong long long
#endif /* _MSC_VER */
#endif /* JAVA */
#endif /* longlong */

#ifdef JAVA
#define deleteFile delete
#endif


#ifndef JAVA
#define ArrayOf(a,b) (*a[b])
#else
#define ArrayOf(a,b) (a[b])
#endif

#ifdef JAVA
#define ArrayLength(ii,a) ii=a.length
#else
#define ArrayLength(ii,a) {ii=0; while(a[ii]!=null)ii++;}
#endif



#ifdef JAVA
public class HttpApi{
#endif


#ifdef JAVA
	static final String MIME_PLAINTEXT = "text/plain";
	static final String MIME_HTML = "text/html";
	static final String MIME_JAVASCRIPT = "text/javascript;charset=utf-8";
	static final String MIME_JPEG = "image/jpeg";
	static final String MIME_PNG = "image/png";
	static final String MIME_JSON = "application/json";

	static final String HTTP_OK = "200 OK";
	static final String HTTP_REDIRECT = "301 Moved Permanently";
	static final String HTTP_FORBIDDEN = "403 Forbidden";
	static final String HTTP_NOTFOUND = "404 Not Found";
	static final String HTTP_BADREQUEST = "400 Bad Request";
	static final String HTTP_INTERNALERROR = "500 Internal Server Error";
	static final String HTTP_NOTIMPLEMENTED = "501 Not Implemented";
#else
	String HttpApi::MIME_PLAINTEXT = "text/plain";
	String HttpApi::MIME_HTML = "text/html";
	String HttpApi::MIME_JAVASCRIPT = "text/javascript;charset=utf-8";
	String HttpApi::MIME_JPEG = "image/jpeg";
	String HttpApi::MIME_PNG = "image/png";
	String HttpApi::MIME_JSON = "application/json";

	String HttpApi::HTTP_OK = "200 OK";
	String HttpApi::HTTP_REDIRECT = "301 Moved Permanently";
	String HttpApi::HTTP_FORBIDDEN = "403 Forbidden";
	String HttpApi::HTTP_NOTFOUND = "404 Not Found";
	String HttpApi::HTTP_BADREQUEST = "400 Bad Request";
	String HttpApi::HTTP_INTERNALERROR = "500 Internal Server Error";
	String HttpApi::HTTP_NOTIMPLEMENTED = "501 Not Implemented";
#endif




#ifdef JAVA
HttpApi()
#else
HttpApi::HttpApi()
#endif
{
}

#ifndef JAVA
HttpApi::HttpApi(int id)
{
}
#endif

#ifndef JAVA
HttpApi::~HttpApi()
{
}
#endif


#ifndef JAVA
class HttpApi& HttpApi::operator =(class HttpApi *f)
{
	if(f==NULL)goto end;
	delete f;
end:
	return *this;
}
#endif


#ifdef JAVA
public static void doGetApi(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::doGetApi(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String uu=null;
	String msg=null;
#if 1
	if(uri.indexOf("/api/")==0){
		uu=uri.substring(4);
#ifdef JAVA
		try{
#endif
		apiJsonp(os,is,uu,header,param,session);
#ifdef JAVA
		}catch(Exception e){}
#endif
		return;
	}
#endif
#if 1
	else if(uri.indexOf("/file/")==0){
		uu=uri.substring(5);
#ifdef JAVA
		try{
#endif
		apiFile(os,is,uu,header,param,session);
#ifdef JAVA
		}catch(Exception e){}
#endif
		return;
	}
#endif
#if 1
	else if(uri.indexOf("/test/")==0){
		uu=uri.substring(5);
#ifdef JAVA
		try{
#endif
		apiTest(os,is,uu,header,param,session);
#ifdef JAVA
		}catch(Exception e){}
#endif
		return;
	}
#endif	
	msg="Bad Request";
	sendError(os, HTTP_BADREQUEST,msg  );
	return;
}

#ifdef JAVA
public static void doPostApi(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::doPostApi(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String uu=null;
	String msg=null;
#if 1
	if(uri.indexOf("/api/")==0){
		uu=uri.substring(4);

#if 1
		if(uu.indexOf("/postPhoto")==0){
#ifdef JAVA
			try{
#endif
			apiPostPhoto(os,is,uu,header,param,session);			
#ifdef JAVA
			}catch(Exception e){}
#endif
			return;
		}
#endif

#ifdef JAVA
		try{
#endif
		apiPostJson(os,is,uu,header,param,session);
#ifdef JAVA
		}catch(Exception e){}
#endif
	}
#endif


	msg="Bad Request";
	sendError(os, HTTP_BADREQUEST,msg  );
	return;
}


#ifdef JAVA
public static void sendString(OutputStream os,String msg )
#else
void HttpApi::sendString(OutputStream& os,String& msg )
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
	sendResponse(os, status, MIME_JSON, p, bais,len);

}


#ifdef JAVA
public static void sendHTML(OutputStream os,String msg )
#else
void HttpApi::sendHTML(OutputStream& os,String& msg )
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
	sendResponse(os, status, MIME_HTML, p, bais,len);

}


#ifdef JAVA
public static void sendError(OutputStream os, String status, String msg )
#else
void HttpApi::sendError(OutputStream& os, String& status, String& msg )
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
	sendResponse(os, status, MIME_JSON, p, bais, msg.length());

}


#ifdef JAVA
public static void sendResponse( OutputStream out,String status, String mime, Properties header, InputStream data,int ll )
#else
void HttpApi::sendResponse(OutputStream& out, String& status, String& mime, Properties& header, InputStream& data,int ll )
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
	pw+="Connection: close\r\n";
	if(mime.indexOf("image")!=-1){
		pw+="Cache-Control: max-age=1800\r\n";
	}else{
		pw+="Pragma: no-cache\r\n";
		pw+="Cache-Control: no-cache\r\n";
	}
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
public static void apiTest(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::apiTest(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String sret=null;
	sret="hogehoge";

	sret="";
	sret+="<html><body>\r\n";
	sret+="<form method=\"POST\" action=\"/api/postPhoto\" enctype=\"multipart/form-data\">\r\n";
	sret+="<input type=\"hidden\" name=\"test1\" value=\"12345\" />\r\n";
	sret+="<input type=\"file\" name=\"upfile\" size=\"50\" />\r\n";
	sret+="<input type=\"hidden\" name=\"test2\" value=\"67890\" />\r\n";
	sret+="<input type=\"submit\" value=\"Send\" />\r\n";
	sret+="</form>\r\n";
	sret+="</body></html>\r\n";

	sendHTML(os,sret);
}


#ifdef JAVA
public static String servJsonp(String uri,Properties header,Properties param,Properties session)
#else
String HttpApi::servJsonp(String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String ret=null;
	String cb=null;
	String t=null;

	cb=param.getProperty("callback");

	ret="";
	if(cb!=null)ret+=cb+"(\r\n";

#if 1
	if(uri.indexOf("/getFileList")==0){
#ifdef JAVA
		try{
#endif
		ret+=jsonpGetFileList(uri,header,param);
#ifdef JAVA
		}catch(Exception e){}
#endif
	}else
#endif

	if(t==null || t.equals("")){
		t=null;
		return t;
	}
	if(cb!=null)ret+="\r\n);\r\n";
	return ret;
}



#ifdef JAVA
public static void apiFile(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::apiFile(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String fname=null;
	String tmp=null;
	String ext=null;
	String mime=null;

	File f=null;

	int idx;
	
	if(uri==null)uri="error";

	//idx=uri.lastIndexOf("/");
	//if(idx>=0)fname=uri.substring(idx+1);
	fname=uri;
	if(fname.indexOf("/")==0)fname=fname.substring(1);

	if(fname==null)fname="error";
	if(fname.indexOf("./")>0)fname="error";

	idx=fname.lastIndexOf(".");
	if(idx>0){
		ext=fname.substring(idx+1);
	}
	mime=getMimeString(ext);

	tmp=getDefaultDirectory()+"/";
	tmp+=fname;

	fname=tmp;

	f=new File(fname);
	int sz=0;
	sz=(int)f.length();

	if(f==null || f.exists()==false || f.isFile()==false || sz<=0){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		return;
	}
	Properties p=null;
	p=new Properties();
	FileInputStream fis=null;
#ifdef JAVA
	try{
#endif
	fis=new FileInputStream(fname);
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(fis==null){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		return;
	}
	sendResponse(os, HTTP_OK, mime, p, fis, sz);

	return;
}

#ifdef JAVA
public static void apiPostPhoto(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::apiPostPhoto(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String ret=null;
	String str=null;
	String tmp=null;
	String boundary=null;
	int clen=0;
	int idx;
#ifdef JAVA
	byte[] data=null;
#else
	byte* data=null;
#endif
	int len=0;
	InputUtil iu=null;
	iu=new InputUtil();

	int dsz=64*1024;
	int rsz=64*1024;
	data=new byte[dsz];
	int err=0;
	String fname=null;

	//WebViewEventManager.fireEvent("/postPhoto","start","hoge");
	do{

	str=header.getProperty("content-length");
	if(str==null)break;
	clen=Integer.parseInt(str);
	if(clen<=0)break;
	str=header.getProperty("content-type");
	idx=str.indexOf("multipart/form-data");
	if(idx==-1)break;
	idx=str.indexOf("boundary=");
	if(idx==-1)break;
	tmp=str.substring(idx+9);
	tmp=tmp.trim();
	idx=tmp.indexOf(" ");
	if(idx!=-1){
		tmp=tmp.substring(0,idx);
		tmp=tmp.trim();
	}
	if(tmp.equals(""))break; 
	boundary="--"+tmp;

	while(true){
		if(clen==0)break;
		if(clen<0){
			err=1;
			break;
		}
		//read bound
		println("read bound !!!!");
		println("boundary="+boundary);
		while(true){
			rsz=dsz;
			if(clen<rsz)rsz=clen;
			tmp=iu.readLine(is,data,0,rsz);
			if(tmp==null)break;
			//println("tmp1=>>"+tmp+"<<");
			len=iu.getReadSize();
			if(len<=0)break;
			clen-=len;
			tmp=tmp.trim();
			//println("tmp2=>>"+tmp+"<<");
			if(tmp.indexOf(boundary)!=-1)break;
		}
		if(clen==0)break;
		if(clen<=0 || len<=0 || tmp==null){
			err=1;
			break;
		}
		//read header
		println("read header !!!!");
		fname=null;
		while(true){
			rsz=dsz;
			if(clen<rsz)rsz=clen;
			tmp=iu.readLine(is,data,0,rsz);
			if(tmp==null)break;
			len=iu.getReadSize();
			if(len<=0)break;
			clen-=len;
			tmp=tmp.trim();
			if(tmp.equals(""))break;
	
			idx=tmp.indexOf(":");
			if(idx==-1)continue;
			str=tmp.substring(0,idx);
			str=str.toLowerCase();
			str=str.trim();
			tmp=tmp.substring(idx+1);
			tmp=tmp.trim();
			if(str.equals("content-disposition")){
				do{
					idx=tmp.indexOf("filename=");
					if(idx==-1)break;
					tmp=tmp.substring(idx+9);
					tmp=tmp.trim();
					idx=tmp.indexOf("\"");
					if(idx==-1)break;
					tmp=tmp.substring(idx+1);
					idx=tmp.indexOf("\"");
					if(idx==-1)break;
					tmp=tmp.substring(0,idx);
					if(tmp.equals(""))break;
					idx=tmp.lastIndexOf("\\");
					if(idx!=-1){
						tmp=tmp.substring(idx+1);
					}
					idx=tmp.lastIndexOf("/");
					if(idx!=-1){
						tmp=tmp.substring(idx+1);
					}
					fname=tmp;
					println("OK filename=\""+fname+"\"");
				}while(false);
			}
		}
		if(clen<=0 || len<=0 || tmp==null){
			err=1;
			break;
		}
		
		OutputStream fos=null;
		if(fname!=null){
			//if(fname.length()>30)fname=fname.substring(fname.length()-20);
			//fname=fname.valueOf(CTime.get())+"_"+fname;
			fname=fname.valueOf(CTime.get())+"__.jpg";
			fname=getDefaultDirectory()+"/"+fname;
#ifdef JAVA
			try{
#endif
			fos=new FileOutputStream(fname);
#ifdef JAVA
			}catch(Exception e){}
#endif
		}
		//read body
		println("read body !!!!");
		while(true){
			rsz=dsz;
			if(clen<rsz)rsz=clen;
			len=iu.read(is,data,0,rsz);
			if(len<=0)break;
			idx=BinaryUtil.indexOf(data,0,len,boundary);
			if(idx>=0){
				if(fos!=null){
#ifdef JAVA
					try{
#endif
					fos.write(data,0,idx-2);
#ifdef JAVA
					}catch(Exception e){}
#endif
				}
				iu.unread(data,0,len,len-idx);
				len=idx;
				clen-=len;
				//println("read2="+str.valueOf(len));
				//println("nokori2="+str.valueOf(clen));
				break;
			}
			idx=BinaryUtil.nokori(data,0,len,boundary);
			if(idx>0){
				iu.unread(data,0,len,idx);
				len-=idx;
			}
			if(fos!=null){
#ifdef JAVA
				try{
#endif
				fos.write(data,0,len);
#ifdef JAVA
				}catch(Exception e){}
#endif
			}
			clen-=len;
			//println("read="+str.valueOf(len));
			//println("nokori="+str.valueOf(clen));
		}
		if(fos!=null){
#ifdef JAVA
			try{
#endif
			fos.close();
#ifdef JAVA
			}catch(Exception e){}
#endif
			fos=null;
		}
		if(clen<=0 || len<=0 || tmp==null){
			err=1;
			break;
		}
	}
	//if(err==0)println("OK!!!!!!");
	//else println("NG!!!!!!!!!");
	if(err==1 && fname!=null){
		File fl=null;
#ifdef JAVA
		try{
#endif
		fl=new File(fname);
		fl.deleteFile();
#ifdef JAVA
		}catch(Exception e){}
#endif
	}
	if(err==1)break;

	ret="<html><body>HTML OK<body></html>\r\n";
	//sendHTML(os,ret);

	}while(false);

	//WebViewEventManager.fireEvent("/postPhoto","stop","hoge");

	if(ret!=null){
		sendHTML(os,ret);
	}else{
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
	}
#ifndef JAVA
	if(data)delete[] data;
#endif
	return;
}


#ifdef JAVA
public static void apiJsonp(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::apiJsonp(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String sret=null;
#ifdef JAVA
	try{
#endif
	sret=servJsonp(uri,header,param,session);
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(sret==null || sret.equals("")){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		return;
	}
	sendString(os,sret);
	return;
}


#ifdef JAVA
public static void apiPostJson(OutputStream os,InputStream is,String uri,Properties header,Properties param,Properties session)
#else
void HttpApi::apiPostJson(OutputStream& os,InputStream& is,String& uri,Properties& header,Properties& param,Properties& session)
#endif
{
	String sret=null;
	String tmp=null;

	int len=0;
	tmp=header.getProperty("content-length");
	if(tmp!=null)len=Integer.parseInt(tmp);
	tmp=null;
	if(len>0 && len<1024*64){
#ifdef JAVA
		byte[] b=null;
#else
		byte* b=null;
#endif

#ifdef JAVA
		try{
#endif
		b=new byte[len];
		b[0]=0;
		is.read(b,0,len);
		tmp=new String(b,0,len,"utf-8");

#ifdef JAVA
		}catch(Exception e){}
#endif
#ifndef JAVA
		delete[] b;
#endif
		b=null;

	}
	if(tmp!=null){
		decodeParms( tmp, param );
	}
#ifdef JAVA
	try{
#endif
	sret=servJsonp(uri,header,param,session);
#ifdef JAVA
	}catch(Exception e){}
#endif
	if(sret==null || sret.equals("")){
		String msg=null;
		msg="Bad Request";
		sendError(os, HTTP_BADREQUEST,msg  );
		return;
	}
	sendString(os,sret);
	return;
}



#ifdef JAVA
public static String getMimeString(String ext)
#else
String HttpApi::getMimeString(String& ext)
#endif
{
	String ret=null;

	ret="application/octet-stream";
	if(ext==null){
		return ret;
	}
	if(ext.equals("html")){
		ret="text/html";
	}
	else if(ext.equals("txt")){
		ret="text/plain";
	}
	else if(ext.equals("js")){
		ret="text/javascript";
	}
	else if(ext.equals("css")){
		ret="text/css";
	}
	else if(ext.equals("jpeg") || ext.equals("jpg")){
		ret="image/jpeg";
	}
	else if(ext.equals("png")){
		ret="image/png";
	}
	else if(ext.equals("gif")){
		ret="image/gif";
	}
	return ret;
}

#ifdef JAVA
public static String getDefaultDirectory()
#else
String HttpApi::getDefaultDirectory()
#endif
{
	String ret=null;
	ret=".";
	return ret;
}


#ifdef JAVA
public static String jsonpGetFileList(String uri,Properties header,Properties param)
#else
String HttpApi::jsonpGetFileList(String& uri,Properties& header,Properties& param)
#endif
{
	String ret=null;
	String dir=null;
	File file=null;
	String host=null;
	String base=null;
	String str=null;
	String tmp=null;
	String udir=null;
	String udir2=null;
	int idx;

	ret="[]";

	host=header.getProperty("host");
	if(host==null)return ret;
  
	udir=param.getProperty("dir");
	if(udir!=null){
		if(udir.indexOf("/")==0){
			udir=udir.substring(1);
		}
		idx=udir.lastIndexOf("/");
		if(idx>0 && idx+1==(int)(udir.length())){
			udir=udir.substring(0,idx);
		}
	}
	// ../ ./
	if(udir!=null && udir.indexOf("./")!=-1)return ret;

	base="http://"+host+"/file/";
	if(udir!=null)base+=udir+"/";

	dir=getDefaultDirectory();
	if(dir==null)return ret;
	if(udir!=null)dir+="/"+udir;


	file=new File(dir);
	if(file==null)return ret;


#ifdef JAVA
	String[] sl=null;
	String[] sl2=null;
	byte[] f=null;
	byte[] f2=null;
	longlong[] dt=null;
#else
	String** sl=null;
	String** sl2=null;
	byte* f=null;
	byte* f2=null;
	longlong* dt=null;
#endif
	int i,l=0,l2=0;

	do{
		sl=file.list();
		if(sl==null)l=0;
		else{
			ArrayLength(l,sl);
		}
		if(l==0)break;
		f=new byte[l];
		dt=new longlong[l*2];

		for(i=0;i<l;i++)f[i]=0;

		for(i=0;i<l;i++){
			str=ArrayOf(sl,i);
			//if(str.toLowerCase().indexOf(".jpg")==-1 && str.toLowerCase().indexOf(".jpeg")==-1)continue;
			if(str.indexOf(".")==0)continue;
			l2++;
			f[i]=1;
		}
		if(l2==0)break;;
#ifdef JAVA
		sl2=new String[l2];
		f2=new byte[l2];
#else
		sl2=new String*[l2];
		f2=new byte[l2];
#endif

		int ct=0;

		for(i=0,ct=0;i<l;i++){
			if(f[i]!=0){
				str=ArrayOf(sl,i);
				sl2[ct]=new String(str);
				ct++;
			}
		}
		//for(i=0;i<l2;i++){
		//	println("#####"+ArrayOf(sl2,i));
		//}
		for(i=0;i<l2;i++){
			String fff=null;
			str=ArrayOf(sl2,i);
			fff=dir+"/"+str;
			file=new File(fff);
			dt[i+i]=file.lastModified();
			f2[i]=0;
			if(file.isDirectory())f2[i]=1;
			dt[i+i+1]=(longlong)i;
		}
		MySort.quickSortLargeLong(dt,0,l2-1,2);

		ret="[\r\n";

		udir2="";
		if(udir!=null)udir2=udir+"/";

		for(i=0,ct=0;i<l2;i++){
			idx=0;
			idx=(int)dt[i+i+1];
			str=ArrayOf(sl2,idx);
			tmp="";
			if(ct!=0)tmp+=",\r\n";
			tmp+="{\r\n";
			tmp+=" name:\""+str+"\",\r\n";
			if(f2[idx]==0){
				tmp+=" type:\"file\",\r\n";
			}else{
				tmp+=" type:\"directory\",\r\n";
			}
			if(f2[idx]==0){
				tmp+=" url:\""+base+str+"\",\r\n";
			}else{
				tmp+=" dir:\""+udir2+str+"\",\r\n";
			}
			tmp+="}\r\n";
     
			ct++;
			ret+=tmp;
		}
		//for(i=0;i<l;i++){
		//	str=ArrayOf(sl,i);
		//	if(str.toLowerCase().indexOf(".jpg")==-1 && str.toLowerCase().indexOf(".jpeg")==-1)continue;
		//	if(ct!=0)ret+=",\r\n";
		//	ct++;
		//	tmp="{\r\n";
		//	tmp+=" name:\""+str+"\",\r\n";
		//	tmp+=" url:\""+base+str+"\",\r\n";
		//	tmp+=" surl:\""+base+str+"\" \r\n";
		//	tmp+="}\r\n";
		//	ret+=tmp;
		//}
		ret+="]\r\n";
		//println(ret);
	}while(false);

#ifndef JAVA
	if(dt)delete [] dt;
	if(f)delete [] f;
	if(f2)delete [] f2;
	for(i=0;i<l;i++)delete sl[i];
	if(sl)delete[] sl;
	for(i=0;i<l2;i++)delete sl2[i];
	if(sl2)delete[] sl2;
#endif

	
	
	return ret;
}



#ifdef JAVA
public static void decodeParms( String parms, Properties p )
#else
void HttpApi::decodeParms(String& parms, Properties& p )
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
public static String decodePercent( String str ) 
#else
String HttpApi::decodePercent( String& str )
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



#ifdef JAVA
}
#endif

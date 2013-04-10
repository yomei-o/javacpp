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

#else 

#include "MySort.h"


#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* JAVA*/



#ifdef JAVA 
#define print(a) System.out.println(a)
#define printf System.out.printf
#else
#define print(a) printf("%s\n",(char*)(a))
#endif

#ifdef JAVA 
#else
#define null NULL
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
#define BEGIN_TRY() try{
#define END_TRY() }catch(Exception e){ e.printStackTrace();}
#else
#define BEGIN_TRY()
#define END_TRY()
#endif


#ifdef JAVA
public class MySort{
#endif

#ifdef JAVA
public MySort()
#else
MySort::MySort()
#endif
{
#ifndef JAVA
	isnull=false;
#endif
}

#ifndef JAVA
MySort::MySort(int id)
{
	isnull=true;
}
#endif

#ifndef JAVA
MySort::~MySort()
{
}
#endif


#ifndef JAVA
MySort::MySort(const class MySort& f)
{
	isnull=f.isnull;
}
#endif


#ifndef JAVA
class MySort& MySort::operator =(class MySort *f)
{
	if(f==NULL)goto end;
	isnull=f->isnull;
	delete f;
end:
	return *this;
}
#endif

#ifndef JAVA
class MySort& MySort::operator =(class MySort f)
{
	isnull=f.isnull;
	return *this;
}
#endif


#ifndef JAVA
bool MySort::operator ==(int a)
{
	if(isnull)return true;
	return false;
}
#endif

#ifndef JAVA
bool MySort::operator !=(int a)
{
	if(isnull)return false;
	return true;
}
#endif


#ifdef JAVA
public static int pivotSmallInt(int[] a,int i,int j,int step)
#else
int MySort::pivotSmallInt(int* a,int i,int j,int step)
#endif
{
	int k=i+1;
	while(k<=j && a[i*step]==a[k*step]) k++;
	if(k>j) return -1;
	if(a[i*step]>=a[k*step]) return i;
	return k;
}

#ifdef JAVA
public static int partitionSmallInt(int[] a,int i,int j,int x,int step)
#else
int MySort::partitionSmallInt(int* a,int i,int j,int x,int step)
#endif
{
	int l=i,r=j,s;

    while(l<=r){
		while(l<=j && a[l*step]<x)  l++;
	    while(r>=i && a[r*step]>=x) r--;
		if(l>r) break;
		int t;
		for(s=0;s<step;s++){
			t=a[l*step+s];
			a[l*step+s]=a[r*step+s];
			a[r*step+s]=t;
		}
		l++; r--;
	}
	return l;
}

#ifdef JAVA
public static void quickSortSmallInt(int[] a,int i,int j,int step)
#else
void MySort::quickSortSmallInt(int* a,int i,int j,int step)
#endif
{
	if(i==j) return;
	int p=pivotSmallInt(a,i,j,step);
	if(p!=-1){
		int k=partitionSmallInt(a,i,j,a[p*step],step);
		quickSortSmallInt(a,i,k-1,step);
		quickSortSmallInt(a,k,j,step);
	}
}

#ifdef JAVA
public static int pivotLargeInt(int[] a,int i,int j,int step)
#else
int MySort::pivotLargeInt(int* a,int i,int j,int step)
#endif
{
	int k=i+1;
	while(k<=j && a[i*step]==a[k*step]) k++;
	if(k>j) return -1;
	if(a[i*step]>=a[k*step]) return i;
	return k;
}

#ifdef JAVA
public static int partitionLargeInt(int[] a,int i,int j,int x,int step)
#else
int MySort::partitionLargeInt(int* a,int i,int j,int x,int step)
#endif
{
	int l=i,r=j,s;

    while(l<=r){
		while(l<=j && a[l*step]>=x)  l++;
	    while(r>=i && a[r*step]<x) r--;
		if(l>r) break;
		int t;
		for(s=0;s<step;s++){
			t=a[l*step+s];
			a[l*step+s]=a[r*step+s];
			a[r*step+s]=t;
		}
		l++; r--;
	}
	return l;
}

#ifdef JAVA
public static void quickSortLargeInt(int[] a,int i,int j,int step)
#else
void MySort::quickSortLargeInt(int* a,int i,int j,int step)
#endif
{
	if(i==j) return;
	int p=pivotLargeInt(a,i,j,step);
	if(p!=-1){
		int k=partitionLargeInt(a,i,j,a[p*step],step);
		quickSortLargeInt(a,i,k-1,step);
		quickSortLargeInt(a,k,j,step);
	}
}

#ifdef JAVA
public static int pivotSmallLong(longlong[] a,int i,int j,int step)
#else
int MySort::pivotSmallLong(longlong* a,int i,int j,int step)
#endif
{
	int k=i+1;
	while(k<=j && a[i*step]==a[k*step]) k++;
	if(k>j) return -1;
	if(a[i*step]>=a[k*step]) return i;
	return k;
}

#ifdef JAVA
public static int partitionSmallLong(longlong[] a,int i,int j,longlong x,int step)
#else
int MySort::partitionSmallLong(longlong* a,int i,int j,longlong x,int step)
#endif
{
	int l=i,r=j,s;

    while(l<=r){
		while(l<=j && a[l*step]<x)  l++;
	    while(r>=i && a[r*step]>=x) r--;
		if(l>r) break;
		longlong t;
		for(s=0;s<step;s++){
			t=a[l*step+s];
			a[l*step+s]=a[r*step+s];
			a[r*step+s]=t;
		}
		l++; r--;
	}
	return l;
}

#ifdef JAVA
public static void quickSortSmallLong(longlong[] a,int i,int j,int step)
#else
void MySort::quickSortSmallLong(longlong* a,int i,int j,int step)
#endif
{
	if(i==j) return;
	int p=pivotSmallLong(a,i,j,step);
	if(p!=-1){
		int k=partitionSmallLong(a,i,j,a[p*step],step);
		quickSortSmallLong(a,i,k-1,step);
		quickSortSmallLong(a,k,j,step);
	}
}

#ifdef JAVA
public static int pivotLargeLong(longlong[] a,int i,int j,int step)
#else
int MySort::pivotLargeLong(longlong* a,int i,int j,int step)
#endif
{
	int k=i+1;
	while(k<=j && a[i*step]==a[k*step]) k++;
	if(k>j) return -1;
	if(a[i*step]>=a[k*step]) return i;
	return k;
}

#ifdef JAVA
public static int partitionLargeLong(longlong[] a,int i,int j,longlong x,int step)
#else
int MySort::partitionLargeLong(longlong* a,int i,int j,longlong x,int step)
#endif
{
	int l=i,r=j,s;

    while(l<=r){
		while(l<=j && a[l*step]>=x)  l++;
	    while(r>=i && a[r*step]<x) r--;
		if(l>r) break;
		longlong t;
		for(s=0;s<step;s++){
			t=a[l*step+s];
			a[l*step+s]=a[r*step+s];
			a[r*step+s]=t;
		}
		l++; r--;
	}
	return l;
}

#ifdef JAVA
public static void quickSortLargeLong(longlong[] a,int i,int j,int step)
#else
void MySort::quickSortLargeLong(longlong* a,int i,int j,int step)
#endif
{
	if(i==j) return;
	int p=pivotLargeLong(a,i,j,step);
	if(p!=-1){
		int k=partitionLargeLong(a,i,j,a[p*step],step);
		quickSortLargeLong(a,i,k-1,step);
		quickSortLargeLong(a,k,j,step);
	}
}






#ifdef JAVA
}
#endif

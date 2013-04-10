/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_MySort_H__
#define D_MySort_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


class MySort{
public :
	MySort();
	MySort(int id);
	virtual ~MySort();

	MySort(const MySort& o);

	MySort& operator =(MySort *rhs);
	MySort& operator =(MySort rhs);

	bool operator ==(int);
	bool operator !=(int);

	static int pivotSmallInt(int* a,int i,int j,int step);
	static int partitionSmallInt(int* a,int i,int j,int x,int step);
	static void quickSortSmallInt(int* a,int i,int j,int step);

	static int pivotLargeInt(int* a,int i,int j,int step);
	static int partitionLargeInt(int* a,int i,int j,int x,int step);
	static void quickSortLargeInt(int* a,int i,int j,int step);

	static int pivotSmallLong(longlong* a,int i,int j,int step);
	static int partitionSmallLong(longlong* a,int i,int j,longlong x,int step);
	static void quickSortSmallLong(longlong* a,int i,int j,int step);

	static int pivotLargeLong(longlong* a,int i,int j,int step);
	static int partitionLargeLong(longlong* a,int i,int j,longlong x,int step);
	static void quickSortLargeLong(longlong* a,int i,int j,int step);

public:
	bool isnull;
};

static MySort MySort(0);

#endif /* D_MySort_H__ */





/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"
#include "List.h"
#include "ListCast.h"

#include "mylist.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define print(a) printf("%s\n",a)

#define null 0
#define byte char
#define true 1
#define false 0

List::List()
{
	m=mylist_open();
}

List::List(int id)
{
	m=NULL;
}

List::~List()
{
	if(m)mylist_close((mylist*)m);
	m=NULL;
}

List::List(const List &f)
{
	m=mylist_dup((mylist*)(f.m));
}

List& List::operator =(List *f)
{
	if(f==NULL)goto end;

	m=mylist_dup((mylist*)(f->m));

	delete f;
end:
	return *this;
}
#if 0
List& List::operator =(List &f)
{
	if(m){
		mylist_close((mylist*)m);
		m=NULL;
	}
	m=mylist_dup((mylist*)(f.m));
	return *this;
}
#endif
List& List::operator =(List f)
{
	if(m){
		mylist_close((mylist*)m);
		m=NULL;
	}
	m=mylist_dup((mylist*)(f.m));
	return *this;
}


void	List::add(String& s)
{
	char* p=null;
	if(s.equals(""))return;

	p=s.getBytes();
	mylist_add((mylist*)m,p);
}

void	List::add(char* s)
{
	if(s==NULL)return;
	mylist_add((mylist*)m,s);
}

bool List::operator ==(int a)
{
	if(m==NULL && a==0)return true;
	return false;
}

bool List::operator !=(int a)
{
	if(m==NULL && a==0)return false;
	return true;
}

int	List::size()
{
	if(m==NULL)return 0;
	return mylist_size((mylist*)m);
}

ListCast	List::get(int n)
{
	ListCast ret=null;
	if(m==NULL)return ret;
	if(n<0)return ret;

	if(mylist_size((mylist*)m)<=n)return ret;
	ret=mylist_get((mylist*)m,n);
	return ret;
}




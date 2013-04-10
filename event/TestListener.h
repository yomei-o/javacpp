/******* BEGIN LICENCE BLOCK *******

    Sony Nasne Application
    Copyright (C) 2012 Sony Corporation.
    Yomei.Otani@jp.sony.com

******* END LICENCE BLOCK *******/

#ifndef D_TESTLISTENER_H__
#define D_TESTLISTENER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class TestEvent;

class TestListener{
public :
	TestListener();
	TestListener(int id);
	TestListener(const TestListener& tl);
	virtual ~TestListener();

	virtual void v_const();
	virtual void v_dest();

	TestListener& operator =(TestListener *rhs);
	TestListener& operator =(TestListener &rhs);

	bool operator ==(int);
	bool operator !=(int);

	virtual void onTestEvent(TestEvent& te);

public:
	bool m_null;
	TestListener* tl;
};



#endif /* D_EVENT_H__ */



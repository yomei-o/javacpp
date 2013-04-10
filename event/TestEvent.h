/******* BEGIN LICENCE BLOCK *******

    Sony Nasne Application
    Copyright (C) 2012 Sony Corporation.
    Yomei.Otani@jp.sony.com

******* END LICENCE BLOCK *******/

#ifndef D_TESTEVENT_H__
#define D_TESTEVENT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class TestEvent{
public :
	TestEvent();
	TestEvent(int id);
	virtual ~TestEvent();

	virtual void v_const();
	virtual void v_dest();
	virtual void v_copy(const TestEvent& te);

	TestEvent& operator =(TestEvent *rhs);

	void setID(int id);
	int getID();


	bool operator ==(int);
	bool operator !=(int);

public:
	bool m_null;
	int id;
};



#endif /* D_EVENT_H__ */



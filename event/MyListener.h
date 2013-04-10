
#ifndef D_MYLISTENER_H__
#define D_MYLISTENER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TestListener.h"

class MyListener:public TestListener{
public :
	MyListener();
	MyListener(int id);
	MyListener(const MyListener& tl);
	virtual ~MyListener();

	virtual void v_const();
	virtual void v_dest();

	MyListener& operator =(MyListener *rhs);

	bool operator ==(int);
	bool operator !=(int);

	virtual void onTestEvent(TestEvent& te);



};



#endif /* D_EVENT_H__ */



#ifndef D_INPUTSTREAM_H__
#define D_INPUTSTREAM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



class InputStream{
public :
	InputStream();
	InputStream(int id);
	InputStream(const InputStream & f);
	virtual ~InputStream();

	void reset();
	void close();
	int read(char* p,int offset,int byte);
	int skip(int byte);


	void* (*p_open)(void*);
	void* (*p_dup)(void*);
	void (*p_reset)(void*);
	void (*p_close)(void*);
	int (*p_read)(void*,char*,int ,int);
	int (*p_skip)(void*,int);
	
	
	static void* s_open(void*);
	static void* s_dup(void*);
	static void s_reset(void*);
	static void s_close(void*);
	static int s_read(void*,char*,int ,int);
	static int s_skip(void*,int);
	
	InputStream& operator =(InputStream *rhs);
	//InputStream& operator =(InputStream &rhs);
	InputStream& operator =(InputStream rhs);

	bool operator ==(int id);
	bool operator !=(int id);
public:
	
	void* handle;

};



#endif /* D_INPUTSTREAM_H__ */



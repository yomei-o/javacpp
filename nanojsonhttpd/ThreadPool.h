/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_THREAD_POOL_H_
#define D_THREAD_POOL_H_


class ThreadPool{
public:
	ThreadPool();
	virtual ~ThreadPool();

	static int create(void* func,void* arg);
	static int join(int id);
	static void sleep(int ms);
	static int run(void* arg);
private:
	static void endall();

private:
	static int* m_flag;
	static void** m_list;
	static void** m_arg;
	static void** m_func;
};




#endif /* D_THREAD_POOL_H_ */


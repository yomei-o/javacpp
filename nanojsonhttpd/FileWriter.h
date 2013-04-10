/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_BUFILERWRITER_H__
#define D_BUFILERWRITER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "OutputStreamWriter.h"

class String;
class File;


class FileWriter:public OutputStreamWriter{
public :
	FileWriter(int id);
	FileWriter(const FileWriter & f);
	FileWriter(File & f);
	FileWriter(String & f);
	FileWriter(char* f);
	virtual ~FileWriter();

	
	FileWriter& operator =(FileWriter *rhs);
	FileWriter& operator =(FileWriter &rhs);

public:
};



#endif /* D_BUFILERWRITER_H__ */



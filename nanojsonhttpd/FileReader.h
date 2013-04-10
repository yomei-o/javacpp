/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#ifndef D_FILEREADER_H__
#define D_FILEREADER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "InputStreamReader.h"

class String;
class File;

class FileReader:public InputStreamReader{
public :
	FileReader(int id);
	FileReader(const FileReader & f);
	FileReader(String & str);
	FileReader(File & f);
	FileReader(char* f);
	virtual ~FileReader();

	
	FileReader& operator =(FileReader *rhs);
	FileReader& operator =(FileReader &rhs);

public:
};



#endif /* D_FILEREADER_H__ */



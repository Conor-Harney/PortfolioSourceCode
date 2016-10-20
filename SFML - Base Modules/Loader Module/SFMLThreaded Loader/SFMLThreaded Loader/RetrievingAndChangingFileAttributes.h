#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

class RetrievingAndChangingFileAttributes
{
public:
	RetrievingAndChangingFileAttributes(void);
	~RetrievingAndChangingFileAttributes(void);
	void run(int argc, TCHAR* argv[]);
};


#pragma once

#ifdef _WIN32
	#define SAMPP_DEFAULT_THREAD_PRIORITY THREAD_PRIORITY_NORMAL
#else
	#define SAMPP_DEFAULT_THREAD_PRIORITY 5
	#define MAX_PATH 256
	
	typedef unsigned long DWORD;
	typedef unsigned short WORD;
#endif

struct sStuntDetails
{
	unsigned int dwMoney;
	int iInfo[6];
	unsigned char ucType;
};
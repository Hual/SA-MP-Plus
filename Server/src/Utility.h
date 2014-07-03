#ifndef UTILITY_H
#define UTILITY_H

#define SAFE_FREE(ptr) if(ptr) delete ptr;

#include <string>

typedef void(*logprintf_t)(char* format, ...);

namespace Utility
{
	void Initialize(void** ppData);
	std::string GetApplicationPath(const char* szAppend);
	inline std::string GetApplicationPath(std::string strAppend) { return GetApplicationPath(strAppend.c_str()); };
	void Printf(const char* szFormat, ...);
	void* GetAMXFunctions();
}

#endif


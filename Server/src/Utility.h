#ifndef UTILITY_H
#define UTILITY_H

#include <string>

#define SAFE_FREE(ptr) if(ptr) delete ptr;

typedef void(*logprintf_t)(char* format, ...);

namespace Utility
{
	void Initialize(void **plugin_data);
	void Printf(const char *format, ...);
	void* GetAMXFunctions();
	std::string GetWorkingDir();
}

#endif


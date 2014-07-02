#include <cstdarg>
#include <cstdio>

#include <Platform.h>

#include "Utility.h"
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#ifdef __linux
#include <unistd.h>
#include <limits.h>
#endif

extern void* pAMXFunctions;

namespace Utility
{
	static char* m_szPath;
	static logprintf_t logprintf;
	static std::string working_dir;

	void Initialize(void **plugin_data)
	{		
		#ifdef WIN32
			char raw_path[MAX_PATH];
			GetModuleFileNameA((HINSTANCE)&__ImageBase, raw_path, MAX_PATH);
			
			working_dir = raw_path;
			unsigned dir_end = working_dir.find_last_of("\\plugins") - 12;
			
			working_dir.erase(dir_end);
		#else
			char raw_path[PATH_MAX];
			readlink("/proc/self/exe", raw_path, PATH_MAX);
			
			working_dir = raw_path;
			unsigned filename_start = working_dir.find_last_of("/");
			
			working_dir.erase(filename_start);
			working_dir += "/";
		#endif
			
		pAMXFunctions = plugin_data[PLUGIN_DATA_AMX_EXPORTS];
		logprintf = (logprintf_t)plugin_data[PLUGIN_DATA_LOGPRINTF];
	}
	
	void Printf(const char *format, ...)
	{
		char buffer[2048];
				
		std::va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

		logprintf("[SA-MP+] %s", buffer);
	}

	void* GetAMXFunctions()
	{
		return pAMXFunctions;
	}
	
	std::string GetWorkingDir()
	{
		return working_dir;
	}
}

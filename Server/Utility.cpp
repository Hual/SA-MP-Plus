#include <SAMP+/Utility.h>
#include <SAMP+/Platform.h>

#include <ctime>
#include <stdarg.h>

#ifdef LINUX
	#include <unistd.h>
#endif

extern void* pAMXFunctions;

namespace Utility
{
	static char m_szPath[MAX_PATH + 1];
	static logprintf_t logprintf;

	void Initialize(void** ppData)
	{
#ifdef _WIN32
		GetModuleFileNameA(NULL, m_szPath, sizeof(m_szPath));
#else
		readlink("/proc/self/exe", m_szPath, sizeof(m_szPath));
#endif
		pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
		logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	}

	std::string GetApplicationPath(const char* szAppend)
	{
		std::string strPath(m_szPath);

#ifdef _WIN32
		std::string::size_type ptr = strPath.find_last_of("\\");
#else
		std::string::size_type ptr = strPath.find_last_of("/");
#endif

		if(ptr)
		{
			strPath.erase(ptr+1, strPath.length()-ptr-1);
		}
		
		if (szAppend)
			strPath += szAppend;

		return strPath;
	}

	void Printf(const char* szFormat, ...)
	{
		va_list vaArgs;
		char szBuffer[2048];
		va_start(vaArgs, szFormat);
		vsnprintf(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
		va_end(vaArgs);

		return logprintf("[SA-MP+] %s", szBuffer);
	}

	void* GetAMXFunctions()
	{
		return pAMXFunctions;
	}
}
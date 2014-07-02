#include <cstdarg>

#include <Platform.h>

#include "Utility.h"
#include "RakNet/SuperFastHash.h"
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#ifdef __linux
#include <unistd.h>
#endif

extern void* pAMXFunctions;

namespace Utility
{
	static char* m_szPath;
	static logprintf_t logprintf;

	void Initialize(void** ppData)
	{
#ifdef WIN32
		m_szPath = new char[MAX_PATH + 1];
		GetModuleFileNameA((HINSTANCE)&__ImageBase, m_szPath, MAX_PATH + 1);
#else
		m_szPath = new char[4096 + 1];
		readlink("/proc/self/exe", m_szPath, sizeof(m_szPath));
#endif
		pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
		logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	}

	std::string GetApplicationPath(const char* szAppend)
	{
		/*std::string strPath(m_szPath);

		std::string::size_type ptr = strPath.find_last_of("\\");

		if (ptr)
			strPath.erase(ptr-7);
		else
			strPath.erase(strPath.find_last_of("/plugins")-7);

		if (szAppend)
			strPath += szAppend;*/
		std::string strPath = "TEST";

		return strPath;
	}

	void Printf(const char* szFormat, ...)
	{
		va_list vaArgs;
		char szBuffer[2048];
		va_start(vaArgs, szFormat);
		vsnprintf(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
		va_end(vaArgs);

		logprintf("[SA-MP+] %s", szBuffer);
	}

	void* GetAMXFunctions()
	{
		return pAMXFunctions;
	}
}

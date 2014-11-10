#include <SAMP+/client/CLog.h>
#include <stdarg.h>

std::ofstream CLog::m_pOfstream;

void CLog::Initialize()
{
	m_pOfstream.open("log.txt", std::ofstream::out | std::ofstream::trunc);
	Write("Logging initiated");
}

void CLog::Finalize()
{
	m_pOfstream.close();
}

void CLog::Write(const char* szFormat, ...)
{
	char szBuffer[2048];
	va_list vaArgs;
	va_start(vaArgs, szFormat);
	vsnprintf(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
	va_end(vaArgs);

	size_t uiLength = strlen(szBuffer);
	szBuffer[uiLength++] = '\n';

	m_pOfstream.write(szBuffer, uiLength);
	m_pOfstream.flush();
}
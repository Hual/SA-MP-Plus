#include <SAMP+/client/CLog.h>
#include <stdarg.h>

std::ofstream CLog::m_pOfstream;

int CLog::bytesSent;
int CLog::bytesReceived;

void CLog::Initialize()
{
	m_pOfstream.open("log.txt", std::ofstream::out | std::ofstream::trunc);
	Write("Logging initiated");
}

void CLog::Finalize()
{
	Write("Session ended\n\nTotal Bytes sent %d, received: %d", bytesSent, bytesReceived);

	m_pOfstream.close();
}

void CLog::Write(const char* szFormat, ...)
{

	time_t now = time(0);
	tm * ltm = localtime(&now);

	char szBuff[22];

	sprintf(szBuff, "[%d/%d/%d %d:%d:%d] ", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, ltm->tm_hour + 1, ltm->tm_min + 1, ltm->tm_sec + 1);

	std::string time = szBuff;

	char szBuffer[2048];

	va_list vaArgs;
	va_start(vaArgs, szFormat);

	vsnprintf(szBuffer, sizeof(szBuffer), szFormat, vaArgs);

	va_end(vaArgs);

	std::string buffer = szBuffer;

	buffer.insert(0, szBuff);
	buffer.append("\n");

	m_pOfstream.write(buffer.c_str(), buffer.size());
	m_pOfstream.flush();

}
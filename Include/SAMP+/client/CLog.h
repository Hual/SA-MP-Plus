#pragma once

#include <fstream>
#include <ctime>

class CLog
{
public:
	static void Initialize();
	static void Finalize();

	static void Write(const char* szFormat, ...);

	static int bytesSent;
	static int bytesReceived;

private:
	static std::ofstream m_pOfstream;
	

};
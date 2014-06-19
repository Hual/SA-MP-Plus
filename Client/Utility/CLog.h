#pragma once

#include <fstream>

class CLog
{
public:
	static void Initialize();
	static void Finalize();

	static void Write(const char* szFormat, ...);

private:
	static std::ofstream m_pOfstream;

};
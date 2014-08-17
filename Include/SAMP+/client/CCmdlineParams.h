#pragma once

#include <map>
#include <string>

#define SAMP_PARAM_DEBUG "d"
#define SAMP_PARAM_CONNECT "c"
#define SAMP_PARAM_UNAME "n"
#define SAMP_PARAM_ADDRESS "h"
#define SAMP_PARAM_PORT "p"
#define SAMP_PARAM_PASS "z"

class CCmdlineParams
{
public:
	static UINT Process(const char* pChar);
	static size_t GetArgumentCount();
	static bool ArgumentExists(std::string strKey);
	static bool ArgumentHasValue(std::string strKey);
	static std::string& GetArgumentValue(std::string strKey);
	static std::map<std::string, std::string>& GetParamsMap();

private:
	static void ProcessSubstr(std::string strSubstr);

	static std::map<std::string, std::string> m_paramMap;
};
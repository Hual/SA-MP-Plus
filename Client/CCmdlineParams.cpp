#include <SAMP+/client/Client.h>
#include <SAMP+/client/CCmdlineParams.h>

std::map<std::string, std::string> CCmdlineParams::m_paramMap;

UINT CCmdlineParams::Process(const char* pChar)
{
	m_paramMap.clear();

	size_t pos = 0;
	std::string str(pChar), substr;

	while ((pos = str.find(" -")) != std::string::npos)
	{
		substr = str.substr(0, pos);
		ProcessSubstr(substr);
		str.erase(0, pos+2);
	}

	substr = str.substr(pos+1);
	ProcessSubstr(substr);
	return m_paramMap.size();
}

void CCmdlineParams::ProcessSubstr(std::string strSubstr)
{
	std::pair<std::string, std::string> pair;
	size_t pos = strSubstr.find(' ');
	if(pos != std::string::npos)
		pair = std::pair<std::string, std::string>(strSubstr.substr(0, pos), strSubstr.substr(pos + 1));
	else
		pair = std::pair<std::string, std::string>(strSubstr, "");

	m_paramMap.insert(pair);
}

size_t CCmdlineParams::GetArgumentCount()
{
	return m_paramMap.size();
}

bool CCmdlineParams::ArgumentExists(std::string strKey)
{
	return m_paramMap.count(strKey) > 0;
}

bool CCmdlineParams::ArgumentHasValue(std::string strKey)
{
	return m_paramMap.find(strKey)->second.length() > 0;
}

std::string& CCmdlineParams::GetArgumentValue(std::string strKey)
{
	return m_paramMap.find(strKey)->second;
}

std::map<std::string, std::string>& CCmdlineParams::GetParamsMap()
{
	return m_paramMap;
}
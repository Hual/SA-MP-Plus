#include <fstream>

#include <SAMP+/Utility.h>
#include <SAMP+/svr/CServerConfig.h>

CServerConfig::CServerConfig(const char* szFileName)
{
	m_szFileName = szFileName;

	Reparse();
}

CServerConfig::~CServerConfig()
{

}

void CServerConfig::Reparse()
{
	m_settings.clear();

	std::ifstream isConfigFile(Utility::GetApplicationPath(m_szFileName));
	std::string strLine;

	while (std::getline(isConfigFile, strLine))
	{
		std::string strKey, strValue;
		std::string::size_type iDelimiter = strLine.find_first_of(' ');

		if (iDelimiter != std::string::npos)
		{
			strKey = strLine.substr(0, iDelimiter);
			strValue = strLine.substr(iDelimiter + 1);
		}
		else
		{
			strKey = strLine;
			strValue = "";
		}

		m_settings[strKey] = strValue;
	}
}

std::string& CServerConfig::GetSetting(const std::string strKey)
{
	return m_settings.find(strKey)->second;
}
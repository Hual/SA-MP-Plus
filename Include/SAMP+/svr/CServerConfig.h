#pragma once

#include <map>
#include <string>

class CServerConfig
{
public:
	CServerConfig(const char* szFileName);
	virtual ~CServerConfig();

	void Reparse();
	std::string& GetSetting(const std::string strKey);
	inline std::map<std::string, std::string> GetSettings() { return m_settings; };
	inline bool HasSetting(std::string strKey) { return !!m_settings.count(strKey); };
	
private:

	std::map<std::string, std::string> m_settings;
	const char* m_szFileName;

};
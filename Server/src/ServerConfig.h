#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <map>

class ServerConfig
{
public:
	ServerConfig(const char* szFileName);
	virtual ~ServerConfig();

	void Parse();
	
	int GetInt(const std::string key);
	std::string GetString(const std::string key);
	
	inline std::map<std::string, std::string> GetSettings() { return settings; };

private:
	std::string config_path;
	std::map<std::string, std::string> settings;

};

#endif

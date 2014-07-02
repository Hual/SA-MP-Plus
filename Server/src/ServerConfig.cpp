#include <fstream>

#include "ServerConfig.h"
#include "Utility.h"

ServerConfig::ServerConfig(const char* config_path)
{
	this->config_path = Utility::GetWorkingDir() + config_path;
	this->Parse();
}

ServerConfig::~ServerConfig()
{

}

void ServerConfig::Parse()
{
	settings.clear();

	std::ifstream config_file(this->config_path);
	std::string line;
	
	while(std::getline(config_file, line))
	{
		std::string key, value;
		std::string::size_type delimiter = line.find_first_of(' ');

		if (delimiter != std::string::npos)
		{
			key = line.substr(0, delimiter);
			value = line.substr(delimiter + 1);
		}
		else
		{
			key = line;
			value = "";
		}

		settings[key] = value;
	}
}

int ServerConfig::GetInt(const std::string key)
{
	std::map<std::string, std::string>::iterator pos = settings.find(key);
	
	if(pos != settings.end())
		return atoi(pos->second.c_str());
	else
		return 0;
}

std::string ServerConfig::GetString(const std::string key)
{
	std::string value("");
	std::map<std::string, std::string>::iterator pos = settings.find(key);
	
	if(pos != settings.end())
		value = pos->second;
		
	return value;
}


#pragma once

#include <string>

class CSystem
{
public:
	static bool CSystem::GetLoadedModules();
	static bool CSystem::GetLoadedModules(std::string *output, char separator);
};
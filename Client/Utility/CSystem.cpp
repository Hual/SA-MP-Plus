#include "CSystem.h"
#include <stdafx.h>
#include <Windows.h>
#include <TlHelp32.h>

// TODO
std::string CSystem::GetLoadedModules()
{
	std::string strOut;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	MODULEENTRY32 me;
	me.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hSnapshot, &me))
		ExitProcess(1);

	do
	{
		//CLog::Write("name: %s", me.szModule);
	} while (Module32Next(hSnapshot, &me));

	CloseHandle(hSnapshot);

}
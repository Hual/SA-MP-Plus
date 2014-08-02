#include <SAMP+/client/Client.h>
#include <SAMP+/client/CSystem.h>
#include <Windows.h>
#include <TlHelp32.h>

bool CSystem::GetLoadedModules()
{
	HANDLE snaphot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	if(snaphot_handle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 mod_entry;
		mod_entry.dwSize = sizeof(mod_entry);
		if(Module32First(snaphot_handle, &mod_entry))
		{
			CLog::Write("[module] List of loaded modules:");

			do
			{
				CLog::Write("[module] 0x%p : %ls", mod_entry.modBaseAddr, mod_entry.szModule);
			} 
			while(Module32Next(snaphot_handle, &mod_entry));
		}
		else
		{
			CloseHandle(snaphot_handle);
			return false;
		}

		CloseHandle(snaphot_handle);
		return true;
	}
	return false;
}

bool CSystem::GetLoadedModules(std::string *output, char separator)
{
	HANDLE snaphot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	if(snaphot_handle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 mod_entry;
		mod_entry.dwSize = sizeof(mod_entry);
		if(Module32First(snaphot_handle, &mod_entry))
		{
			output -> clear();

			do
			{
				output -> append(mod_entry.szModule);
				output -> push_back(separator);
			} 
			while(Module32Next(snaphot_handle, &mod_entry));
		}
		else
		{
			CloseHandle(snaphot_handle);
			return false;
		}

		output -> pop_back();

		CloseHandle(snaphot_handle);
		return true;
	}
	return false;
}

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

HANDLE start_samp(const bool bDebug, const char *pcUsername, const char *pcAddress, const char *pcPort, const char *pcPassword = NULL);
VOID inject_using_thread(char *pcDllName, HANDLE hProcess);

int main()
{
	HANDLE process = start_samp(false, "King_Hual", "127.0.0.1", "7777");
	return !process;
}

HANDLE start_samp(const bool bDebug, const char *pcUsername, const char *pcAddress, const char *pcPort, const char *pcPassword)
{
	char exe_path[MAX_PATH], cmd_args[MAX_PATH+64] = { '"', 0 };
	GetFullPathName("gta_sa.exe", MAX_PATH, exe_path, NULL);
	if (!bDebug)
	{
		sprintf_s(cmd_args, "\"%s\" -c -n %s -h %s -p %s", exe_path, pcUsername, pcAddress, pcPort);
		if (pcPassword)
		{
			strcat_s(cmd_args, " -z ");
			strcat_s(cmd_args, pcPassword);
		}
	}
	else
		sprintf_s(cmd_args, "\"%s\" -d", exe_path);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	CreateProcess(exe_path, cmd_args, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	inject_using_thread("sampp.dll", pi.hProcess);
	inject_using_thread("samp.dll", pi.hProcess);
	ResumeThread(pi.hThread);
	return pi.hProcess;
}

VOID inject_using_thread(char *pcDllName, HANDLE hProcess)
{
	char dll_path[MAX_PATH];

	LPVOID load_lib_addr, remote_addrspace;
	GetFullPathName(pcDllName, MAX_PATH, dll_path, NULL);
	load_lib_addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	remote_addrspace = (LPVOID)VirtualAllocEx(hProcess, NULL, strlen(dll_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, (LPVOID)remote_addrspace, dll_path, strlen(dll_path), NULL);
	HANDLE thread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)load_lib_addr, remote_addrspace, 0, NULL);

	if (thread)
	{
		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);
	}
	VirtualFreeEx(hProcess, remote_addrspace, sizeof(remote_addrspace), MEM_RELEASE);
}
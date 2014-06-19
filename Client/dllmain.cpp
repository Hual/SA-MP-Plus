#include <stdafx.h>
#include "Game/CCmdlineParams.h"
#include "Game/Hooks/CHooks.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		CLog::Initialize();
		CCmdlineParams::Process(GetCommandLineA());
		CHooks::Apply();
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		CHooks::Remove();
		CLog::Finalize();
		break;
	}
	}
	return TRUE;
}

#include <SAMP+/client/Client.h>
#include <SAMP+/client/CCmdlineParams.h>
#include <SAMP+/client/CHooks.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (GetModuleHandle("samp.dll"))
	{
		switch (dwReason)
		{
		case DLL_PROCESS_ATTACH:
			CLog::Initialize();
			CCmdlineParams::Process(GetCommandLineA());
			CHooks::Apply();
			break;

		case DLL_PROCESS_DETACH:
			CHooks::Remove();
			CLog::Finalize();
			break;

		}
	}
	return TRUE;
}

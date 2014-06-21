#include "CMem.h"
#include <stdafx.h>

DWORD CMem::m_dwUnprotectDummy;

void CMem::ApplyJmp(BYTE* pAddress, DWORD dwProxy, DWORD dwLen)
{
	DWORD dwOld, dwRelAddr;
	Unprotect(pAddress, dwLen, &dwOld);
	dwRelAddr = (DWORD)(dwProxy - (DWORD)pAddress) - 5;

	*pAddress = ASM_JMP;
	PutSingle<DWORD>(pAddress + 1, dwRelAddr);

	for (unsigned long i = 5; i < dwLen; ++i)
		PutSingle<BYTE>(pAddress + i, ASM_NOP);

	VirtualProtect((void*)pAddress, dwLen, dwOld, &m_dwUnprotectDummy);
}

#include <SAMP+/client/Client.h>
#include <SAMP+/client/CMem.h>

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


void CMem::Cpy(void* address, const void* src, int size)
{
	CMem::Unprotect(address, size);
	memcpy(address, src, size);
	VirtualProtect(address, size, m_dwUnprotectDummy, NULL);
}
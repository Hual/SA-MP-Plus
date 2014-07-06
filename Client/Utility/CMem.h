#pragma once

#include <Windows.h>

#define ASM_JMP 0xE9
#define ASM_NOP 0x90

class CMem
{
public:
	template<class T, class U> static void PutSingle(U pMemory, T value);
	template<class T, class U, class V> static void Put(U pMemory, V pValue, unsigned long uiLen);
	template<class T, class U> static T Get(U pMemory);
	template <class T> static BOOL Unprotect(T lpMemory, SIZE_T dwSize, DWORD* pOut = NULL);
	template <class T> static void Set(T lpMemory, unsigned char ucByte, size_t uiSize);
	template <class T, class U> static void InstallJmp(T address, U proxy, DWORD& jumpback, DWORD dwLen, DWORD jumpbackPos = NULL);
	template <class T, class U> static void InstallJmp(T address, U proxy, DWORD dwLen = 5);

	static void ApplyJmp(BYTE* pAddress, DWORD dwProxy, DWORD dwLen);

private:
	static DWORD m_dwUnprotectDummy;

};

template <class T, class U>
void CMem::InstallJmp(T address, U proxy, DWORD& jumpback, DWORD dwLen, DWORD jumpbackPos)
{
	if (!jumpbackPos)
		jumpbackPos = dwLen;

	jumpback = (DWORD)address + jumpbackPos;
	ApplyJmp((BYTE*)address, (DWORD)proxy, dwLen);
}

template <class T, class U>
static void CMem::InstallJmp(T address, U proxy, DWORD dwLen)
{
	return ApplyJmp((BYTE*)address, (DWORD)proxy, dwLen);
}

template<class T, class U>
void CMem::PutSingle(U pMemory, T value)
{
	*(T*)pMemory = value;
}

template<class T, class U, class V>
void CMem::Put(U pMemory, V pValue, unsigned long uiLen)
{
	for (size_t i = 0; i < uiLen; ++i)
		PutSingle<T, T*>((T*)(pMemory) + i, *((T*)(pValue) + i));

}

template<class T, class U>
T CMem::Get(U pMemory)
{
	return *(T*)pMemory;
}

template <class T>
BOOL CMem::Unprotect(T lpMemory, SIZE_T dwSize, DWORD* pOut)
{
	return VirtualProtect((void*)lpMemory, dwSize, PAGE_EXECUTE_READWRITE, pOut ? pOut : &m_dwUnprotectDummy);
}

template <class T>
void CMem::Set(T lpMemory, unsigned char ucByte, size_t uiSize)
{
	memset((void*)lpMemory, ucByte, uiSize);
}

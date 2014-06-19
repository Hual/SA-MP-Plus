#pragma once

#include <Windows.h>

class CMem
{
public:
	template<class T, class U> static void PutSingle(U pMemory, T value);
	template<class T, class U, class V> static void Put(U pMemory, V pValue, unsigned long uiLen);
	template<class T, class U> static T Get(U pMemory);
	template <class T> static BOOL Unprotect(T lpMemory, size_t uiSize, DWORD* pOut = NULL);
	template <class T> static void Set(T lpMemory, unsigned char ucByte, size_t uiSize);

private:
	static DWORD m_dwUnprotectDummy;

};

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
BOOL CMem::Unprotect(T lpMemory, size_t uiSize, DWORD* pOut)
{
	return VirtualProtect((void*)lpMemory, uiSize, PAGE_READWRITE, pOut ? pOut : &m_dwUnprotectDummy);
}

template <class T>
void CMem::Set(T lpMemory, unsigned char ucByte, size_t uiSize)
{
	memset((void*)lpMemory, ucByte, uiSize);
}

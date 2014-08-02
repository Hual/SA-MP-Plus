#include <SAMP+/client/CHUD.h>
#include <SAMP+/client/CMem.h>
#include <SAMP+/client/Proxy/CJmpProxy.h>

sHUDComponent CHUD::components[] =
{
	{ 0x005893B0, { 0xC3, 0x53, 0x01 } },
	{ 0x0058D7D0, { 0xC3, 0xA1, 0x01 } },
	{ 0x00589270, { 0xC3, 0x83, 0x01 } },
	{ 0x00589190, { 0xC3, 0x83, 0x01 } },
	{ 0x005890A0, { 0xC3, 0x83, 0x01 } },
	{ 0x0058A330, { 0xC3, 0xA1, 0x01 } },
	{ 0x0058E020, { 0xC3, 0x83, 0x01 } },
	{ 0x0058F47D, { 0xE990, 0x840F, 0x02 } },
};

DWORD* CHUD::colourComponents = CJmpProxy::HUDColourList;

void CHUD::Initialize()
{
	for (unsigned char i = 0; i < sizeof(components) / sizeof(sHUDComponent); ++i)
		for (unsigned char j = 0; j < components[i].ulOpcodes[2]; ++j)
			CMem::Unprotect((void*)(components[i].ulFunc + j), components[i].ulOpcodes[2]);

}

void CHUD::ToggleComponent(unsigned char ucComponent, bool bToggle)
{
	size_t uiComponentsSize = sizeof(components) / sizeof(sHUDComponent);

	if (ucComponent > uiComponentsSize)
		return;

	if (ucComponent == eHUDComponent::ALL)
	{
		for (unsigned char i = 1; i < uiComponentsSize+1; ++i)
			ToggleComponent(i, bToggle);

	}
	else
	{
		ucComponent -= 1;
		unsigned long* pComponentOpcodes = components[ucComponent].ulOpcodes;
		CMem::Put<unsigned char>(components[ucComponent].ulFunc, &pComponentOpcodes[bToggle], pComponentOpcodes[2]);
	}
}

bool CHUD::IsComponentToggled(unsigned char ucComponent)
{
	size_t uiComponentsSize = sizeof(components) / sizeof(sHUDComponent);

	if (ucComponent > uiComponentsSize || ucComponent == eHUDComponent::ALL)
		return false;

	ucComponent -= 1;
	unsigned long* pComponentOpcodes = components[ucComponent].ulOpcodes;

	for (unsigned char i = 0; i < pComponentOpcodes[2]; ++i)
		if (CMem::Get<unsigned char>(components[ucComponent].ulFunc + i) != CMem::Get<unsigned char>(((unsigned char*)&pComponentOpcodes[1]) + i))
			return false;

	return true;
}

void CHUD::SetComponentColour(unsigned char ucColourComponent, DWORD dwColour)
{
	if (ucColourComponent >= eHUDColourComponent::COUNT)
		return;

	colourComponents[ucColourComponent] = dwColour;
}
#pragma once

#include <SAMP+/client/Client.h>

enum eHUDComponent : unsigned char
{
	ALL,
	AMMO,
	WEAPON,
	HEALTH,
	BREATH,
	ARMOUR,
	MINIMAP,
	CROSSHAIR,
	MONEY
};

enum eHUDColourComponent : unsigned char
{
	MONEY_POSITIVE,
	MONEY_NEGATIVE,
	ARMOUR_BAR,
	HEALTH_BAR,
	BREATH_BAR,
	AMMO_TEXT,
	WANTED_LEVEL,
	COUNT
};

#pragma pack(push, 1)
struct sHUDComponent
{
	unsigned long ulFunc;
	unsigned long ulOpcodes[3];
};
#pragma pack(pop)

class CHUD
{
public:
	static void Initialize();
	static void ToggleComponent(unsigned char ucComponent, bool bToggle);
	static bool IsComponentToggled(unsigned char ucComponent);
	static void SetComponentColour(unsigned char ucColourComponent, DWORD dwColour);

private:
	static sHUDComponent components[];
	static DWORD* colourComponents;

};
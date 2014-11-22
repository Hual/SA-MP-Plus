#pragma once

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>
#include <SAMP+/client/CLog.h>

#include "resource.h"

#include <string>
class Sprite
{
	public:
		Sprite();
		Sprite(int x, int y);
		~Sprite();

		bool Init(LPDIRECT3DDEVICE9 device, int width, int height);
		bool isInitialized();

		void Draw();
		void Resize(int width, int height);
		void Move(int x, int y);
		void Rotate(float angle);

		void Reset();
		void OnLostDevice();
		void OnResetDevice();

private:
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	D3DCOLOR color;
	bool initialized;

	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;

	LPDIRECT3DDEVICE9 m_device;

	D3DXMATRIX mat;

	D3DXVECTOR2 center;

	float rotation;

	void SetTransformation();
};


#pragma once

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>
#include <SAMP+/client/CLog.h>

#include <string>
class Sprite
{
	public:
		Sprite();
		Sprite(float x, float y);
		~Sprite();

		bool Init(LPDIRECT3DDEVICE9 device, std::string filename, float width, float height);
		bool Init(LPDIRECT3DDEVICE9 device, wint_t resource, float width, float height);
		bool begin(LPDIRECT3DDEVICE9 device);
		bool isInitialized();

		void Draw();
		void Resize(float width, float height);
		void Move(float x, float y);
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


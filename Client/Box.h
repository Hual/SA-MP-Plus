#pragma once

#define D3D_DEBUG_INFO

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>
#include <SAMP+/client/CLog.h>

#include "resource.h"

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Box
{
public:
	Box();
	~Box();

	bool Init(IDirect3DDevice9* pDevice, float width, float height, float x, float y, D3DCOLOR color);
	bool isInitialized();

	void OnLostDevice();
	void OnResetDevice();

	void Draw();
	void Show();
	void Hide();


private:
	bool m_bDraw;
	bool initialized;

	IDirect3DVertexBuffer9* v_buffer;
	IDirect3DDevice9* m_pDevice;

	static struct VertexData
	{
		D3DXVECTOR3 Pos;
		float RHW;
		D3DCOLOR Color;
		D3DXVECTOR2 UV;
	};

	D3DRECT m_BarRect;
	RECT m_Rect;

	float m_fX;
	float m_fY;

	float m_fWidth;
	float m_fHeight;

	D3DCOLOR m_cColor;

	//Gaussian blur shader
	ID3DXEffect* m_pShader;
	IDirect3DVertexDeclaration9* m_pDeclaration;
	IDirect3DIndexBuffer9* m_pIndexBuffer;

	//Matrices
	D3DXMATRIX m_World;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;

	LPDIRECT3DTEXTURE9 m_pTexture;

	//IDirect3DTexture9* m_pTexture;
	//IDirect3DSurface9* m_pDest;
	//IDirect3DSurface9* m_pBackBufferSurface;
	//LPD3DXRENDERTOSURFACE m_pRenderToSurface;
};


#include "CSprite.h"

Sprite::Sprite()
{
	pos.x = 0;
	pos.y = 0;

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	initialized = false;

}

Sprite::Sprite(float x, float y)
{
	CLog::Write("Sprite::Sprite");
	pos.x = x;
	pos.y = y;

	scale = D3DXVECTOR2();

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	initialized = false;
}

Sprite::~Sprite()
{
	CLog::Write("Sprite::~Sprite");
	if (sprite)
	{
		sprite->Release();
		sprite = NULL;
		CLog::Write("Sprite::~Sprite1");
	}

	if (tex)
	{
		CLog::Write("Sprite::~Sprite2");
		tex->Release();
		tex = NULL;
	}

	CLog::Write("Sprite::~Sprite3");
	initialized = false;

}

bool Sprite::Init(LPDIRECT3DDEVICE9 device, std::string filename, int width, int height)
{
	m_device = device;

	center = D3DXVECTOR2(width / 2, height / 2);
	scale = D3DXVECTOR2(width, height);

	if (FAILED(D3DXCreateTextureFromFileEx(device, filename.c_str(), width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))
		return false;

	if (FAILED(D3DXCreateSprite(device, &sprite)))
		return false;

	SetTransformation();

	initialized = true;

	return true;
}

bool Sprite::Init(LPDIRECT3DDEVICE9 device, wint_t resource, int width, int height)
{
	m_device = device;

	center = D3DXVECTOR2(width / 2, height / 2);
	scale = D3DXVECTOR2(width, height);


	if (HRESULT hr = (D3DXCreateTextureFromResourceEx(device, GetModuleHandle("sampp_client.asi"), MAKEINTRESOURCE(resource), width, height, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex) != S_OK))
	{
		CLog::Write("Sprite::Init FAILED: %d", hr);
		return false;
	}

	if (FAILED(D3DXCreateSprite(device, &sprite)))
		return false;

	SetTransformation();

	initialized = true;

	return true;
}

bool Sprite::isInitialized()
{
	return initialized;
}

void Sprite::Draw()
{
	if (sprite && tex)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		//m_device->Clear(0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 0, 0);

		//m_device->SetRenderState(D3DRS_ZWRITEENABLE, false);

		//SetTransformation();

		//sprite->SetTransform(&mat);

		sprite->Draw(tex, NULL, NULL, &D3DXVECTOR3(pos.x, pos.y, 0), color);

		sprite->End();
	}
}

void Sprite::Reset()
{
	CLog::Write("Sprite::Reset");
	HRESULT r = m_device->TestCooperativeLevel();

	if (r == D3DERR_DEVICELOST)
		OnLostDevice();

	else if (r == D3DERR_DEVICENOTRESET)
		OnResetDevice();
}

void Sprite::OnLostDevice()
{
	CLog::Write("Sprite::OnLostDevice");
	sprite->OnLostDevice();
}

void Sprite::OnResetDevice()
{
	CLog::Write("Sprite::OnResetDevice");
	sprite->OnResetDevice();
}

void Sprite::Resize(int width, int height)
{
	scale = D3DXVECTOR2(width, height);
}

void Sprite::Move(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Sprite::Rotate(float angle)
{
	rotation = angle;
}

void Sprite::SetTransformation()
{
	D3DXVECTOR2 spriteCenter = center;

	D3DXVECTOR2 trans = pos;

	D3DXVECTOR2 scaling = scale;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCenter, rotation, &trans);
}
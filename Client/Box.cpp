#include "Box.h"


Box::Box()
{
	CLog::Write("Box::Box");
	initialized = false;
	m_bDraw = false;

	//Initialize pointers
	v_buffer = nullptr;
	m_pDevice = nullptr;
	//m_pTexture = nullptr;
	//m_pDest = nullptr;
	//m_pBackBufferSurface = nullptr;
	//m_pRenderToSurface = nullptr;
	m_pShader = nullptr;
	m_pDeclaration = nullptr;
	m_pIndexBuffer = nullptr;
	m_pTexture = nullptr;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&m_View);
	D3DXMatrixIdentity(&m_Proj);
}


bool Box::Init(IDirect3DDevice9* pDevice, float width, float height, float x, float y, D3DCOLOR color)
{

	/*VertexData vertex [] =
	{
		//X			Y		  Z		RHW   Color
		{ D3DXVECTOR3(x, y, 0), 1.0, color },
		{ D3DXVECTOR3(x + width, y, 0), 1.0, color },
		{ D3DXVECTOR3(x, y + height, 0), 1.0, color },
		{ D3DXVECTOR3(x + width, y + height, 0), 1.0, color }
	};*/
	
	VertexData vertex[] =
	{
		//X			Y		  Z		RHW   Color
		{ D3DXVECTOR3(x, y, 0), 1.0, color, D3DXVECTOR2(0.0, 0.0) },
		{ D3DXVECTOR3(x + width, y, 0), 1.0, color, D3DXVECTOR2(1.0, 0.0) },
		{ D3DXVECTOR3(x, y + height, 0), 1.0, color, D3DXVECTOR2(0.0, 1.0) },
		{ D3DXVECTOR3(x + width, y + height, 0), 1.0, color, D3DXVECTOR2(1.0, 1.0) }
	};

	/*VertexData vertex[] =
	{
	//X			Y		  Z		RHW   Color
	{ D3DXVECTOR3(x, y, 1), color },
	{ D3DXVECTOR3(x + width, y, 1), color },
	{ D3DXVECTOR3(x, y + height, 1), color },
	{ D3DXVECTOR3(x + width, y + height, 1), color }
	};*/

	VOID* pVoid = nullptr;

	//Set up the vertex buffer

	unsigned long vertexSize = 4 * sizeof(VertexData);

	if (FAILED(pDevice->CreateVertexBuffer(vertexSize, 0, CUSTOMFVF, D3DPOOL_MANAGED, &v_buffer, NULL)))
	{
		CLog::Write("Box::Init - Couldn't create the vertex buffer");
		return false;
	}

	v_buffer->Lock(0, 0, (void**) &pVoid, 0);
	{
		memcpy(pVoid, vertex, sizeof(vertex));
	}
	v_buffer->Unlock();

	//Set up the index buffer

	short indices [] =
	{
		0, 1, 2, 3
	};

	if (FAILED(pDevice->CreateIndexBuffer(4 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
	{
		CLog::Write("Box::Init - Couldn't create the index buffer");
		return false;
	}

	m_pIndexBuffer->Lock(0, 0, (void**) &pVoid, 0);
	{
		memcpy(pVoid, indices, sizeof(indices));
	}
	m_pIndexBuffer->Unlock();


	//Create the index declaration

	D3DVERTEXELEMENT9 decl [] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};

	if (FAILED(pDevice->CreateVertexDeclaration(decl, &m_pDeclaration)))
		return false;

	//Create the shader

	LPD3DXBUFFER pErr = nullptr;

	if (FAILED(D3DXCreateEffectFromResource(pDevice, GetModuleHandle("sampp_client.asi"), MAKEINTRESOURCE(IDR_RCDATA1), 0, 0, 0, 0, &m_pShader, &pErr)))
	{
		CLog::Write("D3DXCreateEffectFromResource failed: %s", (char*) pErr->GetBufferPointer());
		pErr->Release();
		pErr = nullptr;
		return false;
	}

	//Create the texture

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "rocks.jpg", &m_pTexture)))
	{
		CLog::Write("D3DXCreateTextureFromFile failed");
		return false;
	}

	//Initialize the variables

	m_fX = x;
	m_fY = y;

	m_fWidth = width;
	m_fHeight = height;

	m_pDevice = pDevice;

	m_bDraw = true;

	m_cColor = color;

	m_BarRect = { m_fX, m_fY, m_fX + m_fWidth, m_fY + m_fHeight };

	initialized = true;

	D3DXMatrixTranslation(&m_View, 0, 0, 2);
	D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(75), 1366 / 768, 0.01f, 100.0f);

	return true;
}

Box::~Box()
{

	if (v_buffer)
	{
		v_buffer->Release();
		v_buffer = nullptr;
	}

	if (m_pShader)
	{
		m_pShader->Release();
		m_pShader = nullptr;
	}

	if (m_pDeclaration)
	{
		m_pDeclaration->Release();
		m_pDeclaration = nullptr;
	}

	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}

void Box::Draw()
{
	if (m_bDraw && v_buffer && m_pIndexBuffer)
	{

		//m_pDevice->Clear(1, &m_BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_cColor, 0.0, 0);

		//m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		//Source
		//m_pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_SRCBLEND);

		//Destination
		//m_pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DRS_DESTBLEND);

		unsigned int pass = 0;
		m_pShader->Begin(&pass, 0);
		{
			for (unsigned int i = 0; i < pass; ++i)
			{
				m_pShader->BeginPass(i);
				{
					m_pShader->SetMatrix("WorldViewProj", &(m_World * m_View * m_Proj));
					//m_pDevice->SetVertexDeclaration(m_pDeclaration);
					m_pDevice->SetFVF(CUSTOMFVF);
					m_pDevice->SetStreamSource(0, v_buffer, 0, sizeof(VertexData));
					m_pDevice->SetIndices(m_pIndexBuffer);
					//m_pDevice->SetTexture(0, m_pTexture);
					m_pShader->CommitChanges();

					if (FAILED(m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2)))
					{
						CLog::Write("m_pDevice->DrawIndexedPrimitive failed");
					}
				}
				m_pShader->EndPass();
			}
		}
		m_pShader->End();

		/*

		m_pDevice->SetFVF(CUSTOMFVF);
		m_pDevice->SetStreamSource(0, v_buffer, 0, sizeof(VertexData));
		m_pDevice->SetIndices(m_pIndexBuffer);


		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);*/

		/*m_pDevice->SetFVF(CUSTOMFVF);

		//Disable Z-Depth


		m_pDevice->SetStreamSource(0, v_buffer, 0, sizeof(VertexData));

		// copy the vertex buffer to the back buffer
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Re-enable Z-Depth
		m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		//m_pDevice->EndScene();*/

	}
}

void Box::Show()
{
	m_bDraw = true;
}

void Box::Hide()
{
	m_bDraw = false;
}

void Box::OnLostDevice()
{
	CLog::Write("Box::OnLostDevice");
	m_pShader->OnLostDevice();
}

void Box::OnResetDevice()
{
	CLog::Write("Box::OnResetDevice");
	m_pShader->OnResetDevice();
}

bool Box::isInitialized()
{
	return initialized;
}
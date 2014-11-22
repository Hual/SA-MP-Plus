#include "Box.h"


Box::Box()
{
	initialized = false;
	m_bDraw = false;
	v_buffer = NULL;
	m_pDevice = NULL;
}


bool Box::Init(IDirect3DDevice9* pDevice, int width, int height, int x, int y, D3DCOLOR color)
{
	if (FAILED(pDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &v_buffer, NULL)))
		return false;


	CUSTOMVERTEX vertex[] =
	{
		//X			Y		  Z		RHW   Color
		{ x,		y,		  0.0f, 1.0f, color	},
		{ x+width,  y,		  0.0f, 1.0f, color	},
		{ x,		y+height, 0.0f,	1.0f, color	},
		{ x+width,  y+height, 0.0f,	1.0f, color	}
	};

	VOID* pVoid = NULL;

	if (FAILED(v_buffer->Lock(0, 0, (void**) &pVoid, 0)))
		return false;
	
	memcpy(pVoid, vertex, sizeof(vertex));

	if (!pVoid)
		return false;

	if (FAILED(v_buffer->Unlock()))
		return false;

	m_BarRect = { m_iX, m_iY, m_iX + m_iWidth, m_iY + m_iHeight };

	m_iX = x;
	m_iY = y;

	m_iWidth = width;
	m_iHeight = height;

	m_pDevice = pDevice;

	m_bDraw = true;

	m_cColor = color;

	initialized = true;
}

Box::~Box()
{

	if (v_buffer)
	{
		v_buffer->Release();
		v_buffer = NULL;
	}

}

void Box::Draw()
{
	if (m_bDraw && v_buffer)
	{

		m_pDevice->Clear(1, &m_BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_cColor, 0, 0);

		m_pDevice->SetFVF(CUSTOMFVF);

		//Disable Z-Depth
		m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		//Source
		m_pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DRS_SRCBLEND);

		//Destination
		m_pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DRS_DESTBLEND);

		m_pDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

			// copy the vertex buffer to the back buffer
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Re-enable Z-Depth
		m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		//m_pDevice->EndScene();
	
		

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
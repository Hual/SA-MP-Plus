#include <SAMP+/client/Client.h>
#include <SAMP+/client/CGame.h>
#include <SAMP+/client/Network.h>
#include <SAMP+/client/Proxy/CMessageProxy.h>
#include <SAMP+/client/Proxy/CD3D9DeviceProxy.h>

CD3D9DeviceProxy::CD3D9DeviceProxy(IDirect3DDevice9* pDirect3DDevice9, IDirect3D9* pDirect3D9, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	m_pDirect3DDevice9 = pDirect3DDevice9;
	m_pDirect3D9 = pDirect3D9;

	CGame::OnInitialize(m_pDirect3D9, m_pDirect3DDevice9, (*pPresentationParameters).hDeviceWindow);
}

CD3D9DeviceProxy::~CD3D9DeviceProxy()
{

}

HRESULT CD3D9DeviceProxy::QueryInterface(const IID &riid, void **ppvObj)
{
	return m_pDirect3DDevice9->QueryInterface(riid, ppvObj);
}

ULONG CD3D9DeviceProxy::AddRef()
{
   return m_pDirect3DDevice9->AddRef();
}

ULONG CD3D9DeviceProxy::Release()
{
	ULONG count = m_pDirect3DDevice9->Release();
	if(count == 0)
		delete this;

	return count;
}

HRESULT CD3D9DeviceProxy::TestCooperativeLevel() 
{
	return m_pDirect3DDevice9->TestCooperativeLevel();
}

HRESULT CD3D9DeviceProxy::EvictManagedResources() 
{
	return m_pDirect3DDevice9->EvictManagedResources();
}

HRESULT CD3D9DeviceProxy::GetDirect3D(IDirect3D9** ppD3D9)
{
	HRESULT hr = m_pDirect3DDevice9->GetDirect3D(ppD3D9);
	if(SUCCEEDED(hr))
		*ppD3D9 = m_pDirect3D9;

	return hr;
}

HRESULT CD3D9DeviceProxy::GetDeviceCaps(D3DCAPS9* pCaps) 
{
	return m_pDirect3DDevice9->GetDeviceCaps(pCaps);
}

HRESULT CD3D9DeviceProxy::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode) 
{
	return m_pDirect3DDevice9->GetDisplayMode(iSwapChain, pMode);
}

HRESULT CD3D9DeviceProxy::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) 
{
	return m_pDirect3DDevice9->GetCreationParameters(pParameters);
}

HRESULT CD3D9DeviceProxy::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap) 
{
	return m_pDirect3DDevice9->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

HRESULT CD3D9DeviceProxy::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain) 
{
	return m_pDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT CD3D9DeviceProxy::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain) 
{
	return m_pDirect3DDevice9->GetSwapChain(iSwapChain, pSwapChain);
}

HRESULT CD3D9DeviceProxy::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) 
{
	CGame::PreDeviceReset();
	HRESULT hRes = m_pDirect3DDevice9->Reset(pPresentationParameters);

	CMessageProxy::Initialize(pPresentationParameters->hDeviceWindow);

	if(hRes == D3D_OK)
		CGame::PostDeviceReset();

	return hRes;
}

HRESULT CD3D9DeviceProxy::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) 
{
	Network::Process();

	HRESULT hRes = m_pDirect3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	return hRes;
}

HRESULT CD3D9DeviceProxy::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) 
{
	return m_pDirect3DDevice9->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT CD3D9DeviceProxy::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) 
{
	return m_pDirect3DDevice9->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT CD3D9DeviceProxy::SetDialogBoxMode(BOOL bEnableDialogs) 
{
	return m_pDirect3DDevice9->SetDialogBoxMode(bEnableDialogs);
}

HRESULT CD3D9DeviceProxy::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);;
}

HRESULT CD3D9DeviceProxy::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) 
{
	return m_pDirect3DDevice9->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT CD3D9DeviceProxy::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) 
{
	return m_pDirect3DDevice9->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT CD3D9DeviceProxy::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) 
{
	return m_pDirect3DDevice9->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT CD3D9DeviceProxy::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface) 
{
	return m_pDirect3DDevice9->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT CD3D9DeviceProxy::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) 
{
	return m_pDirect3DDevice9->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT CD3D9DeviceProxy::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color) 
{
	return m_pDirect3DDevice9->ColorFill(pSurface, pRect, color);
}

HRESULT CD3D9DeviceProxy::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	return m_pDirect3DDevice9->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT CD3D9DeviceProxy::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget) 
{
	return m_pDirect3DDevice9->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT CD3D9DeviceProxy::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) 
{
	return m_pDirect3DDevice9->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT CD3D9DeviceProxy::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) 
{
	return m_pDirect3DDevice9->SetDepthStencilSurface(pNewZStencil);
}

HRESULT CD3D9DeviceProxy::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) 
{
	return m_pDirect3DDevice9->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT CD3D9DeviceProxy::BeginScene() 
{
	return m_pDirect3DDevice9->BeginScene();
}

HRESULT CD3D9DeviceProxy::EndScene() 
{
	CGame::PreEndScene();

	HRESULT hRes = m_pDirect3DDevice9->EndScene();

	CGame::PostEndScene();

	return hRes;
}

HRESULT CD3D9DeviceProxy::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) 
{
	return m_pDirect3DDevice9->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT CD3D9DeviceProxy::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) 
{
	return m_pDirect3DDevice9->SetTransform(State, pMatrix);
}

HRESULT CD3D9DeviceProxy::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) 
{
	return m_pDirect3DDevice9->GetTransform(State, pMatrix);
}

HRESULT CD3D9DeviceProxy::MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) 
{
	return m_pDirect3DDevice9->MultiplyTransform(State, pMatrix);
}

HRESULT CD3D9DeviceProxy::SetViewport(CONST D3DVIEWPORT9* pViewport) 
{
	return m_pDirect3DDevice9->SetViewport(pViewport);
}

HRESULT CD3D9DeviceProxy::GetViewport(D3DVIEWPORT9* pViewport) 
{
	return m_pDirect3DDevice9->GetViewport(pViewport);
}

HRESULT CD3D9DeviceProxy::SetMaterial(CONST D3DMATERIAL9* pMaterial) 
{
	return m_pDirect3DDevice9->SetMaterial(pMaterial);
}

HRESULT CD3D9DeviceProxy::GetMaterial(D3DMATERIAL9* pMaterial) 
{
	return m_pDirect3DDevice9->GetMaterial(pMaterial);
}

HRESULT CD3D9DeviceProxy::SetLight(DWORD Index,CONST D3DLIGHT9* pLight) 
{
	return m_pDirect3DDevice9->SetLight(Index, pLight);
}

HRESULT CD3D9DeviceProxy::GetLight(DWORD Index,D3DLIGHT9* pLight) 
{
	return m_pDirect3DDevice9->GetLight(Index, pLight);
}

HRESULT CD3D9DeviceProxy::LightEnable(DWORD Index,BOOL Enable) 
{
	return m_pDirect3DDevice9->LightEnable(Index, Enable);
}

HRESULT CD3D9DeviceProxy::GetLightEnable(DWORD Index,BOOL* pEnable) 
{
	return m_pDirect3DDevice9->GetLightEnable(Index, pEnable);
}

HRESULT CD3D9DeviceProxy::SetClipPlane(DWORD Index,CONST float* pPlane) 
{
	return m_pDirect3DDevice9->SetClipPlane(Index, pPlane);
}

HRESULT CD3D9DeviceProxy::GetClipPlane(DWORD Index,float* pPlane) 
{
	return m_pDirect3DDevice9->GetClipPlane(Index, pPlane);
}

HRESULT CD3D9DeviceProxy::SetRenderState(D3DRENDERSTATETYPE State,DWORD Value) 
{
	return m_pDirect3DDevice9->SetRenderState(State, Value);
}

HRESULT CD3D9DeviceProxy::GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue) 
{
	return m_pDirect3DDevice9->GetRenderState(State, pValue);
}

HRESULT CD3D9DeviceProxy::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) 
{
	return m_pDirect3DDevice9->CreateStateBlock(Type, ppSB);
}

HRESULT CD3D9DeviceProxy::BeginStateBlock() 
{
	return m_pDirect3DDevice9->BeginStateBlock();
}

HRESULT CD3D9DeviceProxy::EndStateBlock(IDirect3DStateBlock9** ppSB) 
{
	return m_pDirect3DDevice9->EndStateBlock(ppSB);
}

HRESULT CD3D9DeviceProxy::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus) 
{
	return m_pDirect3DDevice9->SetClipStatus(pClipStatus);
}

HRESULT CD3D9DeviceProxy::GetClipStatus(D3DCLIPSTATUS9* pClipStatus) 
{
	return m_pDirect3DDevice9->GetClipStatus(pClipStatus);
}

HRESULT CD3D9DeviceProxy::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture) 
{
	return m_pDirect3DDevice9->GetTexture(Stage, ppTexture);
}

HRESULT CD3D9DeviceProxy::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture) 
{
	return m_pDirect3DDevice9->SetTexture(Stage, pTexture);
}

HRESULT CD3D9DeviceProxy::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) 
{
	return m_pDirect3DDevice9->GetTextureStageState(Stage, Type, pValue);
}

HRESULT CD3D9DeviceProxy::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) 
{
	return m_pDirect3DDevice9->SetTextureStageState(Stage, Type, Value);
}

HRESULT CD3D9DeviceProxy::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) 
{
	return m_pDirect3DDevice9->GetSamplerState(Sampler, Type, pValue);
}

HRESULT CD3D9DeviceProxy::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) 
{
	return m_pDirect3DDevice9->SetSamplerState(Sampler, Type, Value);
}

HRESULT CD3D9DeviceProxy::ValidateDevice(DWORD* pNumPasses) 
{
	return m_pDirect3DDevice9->ValidateDevice(pNumPasses);
}

HRESULT CD3D9DeviceProxy::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries) 
{
	return m_pDirect3DDevice9->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT CD3D9DeviceProxy::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries) 
{
	return m_pDirect3DDevice9->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT CD3D9DeviceProxy::SetCurrentTexturePalette(UINT PaletteNumber) 
{
	return m_pDirect3DDevice9->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT CD3D9DeviceProxy::GetCurrentTexturePalette(UINT *PaletteNumber) 
{
	return m_pDirect3DDevice9->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT CD3D9DeviceProxy::SetScissorRect(CONST RECT* pRect) 
{
	return m_pDirect3DDevice9->SetScissorRect(pRect);
}

HRESULT CD3D9DeviceProxy::GetScissorRect(RECT* pRect) 
{
	return m_pDirect3DDevice9->GetScissorRect(pRect);
}

HRESULT CD3D9DeviceProxy::SetSoftwareVertexProcessing(BOOL bSoftware) 
{
	return m_pDirect3DDevice9->SetSoftwareVertexProcessing(bSoftware);
}

HRESULT CD3D9DeviceProxy::SetNPatchMode(float nSegments) 
{
	return m_pDirect3DDevice9->SetNPatchMode(nSegments);
}

HRESULT CD3D9DeviceProxy::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) 
{
	return m_pDirect3DDevice9->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT CD3D9DeviceProxy::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) 
{
	return m_pDirect3DDevice9->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT CD3D9DeviceProxy::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) 
{
	return m_pDirect3DDevice9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT CD3D9DeviceProxy::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) 
{
	return m_pDirect3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT CD3D9DeviceProxy::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) 
{
	return m_pDirect3DDevice9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT CD3D9DeviceProxy::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) 
{
	return m_pDirect3DDevice9->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT CD3D9DeviceProxy::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) 
{
	return m_pDirect3DDevice9->SetVertexDeclaration(pDecl);
}

HRESULT CD3D9DeviceProxy::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) 
{
	return m_pDirect3DDevice9->GetVertexDeclaration(ppDecl);
}

HRESULT CD3D9DeviceProxy::SetFVF(DWORD FVF) 
{
	return m_pDirect3DDevice9->SetFVF(FVF);
}

HRESULT CD3D9DeviceProxy::GetFVF(DWORD* pFVF) 
{
	return m_pDirect3DDevice9->GetFVF(pFVF);
}

HRESULT CD3D9DeviceProxy::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) 
{
	return m_pDirect3DDevice9->CreateVertexShader(pFunction, ppShader);
}

HRESULT CD3D9DeviceProxy::SetVertexShader(IDirect3DVertexShader9* pShader) 
{
	return m_pDirect3DDevice9->SetVertexShader(pShader);
}

HRESULT CD3D9DeviceProxy::GetVertexShader(IDirect3DVertexShader9** ppShader) 
{
	return m_pDirect3DDevice9->GetVertexShader(ppShader);
}

HRESULT CD3D9DeviceProxy::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) 
{
	return m_pDirect3DDevice9->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CD3D9DeviceProxy::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) 
{
	return m_pDirect3DDevice9->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CD3D9DeviceProxy::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) 
{
	return m_pDirect3DDevice9->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT CD3D9DeviceProxy::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) 
{
	return m_pDirect3DDevice9->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT CD3D9DeviceProxy::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) 
{
	return m_pDirect3DDevice9->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT CD3D9DeviceProxy::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) 
{
	return m_pDirect3DDevice9->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT CD3D9DeviceProxy::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) 
{
	return m_pDirect3DDevice9->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT CD3D9DeviceProxy::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride) 
{
	return m_pDirect3DDevice9->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT CD3D9DeviceProxy::SetStreamSourceFreq(UINT StreamNumber,UINT Setting) 
{
	return m_pDirect3DDevice9->SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT CD3D9DeviceProxy::GetStreamSourceFreq(UINT StreamNumber,UINT* pSetting) 
{
	return m_pDirect3DDevice9->GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT CD3D9DeviceProxy::SetIndices(IDirect3DIndexBuffer9* pIndexData) 
{
	return m_pDirect3DDevice9->SetIndices(pIndexData);
}

HRESULT CD3D9DeviceProxy::GetIndices(IDirect3DIndexBuffer9** ppIndexData) 
{
	return m_pDirect3DDevice9->GetIndices(ppIndexData);
}

HRESULT CD3D9DeviceProxy::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) 
{
	return m_pDirect3DDevice9->CreatePixelShader(pFunction, ppShader);
}

HRESULT CD3D9DeviceProxy::SetPixelShader(IDirect3DPixelShader9* pShader) 
{
	return m_pDirect3DDevice9->SetPixelShader(pShader);
}

HRESULT CD3D9DeviceProxy::GetPixelShader(IDirect3DPixelShader9** ppShader) 
{
	return m_pDirect3DDevice9->GetPixelShader(ppShader);
}

HRESULT CD3D9DeviceProxy::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) 
{
	return m_pDirect3DDevice9->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CD3D9DeviceProxy::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) 
{
	return m_pDirect3DDevice9->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CD3D9DeviceProxy::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) 
{
	return m_pDirect3DDevice9->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT CD3D9DeviceProxy::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) 
{
	return m_pDirect3DDevice9->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT CD3D9DeviceProxy::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) 
{
	return m_pDirect3DDevice9->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT CD3D9DeviceProxy::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) 
{
	return m_pDirect3DDevice9->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT CD3D9DeviceProxy::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) 
{
	return m_pDirect3DDevice9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT CD3D9DeviceProxy::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) 
{
	return m_pDirect3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT CD3D9DeviceProxy::DeletePatch(UINT Handle) 
{
	return m_pDirect3DDevice9->DeletePatch(Handle);
}

HRESULT CD3D9DeviceProxy::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) 
{
	return m_pDirect3DDevice9->CreateQuery(Type, ppQuery);
}

UINT CD3D9DeviceProxy::GetAvailableTextureMem()
{
	return m_pDirect3DDevice9->GetAvailableTextureMem();
}

void CD3D9DeviceProxy::SetCursorPosition(int X,int Y,DWORD Flags) 
{
	return m_pDirect3DDevice9->SetCursorPosition(X, Y, Flags);
}

BOOL CD3D9DeviceProxy::ShowCursor(BOOL bShow) 
{
	return m_pDirect3DDevice9->ShowCursor(bShow);
}

UINT CD3D9DeviceProxy::GetNumberOfSwapChains() 
{
	return m_pDirect3DDevice9->GetNumberOfSwapChains();
}

void CD3D9DeviceProxy::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) 
{
	return m_pDirect3DDevice9->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void CD3D9DeviceProxy::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp) 
{
	return m_pDirect3DDevice9->GetGammaRamp(iSwapChain, pRamp);
}

BOOL CD3D9DeviceProxy::GetSoftwareVertexProcessing()
{
	return m_pDirect3DDevice9->GetSoftwareVertexProcessing();
}

float CD3D9DeviceProxy::GetNPatchMode() 
{
	return m_pDirect3DDevice9->GetNPatchMode();
}
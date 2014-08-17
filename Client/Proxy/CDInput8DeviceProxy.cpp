#include <SAMP+/client/Client.h>
#include <SAMP+/client/CGraphics.h>
#include <SAMP+/client/Proxy/CDInput8DeviceProxy.h>

CDInput8DeviceProxy::CDInput8DeviceProxy(IDirectInput8A* pInput, IDirectInputDevice8A* pDevice)
{
	m_pInput = pInput;
    m_pDevice = pDevice;
	m_dwType = 0;

	DIDEVICEINSTANCEA di;
	di.dwSize = sizeof(di);
	if(SUCCEEDED(GetDeviceInfo(&di)))
		m_dwType = di.dwDevType & 0xff;

}

CDInput8DeviceProxy::~CDInput8DeviceProxy() { }

HRESULT CDInput8DeviceProxy::QueryInterface(REFIID riid,  LPVOID * ppvObj)
{
    return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG CDInput8DeviceProxy::AddRef(VOID)
{
    return m_pDevice->AddRef();
}

ULONG CDInput8DeviceProxy::Release(VOID)
{
	ULONG ulRefCount = m_pDevice->Release();
    if(ulRefCount == 0)
		delete this;

	return ulRefCount;
}

HRESULT CDInput8DeviceProxy::GetCapabilities(LPDIDEVCAPS a)
{
	return m_pDevice->GetCapabilities(a);
}

HRESULT CDInput8DeviceProxy::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a, LPVOID b, DWORD c)
{
    return m_pDevice->EnumObjects(a, b, c);
}

HRESULT CDInput8DeviceProxy::GetProperty(REFGUID a, LPDIPROPHEADER b)
{
    return m_pDevice->GetProperty(a, b);
}

HRESULT CDInput8DeviceProxy::SetProperty(REFGUID a, LPCDIPROPHEADER b)
{
    return m_pDevice->SetProperty(a, b);
}

HRESULT CDInput8DeviceProxy::Acquire(VOID)
{
    return m_pDevice->Acquire();
}

HRESULT CDInput8DeviceProxy::Unacquire(VOID)
{
    return m_pDevice->Unacquire();
}

HRESULT CDInput8DeviceProxy::GetDeviceState(DWORD a, LPVOID b)
{
	if (DINPUT_DEVICE_IS_MOUSE && CGraphics::IsCursorEnabled())
	{
		DWORD dwItems = INFINITE;
		HRESULT hRes;

		hRes = m_pDevice->GetDeviceState(a, b);
		memset(b, 0, a);

		m_pDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), NULL, &dwItems, 0);
		return hRes;
	}
    return m_pDevice->GetDeviceState(a, b);
}

HRESULT CDInput8DeviceProxy::GetDeviceData(DWORD a, LPDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d)
{
    return m_pDevice->GetDeviceData(a, b, c, d);

	/*if (DINPUT_DEVICE_IS_MOUSE && CGraphics::IsCursorEnabled())
	{
		DWORD dwItems = INFINITE;
		HRESULT hRes;

		hRes = m_pDevice->GetDeviceData(a, b, c, d);

		if(d != DIGDD_PEEK)
			m_pDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), NULL, &dwItems, 0);

		memset(b, 0, a*(*c));
		return hRes;
	}*/
}

HRESULT CDInput8DeviceProxy::SetDataFormat(LPCDIDATAFORMAT a)
{
    return m_pDevice->SetDataFormat(a);
}

HRESULT CDInput8DeviceProxy::SetEventNotification(HANDLE a)
{
    return m_pDevice->SetEventNotification(a);
}

HRESULT CDInput8DeviceProxy::SetCooperativeLevel(HWND a, DWORD b)
{
	return m_pDevice->SetCooperativeLevel(a, b);
}

HRESULT CDInput8DeviceProxy::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA a, DWORD b, DWORD c)
{
    return m_pDevice->GetObjectInfo(a, b, c);
}

HRESULT CDInput8DeviceProxy::GetDeviceInfo(LPDIDEVICEINSTANCEA a)
{
    return m_pDevice->GetDeviceInfo(a);
}

HRESULT CDInput8DeviceProxy::RunControlPanel(HWND a, DWORD b)
{
    return m_pDevice->RunControlPanel(a, b);
}

HRESULT CDInput8DeviceProxy::Initialize(HINSTANCE a, DWORD b, REFGUID c)
{
    return m_pDevice->Initialize(a, b, c);
}

HRESULT CDInput8DeviceProxy::CreateEffect(REFGUID a, LPCDIEFFECT b, LPDIRECTINPUTEFFECT * c, LPUNKNOWN d)
{
    return m_pDevice->CreateEffect(a, b, c, d);
}

HRESULT CDInput8DeviceProxy::EnumEffects(LPDIENUMEFFECTSCALLBACKA a, LPVOID b, DWORD c)
{
    return m_pDevice->EnumEffects(a, b, c);
}

HRESULT CDInput8DeviceProxy::GetEffectInfo(LPDIEFFECTINFOA a, REFGUID b)
{
    return m_pDevice->GetEffectInfo(a, b);
}

HRESULT CDInput8DeviceProxy::GetForceFeedbackState(LPDWORD a)
{
    return m_pDevice->GetForceFeedbackState(a);
}

HRESULT CDInput8DeviceProxy::SendForceFeedbackCommand(DWORD a)
{
    return m_pDevice->SendForceFeedbackCommand(a);
}

HRESULT CDInput8DeviceProxy::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a, LPVOID b, DWORD c)
{
    return m_pDevice->EnumCreatedEffectObjects(a, b, c);
}

HRESULT CDInput8DeviceProxy::Escape(LPDIEFFESCAPE a)
{
    return m_pDevice->Escape(a);
}

HRESULT CDInput8DeviceProxy::Poll(VOID)
{
    return m_pDevice->Poll();
}

HRESULT CDInput8DeviceProxy::SendDeviceData(DWORD a, LPCDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d)
{
    return m_pDevice->SendDeviceData(a, b, c, d);
}

HRESULT CDInput8DeviceProxy::EnumEffectsInFile(LPCSTR a, LPDIENUMEFFECTSINFILECALLBACK b, LPVOID c, DWORD d)
{
    return m_pDevice->EnumEffectsInFile(a, b, c, d);
}

HRESULT CDInput8DeviceProxy::WriteEffectToFile(LPCSTR a, DWORD b, LPDIFILEEFFECT c, DWORD d)
{
    return m_pDevice->WriteEffectToFile(a, b, c, d);
}

HRESULT CDInput8DeviceProxy::BuildActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c)
{
    return m_pDevice->BuildActionMap(a, b, c);
}

HRESULT CDInput8DeviceProxy::SetActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c)
{
    return m_pDevice->SetActionMap(a, b, c);
}

HRESULT CDInput8DeviceProxy::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA a)
{
    return m_pDevice->GetImageInfo(a);
}

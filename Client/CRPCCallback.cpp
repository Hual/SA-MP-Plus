#include <SAMP+/client/CRPCCallback.h>
#include <SAMP+/client/CHUD.h>
#include <SAMP+/client/CGame.h>
#include <SAMP+/client/CHooks.h>
#include <SAMP+/client/CLocalPlayer.h>
#include <SAMP+/client/Proxy/CJmpProxy.h>

void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::TOGGLE_HUD_COMPONENT, ToggleHUDComponent);
	CRPC::Add(eRPC::SET_RADIO_STATION, SetRadioStation);
	CRPC::Add(eRPC::SET_WAVE_HEIGHT, SetWaveHeight);
	CRPC::Add(eRPC::TOGGLE_PAUSE_MENU, TogglePauseMenu);
	CRPC::Add(eRPC::SET_HUD_COMPONENT_COLOUR, SetHUDComponentColour);
	CRPC::Add(eRPC::SET_CHECKPOINT_EX, SetPlayerCheckpointEx);
	CRPC::Add(eRPC::SET_RACE_CHECKPOINT_EX, SetPlayerRaceCheckpointEx);
	CRPC::Add(eRPC::SET_CHECKPOINT_COLOUR, SetCheckpointColour);
	CRPC::Add(eRPC::SET_RACE_CHECKPOINT_COLOUR, SetRaceCheckpointColour);
	CRPC::Add(eRPC::TOGGLE_ACTION, ToggleAction);
	CRPC::Add(eRPC::SET_CLIP_AMMO, SetAmmoInClip);
	CRPC::Add(eRPC::SET_NO_RELOAD, SetNoReload);
	CRPC::Add(eRPC::SET_BLUR_INTENSITY, SetBlur);
	CRPC::Add(eRPC::TOGGLE_DRIVE_ON_WATER, DriveOnWater);
	CRPC::Add(eRPC::SET_GAME_SPEED, SetSpeed);
	CRPC::Add(eRPC::TOGGLE_PLAYER_FROZEN, SetFrozen);
	CRPC::Add(eRPC::SET_PLAYER_ANIMS, SetAnims);
	CRPC::Add(eRPC::TOGGLE_SWITCH_RELOAD, ToggleSwitchReload);
	CRPC::Add(eRPC::TOGGLE_INFINITE_RUN, ToggleInfiniteRun);
	CRPC::Add(eRPC::SET_AIRCRAFT_HEIGHT, SetAircraftHeight);
	CRPC::Add(eRPC::SET_JETPACK_HEIGHT, SetJetpackHeight);
	CRPC::Add(eRPC::TOGGLE_VEHICLE_BLIPS, ToggleVehicleBlips);
	CRPC::Add(eRPC::TOGGLE_INFINITE_OXYGEN, ToggleInfiniteOxygen);
	CRPC::Add(eRPC::TOGGLE_WATER_BUOYANCY, ToggleWaterBuoyancy);
	CRPC::Add(eRPC::TOGGLE_UNDERWATER_EFFECT, ToggleUnderwaterEffect);
	CRPC::Add(eRPC::TOGGLE_NIGHTVISION, ToggleNightVision);
	CRPC::Add(eRPC::TOGGLE_THERMALVISION, ToggleThermalVision);

	CGame::OnResolutionChange(*(int*)0x0C9C040, *(int*)0x0C9C044);
	CMem::InstallJmp(0x0584770, CJmpProxy::MarkersHook, CJmpProxy::MarkersHookJmpBack, 6);
}

RPC_CALLBACK CRPCCallback::ToggleHUDComponent(RPC_ARGS)
{
	unsigned char ucComponent;
	bool bToggle;

	if (bsData.Read(ucComponent) && bsData.Read(bToggle))
		CHUD::ToggleComponent(ucComponent, bToggle);

}

RPC_CALLBACK CRPCCallback::SetHUDComponentColour(RPC_ARGS)
{
	unsigned char ucComponent;
	DWORD dwColour;

	if (bsData.Read(ucComponent) && bsData.Read(dwColour))
	{
		RakNet::BitStream::ReverseBytesInPlace((unsigned char*)&dwColour, sizeof(DWORD));

		CHUD::SetComponentColour(ucComponent, dwColour);
	}
}

RPC_CALLBACK CRPCCallback::SetRadioStation(RPC_ARGS)
{
	unsigned char ucStation;

	if (bsData.Read(ucStation))
		CGame::SetRadioStation(ucStation);
}

RPC_CALLBACK CRPCCallback::SetWaveHeight(RPC_ARGS)
{
	float fHeight;

	if (bsData.Read(fHeight))
		CGame::SetWaveHeight(fHeight);

}

RPC_CALLBACK CRPCCallback::TogglePauseMenu(RPC_ARGS)
{
	bool ucToggle;

	if (bsData.Read(ucToggle))
		CGame::PauseMenuEnabled = ucToggle;

}

RPC_CALLBACK CRPCCallback::SetCheckpointColour(RPC_ARGS)
{
	int dwColour;
	if (bsData.Read(dwColour))
	{
		int colR = (dwColour & 0xFF000000) >> 24;
		int colG = (dwColour & 0x00FF0000) >> 16;
		int colB = (dwColour & 0x0000FF00) >> 8;
		int colA = (dwColour & 0x000000FF);
		
		for(int i = 0; i < MAX_CHECKPOINTS; ++i)
		{
			unsigned char *thisCheckpoint = (unsigned char*) (CHECKPOINT_ADDR + (i * CHECKPOINT_OFFSET));

			if(*((unsigned short*) (thisCheckpoint + 80)) == 1)
			{
				*((unsigned long*) (thisCheckpoint + 88)) = ((colA << 24) | (colB << 16) | (colG << 8) | colR);
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::SetRaceCheckpointColour(RPC_ARGS)
{
	int dwColour;
	if (bsData.Read(dwColour))
	{
		int colR = (dwColour & 0xFF000000) >> 24;
		int colG = (dwColour & 0x00FF0000) >> 16;
		int colB = (dwColour & 0x0000FF00) >> 8;
		int colA = (dwColour & 0x000000FF);

		for(int i = 0; i < MAX_RACE_CHECKPOINTS; ++i)
		{
			unsigned char *thisCheckpoint = (unsigned char*) (RACE_CHECKPOINT_ADDR + (i * RACE_CHECKPOINT_OFFSET));

			if(*((bool*) (thisCheckpoint + 2)))
			{
				*((bool*) (thisCheckpoint + 2)) = false;
				*((unsigned long*) (thisCheckpoint + 8)) = ((colA << 24) | (colB << 16) | (colG << 8) | colR);
			}
		}

		CGame::RecreateMarkers = true;
	}
}

RPC_CALLBACK CRPCCallback::SetPlayerCheckpointEx(RPC_ARGS)
{
	CVector pos;
	float size;
	unsigned int col;
	unsigned short period;
	float pulse;
	short rot_rate;
	bool checkZ;

	if(bsData.Read(pos.x) && bsData.Read(pos.y) && bsData.Read(pos.z) && bsData.Read(size) && bsData.Read(col) && bsData.Read(period) && bsData.Read(pulse) && bsData.Read(rot_rate) && bsData.Read(checkZ))
	{
		// Crash
		//((PlaceCheckpoint_t) CHECKPOINT_PLACE)(1, 5, &pos, size, (col & 0xFF000000) >> 24, (col & 0x00FF0000) >> 16, (col & 0x0000FF00) >> 8, col & 0x000000FF, period, pulse, rot_rate, 0.0f, 0.0f, 0.0f, checkZ);
	}
}

RPC_CALLBACK CRPCCallback::SetPlayerRaceCheckpointEx(RPC_ARGS)
{
	unsigned char type;
	float pos[3];
	float next[3];
	float size;
	unsigned int col;
	unsigned short period;
	float pulse;
	short rot_rate;

	if(bsData.Read(type) && bsData.Read(pos[0]) && bsData.Read(pos[1]) && bsData.Read(pos[2]) && bsData.Read(next[0]) && bsData.Read(next[1]) && bsData.Read(next[2]) && bsData.Read(size) && bsData.Read(col) && bsData.Read(period) && bsData.Read(pulse) && bsData.Read(rot_rate))
	{
		char *thisCheckpoint = (char*) (RACE_CHECKPOINT_ADDR);

		float length = sqrtf(powf((pos[0]-next[0]), 2) + powf((pos[1]-next[1]), 2) + powf((pos[2]-next[2]), 2) );

		*((unsigned short*) (thisCheckpoint)) = type;
		*((bool*) (thisCheckpoint + 2)) = true;
		*((bool*) (thisCheckpoint + 3)) = true;
		*((unsigned long*) (thisCheckpoint + 4)) = 1;
		*((unsigned long*) (thisCheckpoint + 8)) = ((col & 0x000000FF) << 24) | ((col & 0x0000FF00) << 8) | ((col & 0x00FF0000) >> 8) | ((col & 0xFF000000) >> 24);
		*((unsigned short*) (thisCheckpoint + 12)) = period;
		*((short*) (thisCheckpoint + 14)) = rot_rate;
		((CVector*) (thisCheckpoint + 16))->x = pos[0];
		((CVector*) (thisCheckpoint + 16))->y = pos[1];
		((CVector*) (thisCheckpoint + 16))->z = pos[2];
		((CVector*) (thisCheckpoint + 28))->x = (next[0]-pos[0]) / length;
		((CVector*) (thisCheckpoint + 28))->y = (next[1]-pos[1]) / length;
		((CVector*) (thisCheckpoint + 28))->z = (next[2]-pos[2]) / length;
		*((float*) (thisCheckpoint + 40)) = pulse;
		*((float*) (thisCheckpoint + 44)) = size;
		*((float*) (thisCheckpoint + 48)) = 43.84f;
		*((float*) (thisCheckpoint + 52)) = 0.0;
	}
}

RPC_CALLBACK CRPCCallback::ToggleAction(RPC_ARGS)
{
	BYTE action;
	bool bToggle;

	if (bsData.Read(action) && bsData.Read(bToggle))
	{
		CLog::Write("ToggleAction %i %i", action, bToggle);
		CLocalPlayer::SetActionEnabled(action, bToggle);
	}

}

RPC_CALLBACK CRPCCallback::SetAmmoInClip(RPC_ARGS)
{
	DWORD dwNewAmmo;
	BYTE bSlotId;

	if (bsData.Read(bSlotId) && bsData.Read(dwNewAmmo))
	{
		CLocalPlayer::SetClipAmmo(bSlotId, dwNewAmmo);
	}
}

RPC_CALLBACK CRPCCallback::SetNoReload(RPC_ARGS)
{

	bool toggle;

	if (bsData.Read(toggle))
	{
		CLocalPlayer::SetNoReload(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleInfiniteRun(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CLocalPlayer::ToggleInfiniteRun(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetSpeed(RPC_ARGS)
{

	float speed;

	if (bsData.Read(speed))
	{
		CGame::SetGameSpeed(speed);
	}
}

RPC_CALLBACK CRPCCallback::DriveOnWater(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle)) 
	{
		CGame::ToggleDriveOnWater(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetBlur(RPC_ARGS)
{
	int intensity;
	if (bsData.Read(intensity))
	{
		CGame::SetBlurIntensity(intensity);
	}
}

RPC_CALLBACK CRPCCallback::SetFrozen(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleFrozen(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetAnims(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::SetPedAnims(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleSwitchReload(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleSwitchReload(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetAircraftHeight(RPC_ARGS)
{
	float height;
	if (bsData.Read(height))
	{
		CGame::SetAircraftMaxHeight(height);
	}
}

RPC_CALLBACK CRPCCallback::SetJetpackHeight(RPC_ARGS)
{
	float height;
	if (bsData.Read(height))
	{
		CGame::SetJetpackMaxHeight(height);
	}
}

RPC_CALLBACK CRPCCallback::ToggleVehicleBlips(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleVehicleBlips(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleInfiniteOxygen(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleInfiniteOxygen(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleWaterBuoyancy(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleWaterBuoyancy(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleUnderwaterEffect(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleUnderwaterEffect(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleNightVision(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleNightVision(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleThermalVision(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleThermalVision(toggle);
	}
}
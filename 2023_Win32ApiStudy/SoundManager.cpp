#include "pch.h"
#include "SoundManager.h"

#include "Core.h"

#include "Sound.h"

CSoundManager::CSoundManager() :
	m_soundDevice(),
	m_bgm()
{
}

CSoundManager::~CSoundManager()
{
}

int CSoundManager::Init(void)
{
	// 사운드 디바이스 생성
	if (FAILED(DirectSoundCreate8(NULL, &m_soundDevice, NULL)))
	{
		MessageBox(NULL, L"Fail to create sound device.", L"SYSTEM ERROR", MB_OK);

		return false;
	}

	// 사운드 디바이스 협조 레벨 설정(Flag 값 정리)
	if (FAILED(m_soundDevice->SetCooperativeLevel(CCore::GetInstance()->GetHwnd(), DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"Fail to set sound device's cooperative Level", L"SYSTEM ERROR", MB_OK);

		return false;
	}

	return true;
}

LPDIRECTSOUND8 CSoundManager::GetSoundDevice()
{
	return m_soundDevice;
}

void CSoundManager::RegisterBGM(CSound* sound)
{
	if (m_bgm != nullptr)
	{
		m_bgm->Stop();
	}

	m_bgm = sound;
}

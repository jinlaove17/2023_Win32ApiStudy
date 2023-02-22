#include "pch.h"
#include "Sound.h"

#include "SoundManager.h"

CSound::CSound() :
	m_isLoop(),
	m_soundBuffer(),
	m_bufferInfo(),
	m_volume()
{
}

CSound::~CSound()
{
	if (m_soundBuffer != nullptr)
	{
		m_soundBuffer->Release();
	}
}

bool CSound::LoadWaveSound(const wstring& filePath)
{
	// wav 파일을 연다.
	HMMIO hFile = mmioOpen((wchar_t*)filePath.c_str(), NULL, MMIO_READ);

	if (hFile == nullptr)
	{
		MessageBox(NULL, L"사운드 리소스 경로에 파일 없음", L"SYSTEM ERROR", MB_OK);

		return false;
	}

	// Chunk 청크 구조체, 문자열로 색인을 인식해서 WaveFormat 및 버퍼 선언 정보를 읽어온다.
	MMCKINFO parent = {};

	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &parent, NULL, MMIO_FINDRIFF);

	MMCKINFO child = {};

	child.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &child, &parent, MMIO_FINDCHUNK);

	WAVEFORMATEX waveFormat = {};

	mmioRead(hFile, (char*)&waveFormat, sizeof(waveFormat));

	mmioAscend(hFile, &child, 0);
	child.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &child, &parent, MMIO_FINDCHUNK);

	m_bufferInfo.dwBufferBytes = child.cksize;
	m_bufferInfo.dwSize = sizeof(DSBUFFERDESC);
	m_bufferInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	m_bufferInfo.lpwfxFormat = &waveFormat;

	if (FAILED(CSoundManager::GetInstance()->GetSoundDevice()->CreateSoundBuffer(&m_bufferInfo, &m_soundBuffer, nullptr)))
	{
		MessageBox(NULL, L"Fail to create sound buufer.", L"SYSTEM ERROR", MB_OK);

		return false;
	}

	void* write1 = nullptr;
	void* write2 = nullptr;
	DWORD length1 = 0, length2 = 0;

	m_soundBuffer->Lock(0, child.cksize, &write1, &length1, &write2, &length2, 0L);

	if (write1 != nullptr)
	{
		mmioRead(hFile, (char*)write1, length1);
	}

	if (write2 != nullptr)
	{
		mmioRead(hFile, (char*)write2, length2);
	}

	m_soundBuffer->Unlock(write1, length1, write2, length2);

	mmioClose(hFile, 0);

	// 초기 음량 절반으로 설정
	SetVolume(50.0f);

	return true;
}

int CSound::GetDecibel(float volume)
{
	// 볼륨 범위 (0.0f ~ 100.0f)
	if (volume <= 0.0f)
	{
		volume = 0.00001f;
	}
	else if (volume > 100.f)
	{
		volume = 100.f;
	}

	// 1.0f ~ 100.0f 사이의 값을 데시벨 단위로 변경
	int decibel = (int)(-2000.0 * log10(100.f / volume));

	if (decibel < -10000)
	{
		decibel = -10000;
	}

	return decibel;
}

int CSound::Load(const wstring& filePath)
{
	assert(CSoundManager::GetInstance()->GetSoundDevice() != nullptr);

	// 확장자 이름 구별하기
	wchar_t extName[10] = {};

	_wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extName, 10);

	if (!wcscmp(extName, L".wav")) // WAV 파일 로드
	{
		assert(LoadWaveSound(filePath));
	}

	return S_OK;
}

void CSound::Play(bool isLoop)
{
	// Play 함수의 1번째 2번째 인자는 0으로 이미 예약되어있다.
	// 3번째 변수는 사운드를 반복 재생할 것인지를 결정한다.
	m_isLoop = isLoop;
	m_soundBuffer->SetCurrentPosition(0);
	m_soundBuffer->Play(0, 0, (m_isLoop) ? DSBPLAY_LOOPING : 0);
}

void CSound::PlayToBGM(bool isLoop)
{
	CSoundManager::GetInstance()->RegisterBGM(this);

	m_isLoop = isLoop;
	m_soundBuffer->Play(0, 0, (m_isLoop) ? DSBPLAY_LOOPING : 0);
}

void CSound::Pause()
{
	m_soundBuffer->Stop();
}

void CSound::Stop()
{
	m_soundBuffer->Stop();
	m_soundBuffer->SetCurrentPosition(0);
}

void CSound::SetVolume(float volume)
{
	m_volume = GetDecibel(volume);
	m_soundBuffer->SetVolume(m_volume);
}

void CSound::SetPosition(float position)
{
	Stop();

	DWORD bytes = (DWORD)((position / 100.f) * (float)m_bufferInfo.dwBufferBytes);

	m_soundBuffer->SetCurrentPosition(bytes);

	Play(m_isLoop);
}

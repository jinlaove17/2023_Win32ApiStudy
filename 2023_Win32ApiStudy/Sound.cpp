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
	// wav ������ ����.
	HMMIO hFile = mmioOpen((wchar_t*)filePath.c_str(), NULL, MMIO_READ);

	if (hFile == nullptr)
	{
		MessageBox(NULL, L"���� ���ҽ� ��ο� ���� ����", L"SYSTEM ERROR", MB_OK);

		return false;
	}

	// Chunk ûũ ����ü, ���ڿ��� ������ �ν��ؼ� WaveFormat �� ���� ���� ������ �о�´�.
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

	// �ʱ� ���� �������� ����
	SetVolume(50.0f);

	return true;
}

int CSound::GetDecibel(float volume)
{
	// ���� ���� (0.0f ~ 100.0f)
	if (volume <= 0.0f)
	{
		volume = 0.00001f;
	}
	else if (volume > 100.f)
	{
		volume = 100.f;
	}

	// 1.0f ~ 100.0f ������ ���� ���ú� ������ ����
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

	// Ȯ���� �̸� �����ϱ�
	wchar_t extName[10] = {};

	_wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extName, 10);

	if (!wcscmp(extName, L".wav")) // WAV ���� �ε�
	{
		assert(LoadWaveSound(filePath));
	}

	return S_OK;
}

void CSound::Play(bool isLoop)
{
	// Play �Լ��� 1��° 2��° ���ڴ� 0���� �̹� ����Ǿ��ִ�.
	// 3��° ������ ���带 �ݺ� ����� �������� �����Ѵ�.
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

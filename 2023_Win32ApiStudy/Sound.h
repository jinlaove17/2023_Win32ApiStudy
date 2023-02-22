#pragma once

#include "Asset.h"

class CSound : public CAsset
{
	friend class CAssetManager;

private:
	bool				m_isLoop;

	LPDIRECTSOUNDBUFFER m_soundBuffer;
	DSBUFFERDESC		m_bufferInfo;
	int					m_volume;

private:
	CSound();

	bool LoadWaveSound(const wstring& filePath);
	int GetDecibel(float volume);

public:
	virtual ~CSound();

	int Load(const wstring& filePath);

	void Play(bool isLoop);
	void PlayToBGM(bool isLoop);
	void Pause();
	void Stop();

	void SetVolume(float volume);

	// �������� ��ġ ����
	void SetPosition(float position); // 0 ~ 100 ����
};

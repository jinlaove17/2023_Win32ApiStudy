#pragma once

class CSound;

class CSoundManager : public CSingleton<CSoundManager>
{
	friend class CSingleton;

private:
	LPDIRECTSOUND8 m_soundDevice; // ����ī�� ��ǥ ��ü
	CSound*        m_bgm;		  // ���� ������ BGM Sound

private:
	CSoundManager();
	~CSoundManager();

public:
	int Init(void);

	LPDIRECTSOUND8 GetSoundDevice();

	void RegisterBGM(CSound* sound);
};

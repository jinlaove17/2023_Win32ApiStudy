#pragma once

class CSound;

class CSoundManager : public CSingleton<CSoundManager>
{
	friend class CSingleton;

private:
	LPDIRECTSOUND8 m_soundDevice; // 사운드카드 대표 객체
	CSound*        m_bgm;		  // 현재 지정된 BGM Sound

private:
	CSoundManager();
	~CSoundManager();

public:
	int Init(void);

	LPDIRECTSOUND8 GetSoundDevice();

	void RegisterBGM(CSound* sound);
};

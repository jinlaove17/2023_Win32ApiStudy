#pragma once

class CTimeManager : public CSingleton<CTimeManager>
{
	friend class CSingleton;

private:
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_currentCount;
	LARGE_INTEGER m_frequency;

	// 현재 프레임과 이전 프레임 사이의 시간
	float		  m_deltaTime;

	// 1초를 계산하기 위한 누적 시간
	float		  m_accTime;

	// 함수 호출 횟수
	UINT		  m_callCount;

	// 초당 호출 횟수
	UINT		  m_fps;

private:
	CTimeManager();
	~CTimeManager();

public:
	void Init();

	float GetDeltaTime();

	void Update();
};

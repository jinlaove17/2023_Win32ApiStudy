#include "pch.h"
#include "TimeManager.h"

#include "Core.h"

CTimeManager::CTimeManager() :
	m_prevCount(),
	m_currentCount(),
	m_frequency(),
	m_deltaTime(),
	m_accTime(),
	m_callCount(),
	m_fps()
{
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_prevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_frequency);
}

float CTimeManager::GetDeltaTime()
{
	return m_deltaTime;
}

void CTimeManager::Update()
{
	QueryPerformanceCounter(&m_currentCount);

	// 현재 프레임의 카운트와 이전 프레임의 카운트 차이를 초당 카운트 횟수로 나누어 초당 카운트의 차를 구한다.
	m_deltaTime = (float)(m_currentCount.QuadPart - m_prevCount.QuadPart) / m_frequency.QuadPart;

#ifdef _DEBUG
	// 중단점을 걸었을 때, 시간이 오래 지나면 m_deltaTime이 매우 커지기 때문에 디버그 모드일 때는 이 값을 고정시킨다.
	float fixedDeltaTime = 1.0f / 60.0f;

	if (m_deltaTime > fixedDeltaTime)
	{
		m_deltaTime = fixedDeltaTime;
	}
#endif

	// 다음 번 계산을 위해여 이전 카운트의 값을 현재 카운트 값으로 갱신한다.
	m_prevCount = m_currentCount;

	// 호출 횟수를 1 증가시킨다.
	++m_callCount;

	// 흐른 시간을 누적한다.
	m_accTime += m_deltaTime;

	if (m_accTime >= 1.0f)
	{
		m_fps = m_callCount;
		m_callCount = 0;
		m_accTime = 0.0f;

		WCHAR buffer[64] = {};

		swprintf_s(buffer, L"FPS: %d, DeltaTime: %f", m_fps, m_deltaTime);
		SetWindowText(CCore::GetInstance()->GetHwnd(), buffer);
	}
}

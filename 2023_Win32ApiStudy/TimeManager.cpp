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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_prevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_frequency);
}

float CTimeManager::GetDeltaTime()
{
	return m_deltaTime;
}

void CTimeManager::Update()
{
	QueryPerformanceCounter(&m_currentCount);

	// ���� �������� ī��Ʈ�� ���� �������� ī��Ʈ ���̸� �ʴ� ī��Ʈ Ƚ���� ������ �ʴ� ī��Ʈ�� ���� ���Ѵ�.
	m_deltaTime = (float)(m_currentCount.QuadPart - m_prevCount.QuadPart) / m_frequency.QuadPart;

#ifdef _DEBUG
	// �ߴ����� �ɾ��� ��, �ð��� ���� ������ m_deltaTime�� �ſ� Ŀ���� ������ ����� ����� ���� �� ���� ������Ų��.
	float fixedDeltaTime = 1.0f / 60.0f;

	if (m_deltaTime > fixedDeltaTime)
	{
		m_deltaTime = fixedDeltaTime;
	}
#endif

	// ���� �� ����� ���ؿ� ���� ī��Ʈ�� ���� ���� ī��Ʈ ������ �����Ѵ�.
	m_prevCount = m_currentCount;

	// ȣ�� Ƚ���� 1 ������Ų��.
	++m_callCount;

	// �帥 �ð��� �����Ѵ�.
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

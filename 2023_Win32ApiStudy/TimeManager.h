#pragma once

class CTimeManager
{
	SINGLETON(CTimeManager)

private:
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_currentCount;
	LARGE_INTEGER m_frequency;

	// ���� �����Ӱ� ���� ������ ������ �ð�
	float		  m_deltaTime;

	// 1�ʸ� ����ϱ� ���� ���� �ð�
	float		  m_accTime;

	// �Լ� ȣ�� Ƚ��
	UINT		  m_callCount;

	// �ʴ� ȣ�� Ƚ��
	UINT		  m_fps;

public:
	void Init();

	float GetDeltaTime();

	void Update();
};

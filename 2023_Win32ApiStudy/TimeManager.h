#pragma once

class CTimeManager : public CSingleton<CTimeManager>
{
	friend class CSingleton;

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

private:
	CTimeManager();
	~CTimeManager();

public:
	void Init();

	float GetDeltaTime();

	void Update();
};

#pragma once

class CCollider;

union CollisionID
{
	struct
	{
		ULONG m_lowPart;
		ULONG m_highPart;
	};

	ULONGLONG m_quadPart;
};

class CCollisionManager : public CSingleton<CCollisionManager>
{
	friend class CSingleton;

private:
	UINT                           m_layer[(int)GROUP_TYPE::COUNT]; // �׷� ���� �浹 üũ ���̾�
	unordered_map<ULONGLONG, bool> m_prevStates;				    // �浹ü ���� ���� ������ �浹 ����

private:
	CCollisionManager();
	~CCollisionManager();

	void UpdateCollisionGroup(GROUP_TYPE group1, GROUP_TYPE group2);
	bool IsCollided(CCollider* collider1, CCollider* collider2);

public:
	void SetCollisionGroup(GROUP_TYPE group1, GROUP_TYPE group2);
	void ResetCollisionGroup();

	void Update();
};

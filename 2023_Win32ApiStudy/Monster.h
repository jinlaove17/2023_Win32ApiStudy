#pragma once
#include "Object.h"

struct MonsterInfo
{
	float m_health;	      // ü��
	float m_speed;		  // �̵� �ӵ�
	float m_recogRange;	  // �÷��̾� �ν� ����
	float m_attackRange;  // ���� ����
	float m_attackDamage; // ���ݷ�
};

class CMonster : public CObject
{
	friend class CMonsterFactory;

private:
	MonsterInfo m_info;

public:
	CMonster();
	virtual ~CMonster();

	CLONE(CMonster);

	const MonsterInfo& GetInfo();

	void SetHealth(float health);
	float GetHealth();

	void SetSpeed(float speed);
	float GetSpeed();

	virtual void OnCollisionEnter(CCollider* collidedCollider); // �浹 ���� �� ȣ��
	virtual void OnCollision(CCollider* collidedCollider);      // �浹 ���� �� ȣ��
	virtual void OnCollisionExit(CCollider* collidedCollider);  // �浹 ���� �� ȣ��

private:
	void SetInfo(const MonsterInfo& info);
};

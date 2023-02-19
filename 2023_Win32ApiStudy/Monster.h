#pragma once
#include "Object.h"

struct MonsterInfo
{
	float m_health;	      // 체력
	float m_speed;		  // 이동 속도
	float m_recogRange;	  // 플레이어 인식 범위
	float m_attackRange;  // 공격 범위
	float m_attackDamage; // 공격력
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

	virtual void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	virtual void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	virtual void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출

private:
	void SetInfo(const MonsterInfo& info);
};

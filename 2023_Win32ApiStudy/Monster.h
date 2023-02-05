#pragma once
#include "Object.h"

class CMonster : public CObject
{
private:
	Vec2  m_centerPosition;

	float m_direction;
	float m_speed;
	float m_maxDistance;

public:
	CMonster();
	virtual ~CMonster();

	void SetDirection(float direction);
	float GetDirection();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetMaxDistance(float maxDistance);
	float GetMaxDistance();

	void SetCenterPosition(const Vec2& centerPosition);
	const Vec2& GetCenterPosition();

	virtual void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	virtual void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	virtual void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출

	virtual void Update();
};

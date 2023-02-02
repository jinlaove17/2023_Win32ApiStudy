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

	virtual void Update();
};

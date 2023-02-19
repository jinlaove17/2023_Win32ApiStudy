#pragma once
#include "Component.h"

class CRigidBody : public CComponent
{
	friend class CObject;

private:
	bool	 m_isUsedGravity; // 중력의 영향을 받는지에 대한 여부(기본 값: true)

	float	 m_mass;	      // 질량
	Vec2	 m_force;	      // 힘(방향, 크기)
	Vec2	 m_velocity;      // 속도
	float    m_maxSpeed;      // 최대 속력
	Vec2	 m_accel;         // 가속도
	float    m_frictionCoeff; // 마찰 계수

private:
	CRigidBody();
	~CRigidBody();

public:
	void SetGravity(bool useGravity);
	bool IsUsedGravity();

	void SetMass(float mass);
	float GetMass();

	void SetVelocity(const Vec2& velocity); 
	const Vec2& GetVelocity();

	float GetSpeed();

	void SetMaxSpeed(float maxSpeed);
	float GetMaxSpeed();

	void AddVelocity(const Vec2& velocity); // 속도는 Update 함수에서 계산되지만, 게임 내에서는 별도로 조작하여 자연스럽게 만들 수 있다.
	void AddForce(const Vec2& force);

	void MovePosition();

	virtual void Update();

	virtual void Render(HDC hDC);
};

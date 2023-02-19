#pragma once
#include "Component.h"

class CRigidBody : public CComponent
{
	friend class CObject;

private:
	static const Vec2 m_gravityAccel;		// 중력 가속도
											
	bool			  m_isUsedGravity;		// 중력의 영향을 받는지에 대한 여부(기본 값: true)
	bool			  m_isLanded;			// 타 충돌체에 착지 여부
					  						  
	float			  m_mass;				// 질량
	Vec2			  m_force;				// 힘(방향, 크기)
	Vec2			  m_velocity;			// 속도
	Vec2			  m_maxVelocity;		// 최대 속도
	Vec2			  m_accel;				// 가속도
											
	float			  m_frictionCoeff;		// 마찰 계수(m_velocity.m_x의 반대 방향으로 작용)
	float			  m_airRegistanceCoeff; // 공기 저항 계수(m_velocity.m_y의 반대 방향으로 작용)

private:
	CRigidBody();
	~CRigidBody();

public:
	void SetGravity(bool useGravity);
	bool IsUsedGravity();

	void SetLanded(bool isLanded);
	bool IsLanded();

	void SetMass(float mass);
	float GetMass();

	void SetVelocity(const Vec2& velocity); 
	const Vec2& GetVelocity();

	void SetMaxVelocity(const Vec2& velocity);
	const Vec2& GetMaxVelocity();

	float GetSpeedX();
	float GetSpeedY();

	void SetFrictionCoeff(float frictionCoeff);
	float GetFrictionCoeff();

	void SetAirResistanceCoeff(float airRegistanceCoeff);
	float GetAirResistanceCoeff();

	void AddVelocity(const Vec2& velocity); // 속도는 Update 함수에서 계산되지만, 게임 내에서는 별도로 조작하여 자연스럽게 만들 수 있다.
	void AddForce(const Vec2& force);

	void MovePosition();

	virtual void Update();

	virtual void Render(HDC hDC);
};

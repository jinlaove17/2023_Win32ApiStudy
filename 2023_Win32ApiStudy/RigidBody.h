#pragma once

class CObject;

class CRigidBody
{
	friend class CObject;

private:
	float	 m_mass;	      // 질량
	Vec2	 m_force;	      // 힘(방향, 크기)
	Vec2	 m_velocity;      // 속도
	float    m_maxSpeed;      // 최대 속력
	Vec2	 m_accel;         // 가속도
	float    m_frictionCoeff; // 마찰 계수

	CObject* m_owner;

public:
	CRigidBody();
	~CRigidBody();

	void SetMass(float mass);
	float GetMass();

	void SetVelocity(const Vec2& velocity); 
	const Vec2& GetVelocity();

	void SetMaxSpeed(float maxSpeed);
	float GetMaxSpeed();

	CObject* GetOwner();

	void AddVelocity(const Vec2& velocity); // 속도는 Update 함수에서 계산되지만, 게임 내에서는 별도로 조작하여 자연스럽게 만들 수 있다.
	void AddForce(const Vec2& force);

	void Update();

	void MovePosition();
};

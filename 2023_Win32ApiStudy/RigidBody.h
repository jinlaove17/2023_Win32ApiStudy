#pragma once
#include "Component.h"

class CRigidBody : public CComponent
{
	friend class CObject;

private:
	float	 m_mass;	      // ����
	Vec2	 m_force;	      // ��(����, ũ��)
	Vec2	 m_velocity;      // �ӵ�
	float    m_maxSpeed;      // �ִ� �ӷ�
	Vec2	 m_accel;         // ���ӵ�
	float    m_frictionCoeff; // ���� ���

private:
	CRigidBody();
	~CRigidBody();

public:
	void SetMass(float mass);
	float GetMass();

	void SetVelocity(const Vec2& velocity); 
	const Vec2& GetVelocity();

	void SetMaxSpeed(float maxSpeed);
	float GetMaxSpeed();

	void AddVelocity(const Vec2& velocity); // �ӵ��� Update �Լ����� ��������, ���� �������� ������ �����Ͽ� �ڿ������� ���� �� �ִ�.
	void AddForce(const Vec2& force);

	void MovePosition();

	virtual void Update();

	virtual void Render(HDC hDC);
};

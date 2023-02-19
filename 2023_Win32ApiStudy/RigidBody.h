#pragma once
#include "Component.h"

class CRigidBody : public CComponent
{
	friend class CObject;

private:
	static const Vec2 m_gravityAccel;		// �߷� ���ӵ�
											
	bool			  m_isUsedGravity;		// �߷��� ������ �޴����� ���� ����(�⺻ ��: true)
	bool			  m_isLanded;			// Ÿ �浹ü�� ���� ����
					  						  
	float			  m_mass;				// ����
	Vec2			  m_force;				// ��(����, ũ��)
	Vec2			  m_velocity;			// �ӵ�
	Vec2			  m_maxVelocity;		// �ִ� �ӵ�
	Vec2			  m_accel;				// ���ӵ�
											
	float			  m_frictionCoeff;		// ���� ���(m_velocity.m_x�� �ݴ� �������� �ۿ�)
	float			  m_airRegistanceCoeff; // ���� ���� ���(m_velocity.m_y�� �ݴ� �������� �ۿ�)

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

	void AddVelocity(const Vec2& velocity); // �ӵ��� Update �Լ����� ��������, ���� �������� ������ �����Ͽ� �ڿ������� ���� �� �ִ�.
	void AddForce(const Vec2& force);

	void MovePosition();

	virtual void Update();

	virtual void Render(HDC hDC);
};

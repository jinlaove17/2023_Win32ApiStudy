#pragma once

class CObject;

class CRigidBody
{
	friend class CObject;

private:
	float	 m_mass;	      // ����
	Vec2	 m_force;	      // ��(����, ũ��)
	Vec2	 m_velocity;      // �ӵ�
	float    m_maxSpeed;      // �ִ� �ӷ�
	Vec2	 m_accel;         // ���ӵ�
	float    m_frictionCoeff; // ���� ���

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

	void AddVelocity(const Vec2& velocity); // �ӵ��� Update �Լ����� ��������, ���� �������� ������ �����Ͽ� �ڿ������� ���� �� �ִ�.
	void AddForce(const Vec2& force);

	void Update();

	void MovePosition();
};

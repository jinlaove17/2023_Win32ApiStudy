#include "pch.h"
#include "RigidBody.h"

#include "TimeManager.h"

CRigidBody::CRigidBody() :
	m_isUsedGravity(true),
	m_mass(1.0f),
	m_force(),
	m_velocity(),
	m_maxSpeed(200.0f),
	m_accel(),
	m_frictionCoeff(80.0f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::SetGravity(bool useGravity)
{
	m_isUsedGravity = useGravity;
}

bool CRigidBody::IsUsedGravity()
{
	return m_isUsedGravity;
}

void CRigidBody::SetMass(float mass)
{
	assert(mass > 0.0f);

	m_mass = mass;
}

float CRigidBody::GetMass()
{
	return m_mass;
}

void CRigidBody::SetVelocity(const Vec2& velocity)
{
	m_velocity = velocity;
}

const Vec2& CRigidBody::GetVelocity()
{
	return m_velocity;
}

float CRigidBody::GetSpeed()
{
	return m_velocity.Length();
}

void CRigidBody::SetMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

float CRigidBody::GetMaxSpeed()
{
	return m_maxSpeed;
}

void CRigidBody::AddVelocity(const Vec2& velocity)
{
	m_velocity += velocity;
}

void CRigidBody::AddForce(const Vec2& force)
{
	m_force += force;
}

void CRigidBody::Update()
{
	float frictionCoeff = m_frictionCoeff;

	if (m_force.Length() > 0.0f)
	{
		m_accel = m_force / m_mass;
		m_velocity += m_accel * DT;
	}
	else
	{
		// �̹� �����ӿ� ������ �Է��� ���� ���� ũ�Ⱑ 0�� ��쿡��, �������� ������Ų��.
		frictionCoeff *= 10.0f;
	}

	// �ӵ� ���� �˻�
	float speed = m_velocity.Length();

	if (speed > m_maxSpeed)
	{
		m_velocity.Normalize();
		m_velocity *= m_maxSpeed;
		speed = m_maxSpeed;
	}

	if (speed > 0.0f)
	{
		// ������ ����
		Vec2 friction = -m_velocity;

		friction = friction.Normalize() * frictionCoeff * DT;

		// �������� ���� �ӵ����� �� ū ���
		if (friction.Length() >= speed)
		{
			m_velocity = Vec2(0.0f, 0.0f);
		}
		else
		{
			m_velocity += friction;
		}
	}

	MovePosition();

	// �� ������ ���� ������ �� �ʱ�ȭ
	m_force = Vec2(0.0f, 0.0f);
}

void CRigidBody::Render(HDC hDC)
{
}

void CRigidBody::MovePosition()
{
	// ��ġ �̵�
	Vec2 position = GetOwner()->GetPosition();

	position += m_velocity * DT;

	GetOwner()->SetPosition(position);
}

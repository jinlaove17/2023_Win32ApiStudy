#include "pch.h"
#include "RigidBody.h"

#include "TimeManager.h"

#include "Object.h"

CRigidBody::CRigidBody() :
	m_mass(1.0f),
	m_force(),
	m_velocity(),
	m_maxSpeed(200.0f),
	m_accel(),
	m_frictionCoeff(80.0f),
	m_owner()
{
}

CRigidBody::~CRigidBody()
{
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

void CRigidBody::SetMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

float CRigidBody::GetMaxSpeed()
{
	return m_maxSpeed;
}

CObject* CRigidBody::GetOwner()
{
	return m_owner;
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
	if (m_force.Length() > 0.0f)
	{
		m_accel = m_force / m_mass;
		m_velocity += m_accel * DT;
	}

	// 속도 제한 검사
	float speed = m_velocity.Length();

	if (speed > m_maxSpeed)
	{
		m_velocity.Normalize();
		m_velocity *= m_maxSpeed;
		speed = m_maxSpeed;
	}

	if (speed > 0.0f)
	{
		// 마찰력 적용
		Vec2 friction = -m_velocity;

		friction = friction.Normalize() * m_frictionCoeff * DT;

		// 마찰력이 현재 속도보다 더 큰 경우
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

	// 한 프레임 동안 누적된 힘 초기화
	m_force = Vec2(0.0f, 0.0f);
}

void CRigidBody::MovePosition()
{
	// 위치 이동
	Vec2 position = m_owner->GetPosition();

	position += m_velocity * DT;

	m_owner->SetPosition(position);
}

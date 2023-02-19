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
		// 이번 프레임에 별도의 입력이 없어 힘의 크기가 0인 경우에는, 마찰력을 급증시킨다.
		frictionCoeff *= 10.0f;
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

		friction = friction.Normalize() * frictionCoeff * DT;

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

void CRigidBody::Render(HDC hDC)
{
}

void CRigidBody::MovePosition()
{
	// 위치 이동
	Vec2 position = GetOwner()->GetPosition();

	position += m_velocity * DT;

	GetOwner()->SetPosition(position);
}

#include "pch.h"
#include "RigidBody.h"

#include "TimeManager.h"

const Vec2 CRigidBody::m_gravityAccel = { 0.0f, 1000.0f };

CRigidBody::CRigidBody() :
	m_isUsedGravity(true),
	m_isLanded(),
	m_mass(1.0f),
	m_force(),
	m_velocity(),
	m_maxVelocity(Vec2(300.0f, 600.0f)),
	m_accel(),
	m_frictionCoeff(40.0f),
	m_airRegistanceCoeff(50.0f)
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

void CRigidBody::SetLanded(bool isLanded)
{
	m_isLanded = isLanded;

	if (m_isLanded)
	{
		m_velocity.m_y = 0.0f;
	}
}

bool CRigidBody::IsLanded()
{
	return m_isLanded;
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

void CRigidBody::SetMaxVelocity(const Vec2& velocity)
{
	m_maxVelocity = velocity;
}

const Vec2& CRigidBody::GetMaxVelocity()
{
	return m_maxVelocity;
}

float CRigidBody::GetSpeedX()
{
	return abs(m_velocity.m_x);
}

float CRigidBody::GetSpeedY()
{
	return abs(m_velocity.m_y);
}

void CRigidBody::SetFrictionCoeff(float frictionCoeff)
{
	m_frictionCoeff = frictionCoeff;
}

float CRigidBody::GetFrictionCoeff()
{
	return m_frictionCoeff;
}

void CRigidBody::SetAirResistanceCoeff(float airRegistanceCoeff)
{
	m_airRegistanceCoeff = airRegistanceCoeff;
}

float CRigidBody::GetAirResistanceCoeff()
{
	return m_airRegistanceCoeff;
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
	// 가속도 갱신
	// F = M * A
	// A = F / m;
	m_accel = m_force / m_mass;

	// 중력 가속도 추가
	if (m_isUsedGravity && !m_isLanded)
	{
		m_accel += m_gravityAccel;
	}

	// 갱신된 가속도만큼 속도 증가
	m_velocity += m_accel * DT;

	// X축 성분 처리
	float speedX = abs(m_velocity.m_x);

	if (speedX > 0.0f)
	{
		// 이번 프레임에 X축 성분으로 누적된 힘이 없을 경우, 마찰력을 급증시킨다.
		float frictionCoeff = (abs(m_force.m_x) > 0.0f) ? m_frictionCoeff : 10.0f * m_frictionCoeff;

		// X축 성분에 대해 마찰력 적용
		float direction = m_velocity.m_x / speedX;
		float friction = -direction * frictionCoeff * DT;

		// 마찰력이 현재 속도보다 더 큰 경우
		if (friction >= speedX)
		{
			m_velocity.m_x = 0.0f;
		}
		else
		{
			m_velocity.m_x += friction;
		}

		// 마찰력을 계산한 이후, X축 속도 성분을 다시 구한다.
		speedX = abs(m_velocity.m_x);

		float maxSpeedX = abs(m_maxVelocity.m_x);

		// 최대 속도 제한
		if (speedX > maxSpeedX)
		{
			// 현재 속도의 X축 성분을 X축의 길이로 나누고, 최대 속력을 곱한다.
			m_velocity.m_x = direction * maxSpeedX;
		}
	}

	// Y축 성분 처리
	float speedY = abs(m_velocity.m_y);

	if (speedY > 0.0f)
	{
		//// Y축 성분에 대해 공기 저항 적용
		float direction = m_velocity.m_y / speedY;
		float airRegistance = -direction * m_airRegistanceCoeff * DT;

		// 공기 저항이 현재 속도보다 더 큰 경우
		if (airRegistance >= speedY)
		{
			m_velocity.m_y = 0.0f;
		}
		else
		{
			m_velocity.m_y += airRegistance;
		}

		// 공기 저항을 계산한 이후, Y축 속도 성분을 다시 구한다.
		speedY = abs(m_velocity.m_y);

		float maxSpeedY = abs(m_maxVelocity.m_y);

		// 최대 속도 제한
		if (speedY > maxSpeedY)
		{
			// 현재 속도의 Y축 성분을 Y축의 길이로 나누고, 최대 속력을 곱한다.
			m_velocity.m_y = direction * maxSpeedY;
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

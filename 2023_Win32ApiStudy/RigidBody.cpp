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
	// ���ӵ� ����
	// F = M * A
	// A = F / m;
	m_accel = m_force / m_mass;

	// �߷� ���ӵ� �߰�
	if (m_isUsedGravity && !m_isLanded)
	{
		m_accel += m_gravityAccel;
	}

	// ���ŵ� ���ӵ���ŭ �ӵ� ����
	m_velocity += m_accel * DT;

	// X�� ���� ó��
	float speedX = abs(m_velocity.m_x);

	if (speedX > 0.0f)
	{
		// �̹� �����ӿ� X�� �������� ������ ���� ���� ���, �������� ������Ų��.
		float frictionCoeff = (abs(m_force.m_x) > 0.0f) ? m_frictionCoeff : 10.0f * m_frictionCoeff;

		// X�� ���п� ���� ������ ����
		float direction = m_velocity.m_x / speedX;
		float friction = -direction * frictionCoeff * DT;

		// �������� ���� �ӵ����� �� ū ���
		if (friction >= speedX)
		{
			m_velocity.m_x = 0.0f;
		}
		else
		{
			m_velocity.m_x += friction;
		}

		// �������� ����� ����, X�� �ӵ� ������ �ٽ� ���Ѵ�.
		speedX = abs(m_velocity.m_x);

		float maxSpeedX = abs(m_maxVelocity.m_x);

		// �ִ� �ӵ� ����
		if (speedX > maxSpeedX)
		{
			// ���� �ӵ��� X�� ������ X���� ���̷� ������, �ִ� �ӷ��� ���Ѵ�.
			m_velocity.m_x = direction * maxSpeedX;
		}
	}

	// Y�� ���� ó��
	float speedY = abs(m_velocity.m_y);

	if (speedY > 0.0f)
	{
		//// Y�� ���п� ���� ���� ���� ����
		float direction = m_velocity.m_y / speedY;
		float airRegistance = -direction * m_airRegistanceCoeff * DT;

		// ���� ������ ���� �ӵ����� �� ū ���
		if (airRegistance >= speedY)
		{
			m_velocity.m_y = 0.0f;
		}
		else
		{
			m_velocity.m_y += airRegistance;
		}

		// ���� ������ ����� ����, Y�� �ӵ� ������ �ٽ� ���Ѵ�.
		speedY = abs(m_velocity.m_y);

		float maxSpeedY = abs(m_maxVelocity.m_y);

		// �ִ� �ӵ� ����
		if (speedY > maxSpeedY)
		{
			// ���� �ӵ��� Y�� ������ Y���� ���̷� ������, �ִ� �ӷ��� ���Ѵ�.
			m_velocity.m_y = direction * maxSpeedY;
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

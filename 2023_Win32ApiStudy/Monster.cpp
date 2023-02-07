#include "pch.h"
#include "Monster.h"

#include "TimeManager.h"
#include "EventManager.h"

#include "Collider.h"

CMonster::CMonster() :
	m_centerPosition(),
	m_direction(1.0f),
	m_speed(150.0f),
	m_maxDistance(40.0f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.0f, 40.0f));
}

CMonster::~CMonster()
{
}

void CMonster::SetDirection(float direction)
{
	m_direction = direction;
}

float CMonster::GetDirection()
{
	return m_direction;
}

void CMonster::SetSpeed(float speed)
{
	m_speed = speed;
}

float CMonster::GetSpeed()
{
	return m_speed;
}

void CMonster::SetMaxDistance(float maxDistance)
{
	m_maxDistance = maxDistance;
}

float CMonster::GetMaxDistance()
{
	return m_maxDistance;
}

void CMonster::SetCenterPosition(const Vec2& centerPosition)
{
	m_centerPosition = centerPosition;
}

const Vec2& CMonster::GetCenterPosition()
{
	return m_centerPosition;
}

void CMonster::OnCollisionEnter(CCollider* collidedCollider)
{
	CObject* collidedObject = collidedCollider->GetOwner();

	if (collidedObject->GetName() == L"Missile(Player)")
	{
		CEventManager::GetInstance()->DeleteObject(this);
	}
}

void CMonster::OnCollision(CCollider* collidedCollider)
{
}

void CMonster::OnCollisionExit(CCollider* collidedCollider)
{
}

void CMonster::Update()
{
	Vec2 position = GetPosition();

	// ���� �������� �ð� �� m_speed ��ŭ �̵�
	position.m_x += m_direction * m_speed * DT;

	float dist = abs(m_centerPosition.m_x - position.m_x) - m_maxDistance;

	if (dist > 0.0f)
	{
		m_direction = -m_direction;
		position.m_x += m_direction * dist;
	}

	SetPosition(position);
}

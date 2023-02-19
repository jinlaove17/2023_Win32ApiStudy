#include "pch.h"
#include "Monster.h"

#include "TimeManager.h"
#include "EventManager.h"

#include "Collider.h"

#include "StateMachine.h"

#include "MonsterStates.h"

CMonster::CMonster() :
	m_info()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.0f, 40.0f));

	// 생성시에는 Idle 상태로 시작한다.
	CreateStateMachine();
	GetStateMachine()->SetCurrentState(CMonsterIdleState::GetInstance());
}

CMonster::~CMonster()
{
}

const MonsterInfo& CMonster::GetInfo()
{
	return m_info;
}

void CMonster::SetHealth(float health)
{
	if (health < 0)
	{
		health = 0;
	}

	m_info.m_health = health;
}

float CMonster::GetHealth()
{
	return m_info.m_health;
}

void CMonster::SetSpeed(float speed)
{
	m_info.m_speed = speed;
}

float CMonster::GetSpeed()
{
	return m_info.m_speed;
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

void CMonster::SetInfo(const MonsterInfo& info)
{
	m_info = info;
}

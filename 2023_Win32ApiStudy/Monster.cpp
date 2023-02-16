#include "pch.h"
#include "Monster.h"

#include "TimeManager.h"
#include "EventManager.h"

#include "Collider.h"

#include "AI.h"

#include "IdleState.h"

CMonster::CMonster() :
	m_info(),
	m_AI()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.0f, 40.0f));
}

CMonster::~CMonster()
{
	if (m_AI != nullptr)
	{
		delete m_AI;
	}
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

void CMonster::CreateAI()
{
	if (m_AI == nullptr)
	{
		m_AI = new CAI();
		m_AI->m_owner = this;
	}
}

CAI* CMonster::GetAI()
{
	return m_AI;
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
	m_AI->Update();
}

void CMonster::SetInfo(const MonsterInfo& info)
{
	m_info = info;
}

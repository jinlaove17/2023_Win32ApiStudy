#include "pch.h"
#include "MonsterStates.h"

#include "TimeManager.h"
#include "SceneManager.h"
#include "EventManager.h"

#include "Scene.h"

#include "Monster.h"

CMonsterIdleState::CMonsterIdleState()
{
}

CMonsterIdleState::~CMonsterIdleState()
{
}

void CMonsterIdleState::Enter(CObject* object)
{
}

void CMonsterIdleState::Exit(CObject* object)
{
}

void CMonsterIdleState::Update(CObject* object)
{
	//CMonster* monster = (CMonster*)object;
	//CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	//CObject* target = currentScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];

	//const Vec2& targetPosition = target->GetPosition();
	//const Vec2& monsterPosition = monster->GetPosition();
	//Vec2 diff = targetPosition - monsterPosition;

	//// 플레이어의 위치를 체크하여 범위 안에 들어오면 Trace 상태로 전환한다.
	//if (diff.Length() <= monster->GetInfo().m_recogRange)
	//{
	//	CEventManager::GetInstance()->ChangeState(monster, CMonsterTraceState::GetInstance());
	//}
}



CMonsterTraceState::CMonsterTraceState()
{
}

CMonsterTraceState::~CMonsterTraceState()
{
}

void CMonsterTraceState::Enter(CObject* object)
{
}

void CMonsterTraceState::Exit(CObject* object)
{
}

void CMonsterTraceState::Update(CObject* object)
{
	//CMonster* monster = (CMonster*)object;
	//CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	//CObject* target = currentScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];

	//const Vec2& targetPosition = target->GetPosition();
	//Vec2 monsterPosition = monster->GetPosition();
	//Vec2 diff = targetPosition - monsterPosition;
	//float len = diff.Length();

	//// 플레이어의 위치를 체크하여 범위를 벗어나면 Idle 상태로 변경한다.
	//if (len > monster->GetInfo().m_recogRange)
	//{
	//	CEventManager::GetInstance()->ChangeState(monster, CMonsterIdleState::GetInstance());
	//}
	//else if (len > 0.0f)
	//{
	//	monsterPosition += diff.Normalize() * monster->GetInfo().m_speed * DT;
	//	monster->SetPosition(monsterPosition);
	//}
}

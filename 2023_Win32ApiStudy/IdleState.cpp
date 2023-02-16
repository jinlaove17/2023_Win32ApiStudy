#include "pch.h"
#include "IdleState.h"

#include "SceneManager.h"
#include "EventManager.h"

#include "Scene.h"

#include "Monster.h"

#include "AI.h"

CIdleState::CIdleState() : CState(STATE_TYPE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}

void CIdleState::Update()
{
	// 플레이어의 위치를 체크하여 범위 안에 들어오면 추적상태로 전환한다.
	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	CObject* target = currentScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];
	CAI* ai = GetAI();
	CMonster* monster = ai->GetOwner();

	const Vec2& targetPosition = target->GetPosition();
	const Vec2& monsterPosition = monster->GetPosition();
	Vec2 diff = targetPosition - monsterPosition;

	// 플레이어가 몬스터의 인식범위 안에 진입한 경우
	if (diff.Length() <= monster->GetInfo().m_recogRange)
	{
		CEventManager::GetInstance()->ChangeAIState(ai, STATE_TYPE::TRACE);
	}
}

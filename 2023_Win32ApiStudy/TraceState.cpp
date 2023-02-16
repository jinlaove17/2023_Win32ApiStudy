#include "pch.h"
#include "TraceState.h"

#include "TimeManager.h"
#include "SceneManager.h"
#include "EventManager.h"

#include "Scene.h"

#include "Monster.h"

#include "AI.h"

CTraceState::CTraceState() : CState(STATE_TYPE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

void CTraceState::Update()
{
	// 플레이어의 위치를 체크하여 범위 안에 들어오면 추적상태로 전환한다.
	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	CObject* target = currentScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];
	CAI* ai = GetAI();
	CMonster* monster = ai->GetOwner();

	const Vec2& targetPosition = target->GetPosition();
	Vec2 monsterPosition = monster->GetPosition();
	Vec2 diff = targetPosition - monsterPosition;
	float len = diff.Length();

	// 플레이어가 몬스터의 인식범위를 벗어난 경우
	if (len > monster->GetInfo().m_recogRange)
	{
		CEventManager::GetInstance()->ChangeAIState(ai, STATE_TYPE::IDLE);
	}
	else if (len > 0.0f)
	{
		monsterPosition += diff.Normalize() * monster->GetInfo().m_speed * DT;
		monster->SetPosition(monsterPosition);
	}
}

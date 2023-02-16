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
	// �÷��̾��� ��ġ�� üũ�Ͽ� ���� �ȿ� ������ �������·� ��ȯ�Ѵ�.
	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	CObject* target = currentScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];
	CAI* ai = GetAI();
	CMonster* monster = ai->GetOwner();

	const Vec2& targetPosition = target->GetPosition();
	Vec2 monsterPosition = monster->GetPosition();
	Vec2 diff = targetPosition - monsterPosition;
	float len = diff.Length();

	// �÷��̾ ������ �νĹ����� ��� ���
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

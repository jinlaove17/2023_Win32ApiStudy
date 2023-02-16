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
	// �÷��̾��� ��ġ�� üũ�Ͽ� ���� �ȿ� ������ �������·� ��ȯ�Ѵ�.
	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	CObject* target = currentScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];
	CAI* ai = GetAI();
	CMonster* monster = ai->GetOwner();

	const Vec2& targetPosition = target->GetPosition();
	const Vec2& monsterPosition = monster->GetPosition();
	Vec2 diff = targetPosition - monsterPosition;

	// �÷��̾ ������ �νĹ��� �ȿ� ������ ���
	if (diff.Length() <= monster->GetInfo().m_recogRange)
	{
		CEventManager::GetInstance()->ChangeAIState(ai, STATE_TYPE::TRACE);
	}
}

#include "pch.h"
#include "TitleScene.h"

#include "Core.h"

#include "InputManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"

#include "Player.h"
#include "Monster.h"

CTitleScene::CTitleScene()
{
	SetName(L"TitleScene");
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Enter()
{
	// 오브젝트 추가
	CObject* object = new CPlayer();

	object->SetName(L"Player");
	object->SetPosition(Vec2(640.0f, 384.0f));
	object->SetScale(Vec2(100.0f, 100.0f));

	AddObject(GROUP_TYPE::PLAYER, object);

	// 카메라 포커싱 설정
	Vec2 resolution = CCore::GetInstance()->GetResolution();

	// 초기 위치는 해상도의 정중앙이다.
	CCamera::GetInstance()->SetFinalLookAt(resolution / 2.0f);
	//CCamera::GetInstance()->SetTarget(object);

	float term = (resolution.m_x - 2 * 200.0f) / 4.0f;

	for (int i = 0; i < 5; ++i)
	{
		CMonster* monster = new CMonster();

		monster->SetName(L"Monster");
		monster->SetPosition(Vec2(200.0f + (float)term * i, 50.0f));
		monster->SetScale(Vec2(50.0f, 50.0f));
		monster->SetCenterPosition(monster->GetPosition());

		AddObject(GROUP_TYPE::MONSTER, monster);
	}

	// 그룹 간 충돌 설정
	CCollisionManager::GetInstance()->SetCollisionGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->SetCollisionGroup(GROUP_TYPE::PLAYER_PROJ, GROUP_TYPE::MONSTER);
}

void CTitleScene::Exit()
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		DeleteGroupObject((GROUP_TYPE)i);
	}

	CCollisionManager::GetInstance()->ResetCollisionGroup();
}

void CTitleScene::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		CEventManager::GetInstance()->ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBUTTON))
	{
		Vec2 finalLookAt = CCamera::GetInstance()->ScreenToWorld(CURSOR);

		CCamera::GetInstance()->SetFinalLookAt(finalLookAt);
	}
}

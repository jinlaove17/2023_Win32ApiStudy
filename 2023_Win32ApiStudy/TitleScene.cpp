#include "pch.h"
#include "TitleScene.h"

#include "Core.h"

#include "InputManager.h"
#include "CollisionManager.h"
#include "EventManager.h"

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

	object->SetPosition(Vec2(640.0f, 384.0f));
	object->SetScale(Vec2(100.0f, 100.0f));

	AddObject(GROUP_TYPE::PLAYER, object);

	object = object->Clone(); //new CPlayer(*(CPlayer*)object);
	object->SetPosition(Vec2(740.0f, 384.0f));
	object->SetScale(Vec2(100.0f, 100.0f));

	AddObject(GROUP_TYPE::PLAYER, object);

	Vec2 resolution = CCore::GetInstance()->GetResolution();
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
}

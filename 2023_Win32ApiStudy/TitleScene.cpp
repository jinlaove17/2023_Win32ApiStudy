#include "pch.h"
#include "TitleScene.h"

#include "Core.h"

#include "InputManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"

#include "Player.h"
#include "Ground.h"

#include "MonsterFactory.h"

CTitleScene::CTitleScene()
{
	SetName(L"TitleScene");
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::SaveData()
{
}

void CTitleScene::LoadData()
{
}

void CTitleScene::Enter()
{
	// ������Ʈ �߰�
	CObject* object = new CPlayer();

	object->SetName(L"Player");
	object->SetPosition(Vec2(640.0f, 384.0f));
	object->SetScale(Vec2(100.0f, 100.0f));

	AddObject(GROUP_TYPE::PLAYER, object);

	// ī�޶� ��Ŀ�� ����
	Vec2 resolution = CCore::GetInstance()->GetResolution();

	// �ʱ� ��ġ�� �ػ��� ���߾��̴�.
	CCamera::GetInstance()->SetFinalLookAt(resolution / 2.0f);
	CCamera::GetInstance()->SetTarget(object);

	// ���� ����
	object = new CGround();
	object->SetPosition(Vec2(640.0f, 584.0f));
	object->SetScale(Vec2(300.0f, 100.0f));

	AddObject(GROUP_TYPE::GROUND, object);

	// ���� ����
	CMonster* monster = CMonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, Vec2(resolution.m_x / 2.0f, resolution.m_y / 2.0f - 250.0f));

	AddObject(GROUP_TYPE::MONSTER, monster);

	// �׷� �� �浹 ����
	CCollisionManager::GetInstance()->SetCollisionGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionManager::GetInstance()->SetCollisionGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->SetCollisionGroup(GROUP_TYPE::PLAYER_PROJ, GROUP_TYPE::MONSTER);

	// ���̵� ȿ�� ����
	CCamera::GetInstance()->AddEffect(CAM_EFFECT::FADE_OUT, 1.0f);
	CCamera::GetInstance()->AddEffect(CAM_EFFECT::FADE_IN, 1.0f);
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

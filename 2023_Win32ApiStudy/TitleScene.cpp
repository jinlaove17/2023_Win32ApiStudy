#include "pch.h"
#include "TitleScene.h"

#include "Core.h"

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

	Vec2 resolution = CCore::GetInstance()->GetResolution();
	float term = (resolution.m_x - 2 * 200.0f) / 4.0f;

	for (int i = 0; i < 5; ++i)
	{
		CMonster* monster = new CMonster();

		monster->SetPosition(Vec2(200.0f + (float)term * i, 50.0f));
		monster->SetScale(Vec2(50.0f, 50.0f));
		monster->SetCenterPosition(monster->GetPosition());

		AddObject(GROUP_TYPE::MONSTER, monster);
	}
}

void CTitleScene::Exit()
{
}

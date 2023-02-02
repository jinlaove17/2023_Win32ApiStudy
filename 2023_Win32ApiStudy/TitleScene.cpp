#include "pch.h"
#include "TitleScene.h"

#include "Object.h"

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
	CObject* object = new CObject();

	object->SetPosition(Vec2(640.0f, 384.0f));
	object->SetScale(Vec2(100.0f, 100.0f));

	AddObject(GROUP_TYPE::DEFAULT, object);
}

void CTitleScene::Exit()
{
}

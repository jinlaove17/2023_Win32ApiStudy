#include "pch.h"
#include "ToolScene.h"

#include "InputManager.h"
#include "EventManager.h"

CToolScene::CToolScene()
{
}

CToolScene::~CToolScene()
{
}

void CToolScene::Enter()
{
}

void CToolScene::Exit()
{
}

void CToolScene::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		CEventManager::GetInstance()->ChangeScene(SCENE_TYPE::TITLE);
	}
}

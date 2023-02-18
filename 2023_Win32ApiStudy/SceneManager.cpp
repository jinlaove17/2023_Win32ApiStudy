#include "pch.h"
#include "SceneManager.h"

#include "ToolScene.h"
#include "TitleScene.h"

CSceneManager::CSceneManager() :
	m_scenes(),
	m_currentScene()
{
}

CSceneManager::~CSceneManager()
{
	for (int i = 0; i < (int)SCENE_TYPE::COUNT; ++i)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
		}
	}
}

void CSceneManager::ChangeScene(SCENE_TYPE scene)
{
	m_currentScene->Exit();
	m_currentScene = m_scenes[(int)scene];
	m_currentScene->Enter();
}

void CSceneManager::Init()
{
	// ¾À »ý¼º
	m_scenes[(int)SCENE_TYPE::TOOL] = new CToolScene();
	m_scenes[(int)SCENE_TYPE::TOOL]->SetName(L"ToolScene");
	m_scenes[(int)SCENE_TYPE::TITLE] = new CTitleScene();
	m_scenes[(int)SCENE_TYPE::TITLE]->SetName(L"TitleScene");

	// ÇöÀç ¾À ¼³Á¤
	m_currentScene = m_scenes[(int)SCENE_TYPE::TITLE];
	m_currentScene->Enter();
}

CScene* CSceneManager::GetCurrentScene()
{
	return m_currentScene;
}

void CSceneManager::Update()
{
	m_currentScene->Update();
	m_currentScene->LateUpdate();
}

void CSceneManager::Render(HDC hDC)
{
	m_currentScene->Render(hDC);
}

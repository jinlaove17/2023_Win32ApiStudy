#include "pch.h"
#include "SceneManager.h"

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

void CSceneManager::Init()
{
	// �� ����
	m_scenes[(int)SCENE_TYPE::TITLE] = new CTitleScene();

	// ���� �� ����
	m_currentScene = m_scenes[(int)SCENE_TYPE::TITLE];
	m_currentScene->Enter();
}

void CSceneManager::Update()
{
	m_currentScene->Update();
}

void CSceneManager::Render(HDC hDC)
{
	m_currentScene->Render(hDC);
}

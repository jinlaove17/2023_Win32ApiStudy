#include "pch.h"
#include "Scene.h"

#include "Object.h"

CScene::CScene() :
	m_name(),
	m_objects()
{
}

CScene::~CScene()
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		for (int j = 0; j < m_objects[i].size(); ++j)
		{
			if (m_objects[i][j] != nullptr)
			{
				delete m_objects[i][j];
			}
		}

		m_objects[i].clear();
	}
}

void CScene::SetName(const wstring& name)
{
	m_name = name;
}

const wstring& CScene::GetName()
{
	return m_name;
}

void CScene::AddObject(GROUP_TYPE group, CObject* object)
{
	m_objects[(int)group].push_back(object);
}

void CScene::Update()
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		for (int j = 0; j < m_objects[i].size(); ++j)
		{
			m_objects[i][j]->Update();
		}
	}
}

void CScene::Render(HDC hDC)
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		for (int j = 0; j < m_objects[i].size(); ++j)
		{
			m_objects[i][j]->Render(hDC);
		}
	}
}

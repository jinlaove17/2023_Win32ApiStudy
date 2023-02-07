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

const vector<CObject*>& CScene::GetGroupObject(GROUP_TYPE group)
{
	return m_objects[(int)group];
}

void CScene::Update()
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		for (int j = 0; j < m_objects[i].size(); ++j)
		{
			if (m_objects[i][j]->IsActive() && !m_objects[i][j]->IsDeleted())
			{
				m_objects[i][j]->Update();
			}
		}
	}
}

void CScene::LateUpdate()
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		for (int j = 0; j < m_objects[i].size(); ++j)
		{
			if (m_objects[i][j]->IsActive() && !m_objects[i][j]->IsDeleted())
			{
				m_objects[i][j]->LateUpdate();
			}
		}
	}
}

void CScene::Render(HDC hDC)
{
	for (int i = 0; i < (int)GROUP_TYPE::COUNT; ++i)
	{
		for (auto iter = m_objects[i].begin(); iter != m_objects[i].end(); )
		{
			CObject* object = *iter;

			// 삭제 예정된 오브젝트를 벡터에서 제거한다.
			if (object->IsDeleted())
			{
				iter = m_objects[i].erase(iter);
			}
			else if (object->IsActive())
			{
				object->Render(hDC);
				++iter;
			}
		}
	}
}

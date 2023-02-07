#include "pch.h"
#include "EventManager.h"

#include "SceneManager.h"

#include "Scene.h"

#include "Object.h"

CEventManager::CEventManager() :
	m_eventQueue(),
	m_deletedObjectQueue()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::CreateObject(GROUP_TYPE group, CObject* object)
{
	m_eventQueue.push([group, object]()
		{ 
			CSceneManager::GetInstance()->GetCurrentScene()->AddObject(group, object);
		});
}

void CEventManager::DeleteObject(CObject* object)
{
	m_eventQueue.push([object, this]()
		{
			object->SetActive(false);
			object->SetDeleted(true);

			this->m_deletedObjectQueue.push(object);
		});
}

void CEventManager::Update()
{
	// ���� �����ӿ� ��ϵ� ������ ������Ʈ�� ��� �����Ѵ�.
	while (!m_deletedObjectQueue.empty())
	{
		delete m_deletedObjectQueue.front();
		m_deletedObjectQueue.pop();
	}

	while (!m_eventQueue.empty())
	{
		m_eventQueue.front()();
		m_eventQueue.pop();
	}
}

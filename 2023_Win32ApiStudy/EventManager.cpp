#include "pch.h"
#include "EventManager.h"

#include "SceneManager.h"
#include "UIManager.h"

#include "Scene.h"

#include "Object.h"

#include "StateMachine.h"

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
	assert(object != nullptr);

	m_eventQueue.push(
		[=]()
		{
			CSceneManager::GetInstance()->GetCurrentScene()->AddObject(group, object);
		});
}

void CEventManager::DeleteObject(CObject* object)
{
	assert(object != nullptr);

	m_eventQueue.push(
		[=]()
		{
			object->SetActive(false);
			object->SetDeleted(true);

			this->m_deletedObjectQueue.push(object);
		});
}

void CEventManager::ChangeScene(SCENE_TYPE scene)
{
	m_eventQueue.push(
		[=]()
		{
			// ���� �����ϴ� �̺�Ʈ�� ����Ǹ�, ���� �̺�Ʈ�� ó���� �ʿ䰡 �����Ƿ� ť�� ����� 1�� �����.(��ٷ� Update���� pop() �� ���̱� ������)
			while (m_eventQueue.size() > 1)
			{
				m_eventQueue.pop();
			}

			CUIManager::GetInstance()->SetFocusedUI(nullptr);
			CSceneManager::GetInstance()->ChangeScene(scene);
		});
}

void CEventManager::ChangeState(CObject* object, CState* state)
{
	assert((object != nullptr) && (state != nullptr));

	m_eventQueue.push(
		[=]()
		{
			object->GetStateMachine()->ChangeState(state);
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

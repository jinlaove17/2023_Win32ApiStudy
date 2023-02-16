#include "pch.h"
#include "EventManager.h"

#include "SceneManager.h"
#include "UIManager.h"

#include "Scene.h"

#include "Object.h"

#include "AI.h"

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
	m_eventQueue.push(
		[=]()
		{
			CSceneManager::GetInstance()->GetCurrentScene()->AddObject(group, object);
		});
}

void CEventManager::DeleteObject(CObject* object)
{
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
			// 씬을 변경하는 이벤트가 실행되면, 이후 이벤트는 처리할 필요가 없으므로 큐의 사이즈를 1로 만든다.(곧바로 Update에서 pop() 될 것이기 때문에)
			while (m_eventQueue.size() > 1)
			{
				m_eventQueue.pop();
			}

			CUIManager::GetInstance()->SetFocusedUI(nullptr);
			CSceneManager::GetInstance()->ChangeScene(scene);
		});
}

void CEventManager::ChangeAIState(CAI* AI, STATE_TYPE state)
{
	m_eventQueue.push(
		[=]()
		{
			AI->ChangeState(state);
		});
}

void CEventManager::Update()
{
	// 이전 프레임에 등록된 삭제할 오브젝트를 모두 제거한다.
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

#pragma once

class CObject;
class CStateMachine;
class CState;

class CEventManager : public CSingleton<CEventManager>
{
	friend class CSingleton;
	
private:
	queue<Event>    m_eventQueue;
	queue<CObject*> m_deletedObjectQueue;

private:
	CEventManager();
	~CEventManager();

public:
	void CreateObject(GROUP_TYPE group, CObject* object);
	void DeleteObject(CObject* object);
	void ChangeScene(SCENE_TYPE scene);
	void ChangeState(CObject* object, CState* state);

	void Update();
};

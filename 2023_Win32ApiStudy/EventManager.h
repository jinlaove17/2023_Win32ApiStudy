#pragma once

class CObject;
class CAI;

class CEventManager
{
	SINGLETON(CEventManager)

private:
	queue<Event>    m_eventQueue;
	queue<CObject*> m_deletedObjectQueue;

public:
	void CreateObject(GROUP_TYPE group, CObject* object);
	void DeleteObject(CObject* object);
	void ChangeScene(SCENE_TYPE scene);
	void ChangeAIState(CAI* AI, STATE_TYPE state);

	void Update();
};

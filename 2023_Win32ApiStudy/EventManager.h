#pragma once

class CObject;
class CAI;

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
	void ChangeAIState(CAI* AI, STATE_TYPE state);

	void Update();
};

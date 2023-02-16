#pragma once

class CState;
class CMonster;

class CAI
{
	friend class CMonster;

private:
	unordered_map<STATE_TYPE, CState*> m_states;
	CState*							   m_currentState;

	CMonster*						   m_owner;

public:
	CAI();
	~CAI();

	void AddState(STATE_TYPE stateType);
	CState* GetState(STATE_TYPE stateType);

	void SetCurrentState(STATE_TYPE stateType);
	CState* GetCurrentState();

	CMonster* GetOwner();

	void ChangeState(STATE_TYPE stateType);

	void Update();
};

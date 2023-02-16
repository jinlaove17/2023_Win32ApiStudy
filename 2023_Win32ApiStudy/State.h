#pragma once

class CAI;

class CState
{
	friend class CAI;

private:
	STATE_TYPE m_state;

	CAI*	   m_AI;

public:
	CState(STATE_TYPE state);
	virtual ~CState();

	STATE_TYPE GetType();
	CAI* GetAI();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update() = 0;
};

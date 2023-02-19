#pragma once
#include "Component.h"

class CState;

class CStateMachine : public CComponent
{
	friend class CObject;

private:
	CState*  m_previousState;
	CState*  m_currentState;

private:
	CStateMachine();
	~CStateMachine();

public:
	void SetCurrentState(CState* state);
	CState* GetPreviousState();

	CState* GetCurrentState();

	void ChangeState(CState* state);

	virtual void Update();

	virtual void Render(HDC hDC);
};

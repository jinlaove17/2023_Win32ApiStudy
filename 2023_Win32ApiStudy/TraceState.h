#pragma once
#include "State.h"

class CTraceState : public CState
{
public:
	CTraceState();
	virtual ~CTraceState();

	virtual void Enter();
	virtual void Exit();

	virtual void Update();
};

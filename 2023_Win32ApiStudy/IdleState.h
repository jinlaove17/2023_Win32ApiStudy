#pragma once
#include "State.h"

class CIdleState : public CState
{
public:
	CIdleState();
	virtual ~CIdleState();

	virtual void Enter();
	virtual void Exit();

	virtual void Update();
};

#pragma once
#include "State.h"

class CPlayerIdleState : public CState, public CSingleton<CPlayerIdleState>
{
	friend class CSingleton;

private:
	CPlayerIdleState();
	virtual ~CPlayerIdleState();

public:
	virtual void Enter(CObject* object);
	virtual void Exit(CObject* object);

	virtual void Update(CObject* object);
};

class CPlayerJumpState : public CState, public CSingleton<CPlayerJumpState>
{
	friend class CSingleton;

private:
	CPlayerJumpState();
	virtual ~CPlayerJumpState();

public:
	virtual void Enter(CObject* object);
	virtual void Exit(CObject* object);

	virtual void Update(CObject* object);
};

class CPlayerWalkState : public CState, public CSingleton<CPlayerWalkState>
{
	friend class CSingleton;

private:
	CPlayerWalkState();
	virtual ~CPlayerWalkState();

public:
	virtual void Enter(CObject* object);
	virtual void Exit(CObject* object);

	virtual void Update(CObject* object);
};

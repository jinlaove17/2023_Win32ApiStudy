#pragma once
#include "State.h"

class CMonsterIdleState : public CState, public CSingleton<CMonsterIdleState>
{
	friend class CSingleton;

private:
	CMonsterIdleState();
	virtual ~CMonsterIdleState();

public:
	virtual void Enter(CObject* object);
	virtual void Exit(CObject* object);

	virtual void Update(CObject* object);
};

class CMonsterTraceState : public CState, public CSingleton<CMonsterTraceState>
{
	friend class CSingleton;

private:
	CMonsterTraceState();
	virtual ~CMonsterTraceState();

public:
	virtual void Enter(CObject* object);
	virtual void Exit(CObject* object);

	virtual void Update(CObject* object);
};

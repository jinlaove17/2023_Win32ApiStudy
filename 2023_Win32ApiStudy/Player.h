#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void Update();

private:
	void CreateMissile();
};

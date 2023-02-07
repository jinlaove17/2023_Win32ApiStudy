#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

	CLONE(CPlayer);

	virtual void Update();

	virtual void Render(HDC hDC);

private:
	void CreateMissile();
};

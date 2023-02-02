#pragma once
#include "Object.h"

class CMissile : public CObject
{
private:
	float m_direction;

public:
	CMissile();
	virtual ~CMissile();

	void SetDirection(float direction);
	float GetDirection();

	virtual void Update();
	virtual void Render(HDC hDC);
};

#pragma once
#include "Object.h"

class CMissile : public CObject
{
private:
	Vec2 m_direction;

public:
	CMissile();
	virtual ~CMissile();

	void SetDirection(const Vec2& direction);
	const Vec2& GetDirection();

	virtual void Update();
	virtual void Render(HDC hDC);
};

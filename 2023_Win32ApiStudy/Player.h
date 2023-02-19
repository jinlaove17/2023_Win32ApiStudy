#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	int m_direction; // 플레이어 캐릭터가 바라보는 방향(음수: Left, 양수: Right)

public:
	CPlayer();
	virtual ~CPlayer();

	CLONE(CPlayer);

	void SetDirection(int direction);
	int GetDirection();

	void CreateMissile();

	virtual void Render(HDC hDC);
};

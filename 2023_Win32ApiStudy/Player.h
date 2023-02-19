#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	int m_direction; // �÷��̾� ĳ���Ͱ� �ٶ󺸴� ����(����: Left, ���: Right)

public:
	CPlayer();
	virtual ~CPlayer();

	CLONE(CPlayer);

	void SetDirection(int direction);
	int GetDirection();

	void CreateMissile();

	virtual void Render(HDC hDC);
};

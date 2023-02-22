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

	virtual void OnCollisionEnter(CCollider* collidedCollider);
	virtual void OnCollision(CCollider* collidedCollider);
	virtual void OnCollisionExit(CCollider* collidedCollider);

	virtual void Render(HDC hDC);
};

#pragma once
#include "Object.h"

class CGround : public CObject
{
private:

public:
	CGround();
	virtual ~CGround();

	CLONE(CGround);

	virtual void OnCollisionEnter(CCollider* collidedCollider); // �浹 ���� �� ȣ��
	virtual void OnCollision(CCollider* collidedCollider);      // �浹 ���� �� ȣ��
	virtual void OnCollisionExit(CCollider* collidedCollider);  // �浹 ���� �� ȣ��
};

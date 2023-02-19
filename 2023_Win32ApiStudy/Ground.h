#pragma once
#include "Object.h"

class CGround : public CObject
{
private:

public:
	CGround();
	virtual ~CGround();

	CLONE(CGround);

	virtual void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	virtual void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	virtual void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출
};

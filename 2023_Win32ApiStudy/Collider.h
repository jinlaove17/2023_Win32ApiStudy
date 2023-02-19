#pragma once
#include "Component.h"

class CCollider : public CComponent
{
	friend class CObject;

private:
	static UINT m_nextID;

	UINT	    m_id;             // 고유한 값

	Vec2		m_position;		  // owner의 위치에서 offset 만큼 떨어진 최종 위치
	Vec2		m_scale;
	
	Vec2		m_offset;		  // owner로부터 상대적인 위치

	UINT		m_collisionCount; // 현재 충돌 중인 충돌체의 개수

private:
	CCollider();
	CCollider(const CCollider& rhs);
	~CCollider();

public:
	CCollider& operator =(const CCollider& rhs) = delete;

public:
	UINT GetID();

	const Vec2& GetPosition();

	void SetScale(const Vec2& scale);
	const Vec2& GetScale();

	void SetOffset(const Vec2& offset);
	const Vec2& GetOffset();

	void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출

	virtual void Update();

	virtual void Render(HDC hDC);
};

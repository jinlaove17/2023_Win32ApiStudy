#pragma once

class CObject;

class CCollider
{
	friend class CObject;

private:
	static UINT m_nextID;

	UINT	    m_id;             // 고유한 값
    		                    
	Vec2	    m_offset;         // m_owner의 위치로부터 상대적인 위치
	Vec2	    m_scale;          // 충돌체의 크기

	UINT		m_collisionCount; // 현재 충돌 중인 충돌체의 개수

	CObject*    m_owner;

private:
	CCollider();
	CCollider(const CCollider& rhs);
	~CCollider();

public:
	CCollider& operator =(const CCollider& rhs) = delete;

public:
	UINT GetID();

	void SetOffset(const Vec2& offset);
	const Vec2& GetOffset();

	Vec2 GetPosition();

	void SetScale(const Vec2& scale);
	const Vec2& GetScale();

	CObject* GetOwner();

	void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출

	void Update();

	void Render(HDC hDC);
};

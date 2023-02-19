#pragma once
#include "Component.h"

class CCollider : public CComponent
{
	friend class CObject;

private:
	static UINT m_nextID;

	UINT	    m_id;             // ������ ��

	Vec2		m_position;		  // owner�� ��ġ���� offset ��ŭ ������ ���� ��ġ
	Vec2		m_scale;
	
	Vec2		m_offset;		  // owner�κ��� ������� ��ġ

	UINT		m_collisionCount; // ���� �浹 ���� �浹ü�� ����

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

	void OnCollisionEnter(CCollider* collidedCollider); // �浹 ���� �� ȣ��
	void OnCollision(CCollider* collidedCollider);      // �浹 ���� �� ȣ��
	void OnCollisionExit(CCollider* collidedCollider);  // �浹 ���� �� ȣ��

	virtual void Update();

	virtual void Render(HDC hDC);
};

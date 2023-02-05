#pragma once

class CObject;

class CCollider
{
	friend class CObject;

private:
	static UINT m_nextID;

	UINT	    m_id;             // ������ ��
			    		          
	CObject*    m_owner;          
			    		          
	Vec2	    m_offset;         // m_owner�� ��ġ�κ��� ������� ��ġ
	Vec2	    m_scale;          // �浹ü�� ũ��

	UINT		m_collisionCount; // ���� �浹 ���� �浹ü�� ����

private:
	CCollider();
	CCollider(const CCollider& rhs) = delete;
	~CCollider();

public:
	CCollider& operator =(const CCollider& rhs) = delete;

public:
	UINT GetID();

	CObject* GetOwner();

	void SetOffset(const Vec2& offset);
	const Vec2& GetOffset();

	Vec2 GetPosition();

	void SetScale(const Vec2& scale);
	const Vec2& GetScale();

	void OnCollisionEnter(CCollider* collidedCollider); // �浹 ���� �� ȣ��
	void OnCollision(CCollider* collidedCollider);      // �浹 ���� �� ȣ��
	void OnCollisionExit(CCollider* collidedCollider);  // �浹 ���� �� ȣ��

	void Update();

	void Render(HDC hDC);
};
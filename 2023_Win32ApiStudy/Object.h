#pragma once

class CTexture;
class CCollider;
class CAnimator;

class CObject
{
private:
	bool	   m_isActive;
	bool       m_isDeleted;

	wstring    m_name;

	Vec2       m_position;
	Vec2       m_scale;
			   
	CTexture*  m_texture;
	CCollider* m_collider;
	CAnimator* m_animator;

public:
	CObject();
	CObject(const CObject& rhs);
	virtual ~CObject();

	virtual CObject* Clone() = 0;

	void SetActive(bool isActive);
	bool IsActive();

	void SetDeleted(bool isDeleted);
	bool IsDeleted();

	void SetName(const wstring& name);
	const wstring& GetName();

	void SetPosition(const Vec2& position);
	const Vec2& GetPosition();

	void SetScale(const Vec2& scale);
	const Vec2& GetScale();

	void SetTexture(CTexture* texture);
	CTexture* GetTexture();

	void CreateCollider();
	CCollider* GetCollider();

	void CreateAnimator();
	CAnimator* GetAnimator();

	virtual void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	virtual void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	virtual void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출

	virtual void Update() = 0;
	virtual void LateUpdate() final; // final: 자식 객체에서 더이상 override 할 수 없도록 제한한다.

	virtual void Render(HDC hDC);
	void ComponentRender(HDC hDC);
};

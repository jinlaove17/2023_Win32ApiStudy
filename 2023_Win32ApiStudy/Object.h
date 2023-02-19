#pragma once

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;
class CStateMachine;

class CObject
{
private:
	bool		     m_isActive;
	bool		     m_isDeleted;
				     
	wstring		     m_name;
				     
	Vec2		     m_position;
	Vec2		     m_localPosition;
	Vec2		     m_scale;
				     
	CTexture*	     m_texture;

	CCollider*	     m_collider;
	CAnimator*	     m_animator;
	CRigidBody*      m_rigidBody;
	CStateMachine*	 m_stateMachine;

	CObject*         m_parent;
	vector<CObject*> m_children;

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

	void SetLocalPosition(const Vec2& localPosition);
	const Vec2& GetLocalPosition();

	void SetScale(const Vec2& scale);
	const Vec2& GetScale();

	void SetTexture(CTexture* texture);
	CTexture* GetTexture();

	void CreateCollider();
	CCollider* GetCollider();

	void CreateAnimator();
	CAnimator* GetAnimator();

	void CreateRigidBody();
	CRigidBody* GetRigidBody();

	void CreateStateMachine();
	CStateMachine* GetStateMachine();

	CObject* GetParent();

	void AddChild(CObject* object);
	const vector<CObject*>& GetChildren();

	virtual void OnCollisionEnter(CCollider* collidedCollider); // 충돌 진입 시 호출
	virtual void OnCollision(CCollider* collidedCollider);      // 충돌 중일 시 호출
	virtual void OnCollisionExit(CCollider* collidedCollider);  // 충돌 종료 시 호출

	virtual void Update();
	virtual void LateUpdate();

	virtual void Render(HDC hDC);

protected:
	void UpdateChildren();
	void LateUpdateChildren();

	void RenderComponent(HDC hDC);
	void RenderChildren(HDC hDC);
};

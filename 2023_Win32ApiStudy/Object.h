#pragma once

class CTexture;
class CCollider;

class CObject
{
private:
	wstring    m_name;

	Vec2       m_position;
	Vec2       m_scale;
			   
	CTexture*  m_texture;
	CCollider* m_collider;

public:
	CObject();
	virtual ~CObject();

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

	virtual void OnCollisionEnter(CCollider* collidedCollider); // �浹 ���� �� ȣ��
	virtual void OnCollision(CCollider* collidedCollider);      // �浹 ���� �� ȣ��
	virtual void OnCollisionExit(CCollider* collidedCollider);  // �浹 ���� �� ȣ��

	virtual void Update() = 0;
	virtual void LateUpdate() final; // final: �ڽ� ��ü���� ���̻� override �� �� ������ �����Ѵ�.

	virtual void Render(HDC hDC);
	void ComponentRender(HDC hDC);
};

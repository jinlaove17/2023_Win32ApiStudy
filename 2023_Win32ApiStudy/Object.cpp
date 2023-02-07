#include "pch.h"
#include "Object.h"

#include "Collider.h"

CObject::CObject() :
	m_isActive(true),
	m_isDeleted(),
	m_name(),
	m_position(),
	m_scale(),
	m_texture(),
	m_collider()
{
}

CObject::CObject(const CObject& rhs) :
	m_isActive(rhs.m_isActive),
	m_isDeleted(),
	m_name(rhs.m_name),
	m_position(rhs.m_position),
	m_scale(rhs.m_scale),
	m_texture(rhs.m_texture),
	m_collider()
{
	if (rhs.m_collider != nullptr)
	{
		m_collider = new CCollider(*rhs.m_collider);
		m_collider->m_owner = this;
	}
}

CObject::~CObject()
{
	if (m_collider != nullptr)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}

void CObject::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool CObject::IsActive()
{
	return m_isActive;
}

void CObject::SetDeleted(bool isDeleted)
{
	m_isDeleted = isDeleted;
}

bool CObject::IsDeleted()
{
	return m_isDeleted;
}

void CObject::SetName(const wstring& name)
{
	m_name = name;
}

const wstring& CObject::GetName()
{
	return m_name;
}

void CObject::SetPosition(const Vec2& position)
{
	m_position = position;
}

const Vec2& CObject::GetPosition()
{
	return m_position;
}

void CObject::SetScale(const Vec2& scale)
{
	m_scale = scale;
}

const Vec2& CObject::GetScale()
{
	return m_scale;
}

void CObject::SetTexture(CTexture* texture)
{
	m_texture = texture;
}

CTexture* CObject::GetTexture()
{
	return m_texture;
}

void CObject::CreateCollider()
{
	if (m_collider == nullptr)
	{
		m_collider = new CCollider();
		m_collider->m_owner = this;
	}
}

CCollider* CObject::GetCollider()
{
	return m_collider;
}

void CObject::OnCollisionEnter(CCollider* collidedCollider)
{
}

void CObject::OnCollision(CCollider* collidedCollider)
{
}

void CObject::OnCollisionExit(CCollider* collidedCollider)
{
}

void CObject::LateUpdate()
{
	if (m_collider != nullptr)
	{
		m_collider->Update();
	}
}

void CObject::Render(HDC hDC)
{
	Rectangle(hDC,
		(int)(m_position.m_x - 0.5f * m_scale.m_x),
		(int)(m_position.m_y - 0.5f * m_scale.m_y),
		(int)(m_position.m_x + 0.5f * m_scale.m_x),
		(int)(m_position.m_y + 0.5f * m_scale.m_y));

	ComponentRender(hDC);
}

void CObject::ComponentRender(HDC hDC)
{
	if (m_collider != nullptr)
	{
		m_collider->Render(hDC);
	}
}

#include "pch.h"
#include "Collider.h"

#include "Core.h"

#include "Camera.h"

#include "Object.h"

UINT CCollider::m_nextID = 0;

CCollider::CCollider() :
	m_id(m_nextID++),
	m_offset(),
	m_scale(),
	m_collisionCount(),
	m_owner()
{
}

CCollider::CCollider(const CCollider& rhs) :
	m_id(m_nextID++),
	m_offset(rhs.m_offset),
	m_scale(rhs.m_scale),
	m_collisionCount(),
	m_owner()
{
}

CCollider::~CCollider()
{
}

UINT CCollider::GetID()
{
	return m_id;
}

void CCollider::SetOffset(const Vec2& offset)
{
	m_offset = offset;
}

const Vec2& CCollider::GetOffset()
{
	return m_offset;
}

Vec2 CCollider::GetPosition()
{
	return m_owner->GetPosition() + m_offset;
}

void CCollider::SetScale(const Vec2& scale)
{
	m_scale = scale;
}

const Vec2& CCollider::GetScale()
{
	return m_scale;
}

CObject* CCollider::GetOwner()
{
	return m_owner;
}

void CCollider::OnCollisionEnter(CCollider* collidedCollider)
{
	m_owner->OnCollisionEnter(collidedCollider);
	++m_collisionCount;
}

void CCollider::OnCollision(CCollider* collidedCollider)
{
	m_owner->OnCollision(collidedCollider);
}

void CCollider::OnCollisionExit(CCollider* collidedCollider)
{
	assert(m_collisionCount >= 1);

	m_owner->OnCollisionExit(collidedCollider);
	--m_collisionCount;
}

void CCollider::Update()
{
}

void CCollider::Render(HDC hDC)
{
	CGdiController gdiController(hDC, (m_collisionCount > 0) ? PEN_TYPE::RED : PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW);
	Vec2 finalPosition = CCamera::GetInstance()->WorldToScreen(GetPosition() + m_offset);

	Rectangle(hDC,
		(int)(finalPosition.m_x - 0.5f * m_scale.m_x),
		(int)(finalPosition.m_y - 0.5f * m_scale.m_y),
		(int)(finalPosition.m_x + 0.5f * m_scale.m_x),
		(int)(finalPosition.m_y + 0.5f * m_scale.m_y));
}

#include "pch.h"
#include "Collider.h"

#include "Core.h"

#include "Camera.h"

UINT CCollider::m_nextID = 0;

CCollider::CCollider() :
	m_id(m_nextID++),
	m_position(),
	m_scale(),
	m_offset(),
	m_collisionCount()
{
}

CCollider::CCollider(const CCollider& rhs) :
	m_id(m_nextID++),
	m_position(rhs.m_position),
	m_scale(rhs.m_scale),
	m_offset(rhs.m_offset),
	m_collisionCount()
{
}

CCollider::~CCollider()
{
}

UINT CCollider::GetID()
{
	return m_id;
}

const Vec2& CCollider::GetPosition()
{
	return m_position;
}

void CCollider::SetScale(const Vec2& scale)
{
	m_scale = scale;
}

const Vec2& CCollider::GetScale()
{
	return m_scale;
}

void CCollider::SetOffset(const Vec2& offset)
{
	m_offset = offset;
}

const Vec2& CCollider::GetOffset()
{
	return m_offset;
}

void CCollider::OnCollisionEnter(CCollider* collidedCollider)
{
	GetOwner()->OnCollisionEnter(collidedCollider);
	++m_collisionCount;
}

void CCollider::OnCollision(CCollider* collidedCollider)
{
	GetOwner()->OnCollision(collidedCollider);
}

void CCollider::OnCollisionExit(CCollider* collidedCollider)
{
	assert(m_collisionCount >= 1);

	GetOwner()->OnCollisionExit(collidedCollider);
	--m_collisionCount;
}

void CCollider::Update()
{
	m_position = GetOwner()->GetPosition() + m_offset;
}

void CCollider::Render(HDC hDC)
{
	CGdiController gdiController(hDC, (m_collisionCount > 0) ? PEN_TYPE::RED : PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW);
	Vec2 finalPosition = CCamera::GetInstance()->WorldToScreen(m_position);

	Rectangle(hDC,
		(int)(finalPosition.m_x - 0.5f * m_scale.m_x),
		(int)(finalPosition.m_y - 0.5f * m_scale.m_y),
		(int)(finalPosition.m_x + 0.5f * m_scale.m_x),
		(int)(finalPosition.m_y + 0.5f * m_scale.m_y));
}

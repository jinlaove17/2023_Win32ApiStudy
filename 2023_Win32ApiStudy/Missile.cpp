#include "pch.h"
#include "Missile.h"

#include "TimeManager.h"

#include "Collider.h"

CMissile::CMissile() :
	m_direction()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.0f, 10.0f));
}

CMissile::~CMissile()
{
}

void CMissile::SetDirection(const Vec2& direction)
{
	m_direction = direction;
}

const Vec2& CMissile::GetDirection()
{
	return m_direction;
}

void CMissile::Update()
{
	Vec2 position = GetPosition();

	position.m_x += m_direction.m_x * 600.0f * DT;
	position.m_y += m_direction.m_y * 600.0f * DT;

	SetPosition(position);
}

void CMissile::Render(HDC hDC)
{
	const Vec2& position = GetPosition();
	const Vec2& scale = GetScale();

	Ellipse(hDC,
		(int)(position.m_x - 0.5f * scale.m_x),
		(int)(position.m_y - 0.5f * scale.m_y),
		(int)(position.m_x + 0.5f * scale.m_x),
		(int)(position.m_y + 0.5f * scale.m_y));

	RenderComponent(hDC);
}

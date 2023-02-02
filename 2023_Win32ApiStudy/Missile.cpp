#include "pch.h"
#include "Missile.h"

#include "TimeManager.h"

CMissile::CMissile() :
	m_direction(1.0f)
{
}

CMissile::~CMissile()
{
}

void CMissile::SetDirection(float direction)
{
	m_direction = direction;
}

float CMissile::GetDirection()
{
	return 0.0f;
}

void CMissile::Update()
{
	Vec2 position = GetPosition();

	position.m_y += m_direction * 400.0f * DT;

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
}

#include "pch.h"
#include "Object.h"

CObject::CObject() :
	m_position(),
	m_scale(),
	m_texture()
{
}

CObject::~CObject()
{
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

void CObject::Render(HDC hDC)
{
	Rectangle(hDC,
		(int)(m_position.m_x - 0.5f * m_scale.m_x),
		(int)(m_position.m_y - 0.5f * m_scale.m_y),
		(int)(m_position.m_x + 0.5f * m_scale.m_x),
		(int)(m_position.m_y + 0.5f * m_scale.m_y));
}

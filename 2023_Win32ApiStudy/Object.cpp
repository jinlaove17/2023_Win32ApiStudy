#include "pch.h"
#include "Object.h"

CObject::CObject() :
	m_position(),
	m_scale()
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

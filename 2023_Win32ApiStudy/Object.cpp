#include "pch.h"
#include "Object.h"

#include "TimeManager.h"
#include "InputManager.h"

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

void CObject::Update()
{
	if (CInputManager::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		m_position.m_y -= 300.0f * DT;
	}

	if (CInputManager::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		m_position.m_y += 300.0f * DT;
	}

	if (CInputManager::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		m_position.m_x -= 300.0f * DT;
	}

	if (CInputManager::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		m_position.m_x += 300.0f * DT;
	}
}

void CObject::Render(HDC hDC)
{
	Rectangle(hDC,
		(int)(m_position.m_x - 0.5f * m_scale.m_x),
		(int)(m_position.m_y - 0.5f * m_scale.m_y),
		(int)(m_position.m_x + 0.5f * m_scale.m_x),
		(int)(m_position.m_y + 0.5f * m_scale.m_y));
}

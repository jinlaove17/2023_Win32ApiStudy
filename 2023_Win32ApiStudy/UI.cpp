#include "pch.h"
#include "UI.h"

#include "InputManager.h"
#include "Camera.h"

#include "Collider.h"
#include "Animator.h"

CUI::CUI() :
	m_isFixed(true),
	m_isPressed(),
	m_isCursorOver()
{
}

CUI::CUI(const CUI& rhs) :
	CObject(rhs),
	m_isFixed(rhs.m_isFixed),
	m_isPressed(),
	m_isCursorOver()
{
}

CUI::~CUI()
{
}

void CUI::SetFixed(bool isFixed)
{
	m_isFixed = isFixed;
}

bool CUI::IsFixed()
{
	return m_isFixed;
}

void CUI::SetPressed(bool isPressed)
{
	m_isPressed = isPressed;
}

bool CUI::IsPressed()
{
	return m_isPressed;
}

void CUI::CheckCursorOver()
{
	Vec2 cursor = CURSOR;
	const Vec2& scale = GetScale();

	if (!m_isFixed)
	{
		cursor = CCamera::GetInstance()->ScreenToWorld(cursor);
	}

	Vec2 position = GetPosition();

	if ((position.m_x <= cursor.m_x) && (cursor.m_x <= position.m_x + scale.m_x) &&
		(position.m_y <= cursor.m_y) && (cursor.m_y <= position.m_y + scale.m_y))
	{
		m_isCursorOver = true;
	}
	else
	{
		m_isCursorOver = false;
	}
}

bool CUI::IsCursorOver()
{
	return m_isCursorOver;
}

void CUI::OnCursorOver()
{
}

void CUI::OnCursorLeftButtonDown()
{
}

void CUI::OnCursorLeftButtonUp()
{
}

void CUI::OnCursorLeftButtonClick()
{
}

void CUI::Update()
{
	UpdateChildren();
}

void CUI::LateUpdate()
{
	CObject* parent = GetParent();

	if (parent != nullptr)
	{
		SetPosition(parent->GetPosition() + GetLocalPosition());
	}

	CAnimator* animator = GetAnimator();

	if (animator != nullptr)
	{
		animator->Update();
	}

	CheckCursorOver();
	LateUpdateChildren();
}

void CUI::Render(HDC hDC)
{
	Vec2 position = GetPosition();
	const Vec2& scale = GetScale();

	// 고정되지 않는 UI, 즉 카메라의 영향을 받는 UI의 경우 위치를 월드 좌표 기준으로 변경시킨다.
	if (!m_isFixed)
	{
		if (CCamera::GetInstance()->IsVisible(this))
		{
			position = CCamera::GetInstance()->WorldToScreen(position);
		}
		else
		{
			return;
		}
	}

	if (m_isPressed)
	{
		CGdiController gdiController(hDC, PEN_TYPE::RED);

		Rectangle(hDC,
			(int)(position.m_x),
			(int)(position.m_y),
			(int)(position.m_x + scale.m_x),
			(int)(position.m_y + scale.m_y));
	}
	else
	{
		Rectangle(hDC,
			(int)(position.m_x),
			(int)(position.m_y),
			(int)(position.m_x + scale.m_x),
			(int)(position.m_y + scale.m_y));
	}

	RenderChildren(hDC);
}

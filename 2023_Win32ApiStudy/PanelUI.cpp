#include "pch.h"
#include "PanelUI.h"

#include "InputManager.h"

CPanelUI::CPanelUI() :
	m_dragPoint()
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::OnCursorOver()
{
	if (IsPressed())
	{
		Vec2 diff = CURSOR - m_dragPoint;
		Vec2 newPosition = GetPosition() + diff;

		m_dragPoint = CURSOR;

		SetPosition(newPosition);
	}
}

void CPanelUI::OnCursorLeftButtonDown()
{
	m_dragPoint = CURSOR;
}

void CPanelUI::OnCursorLeftButtonUp()
{
}

void CPanelUI::OnCursorLeftButtonClick()
{
}

void CPanelUI::Update()
{
	CUI::Update();
}

void CPanelUI::Render(HDC hDC)
{
	CUI::Render(hDC);
}

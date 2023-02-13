#include "pch.h"
#include "ButtonUI.h"

CButtonUI::CButtonUI() :
	m_event()
{
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::SetEvent(Event event)
{
	if (event != nullptr)
	{
		m_event = move(event);
	}
}

void CButtonUI::OnCursorOver()
{
}

void CButtonUI::OnCursorLeftButtonDown()
{
}

void CButtonUI::OnCursorLeftButtonUp()
{
}

void CButtonUI::OnCursorLeftButtonClick()
{
	if (m_event != nullptr)
	{
		m_event();
	}
}

#include "pch.h"
#include "Core.h"
#include "Object.h"

CObject object;

CCore::CCore() :
	m_hWnd(),
	m_resolution(),
	m_hDC()
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::Init(HWND hWnd, const SIZE& resolution)
{
	m_hWnd = hWnd;
	m_resolution = resolution;
	m_hDC = GetDC(m_hWnd);
	
	object.m_position = POINT{ m_resolution.cx / 2, m_resolution.cy / 2 };
	object.m_size = SIZE{ 100, 100 };

	// 해상도에 맞게 윈도우 크기 조정
	RECT rect = { 0, 0, m_resolution.cx, m_resolution.cy };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

	return S_OK;
}

void CCore::AdvanceFrame()
{
	Update();
	Render();
}

void CCore::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		object.m_position.y -= 1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		object.m_position.y += 1;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		object.m_position.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		object.m_position.x += 1;
	}
}

void CCore::Render()
{
	Rectangle(m_hDC,
		object.m_position.x - object.m_size.cx / 2,
		object.m_position.y - object.m_size.cy / 2,
		object.m_position.x + object.m_size.cx / 2,
		object.m_position.y + object.m_size.cy / 2);
}

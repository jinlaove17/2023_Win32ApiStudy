#include "pch.h"
#include "Core.h"

#include "TimeManager.h"

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
	
	// 해상도에 맞게 윈도우 크기 조정
	RECT rect = { 0, 0, m_resolution.cx, m_resolution.cy };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

	// 매니저 초기화
	CTimeManager::GetInstance()->Init();

	object.SetPosition(Vec2(m_resolution.cx / 2, m_resolution.cy / 2));
	object.SetScale(Vec2(100, 100));

	return S_OK;
}

HWND CCore::GetHwnd()
{
	return m_hWnd;
}

void CCore::AdvanceFrame()
{
	// 매니저 업데이트
	CTimeManager::GetInstance()->Update();

	Update();
	Render();
}

void CCore::Update()
{
	Vec2 position = object.GetPosition();

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		position.m_y -= 300.0f * DT;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		position.m_y += 300.0f * DT;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		position.m_x -= 300.0f * DT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		position.m_x += 300.0f * DT;
	}

	object.SetPosition(position);
}

void CCore::Render()
{
	const Vec2& position = object.GetPosition();
	const Vec2& scale = object.GetScale();

	Rectangle(m_hDC,
		(int)(position.m_x - scale.m_x / 2.0f),
		(int)(position.m_y - scale.m_y / 2.0f),
		(int)(position.m_x + scale.m_x / 2.0f),
		(int)(position.m_y + scale.m_y / 2.0f));
}

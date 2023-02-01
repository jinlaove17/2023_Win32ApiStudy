#include "pch.h"
#include "Core.h"

#include "TimeManager.h"

#include "Object.h"

CObject object;

CCore::CCore() :
	m_hWnd(),
	m_resolution(),
	m_hDC(),
	m_hBitmap(),
	m_hMemDC()
{
}

CCore::~CCore()
{
	// GetDC 함수로 얻어온 DC는 ReleaseDC 함수로 해제한다.
	ReleaseDC(m_hWnd, m_hDC);
	
	// CreateCompatibleDC 함수로 얻어온 DC는 DeleteDC 함수로 해제한다.
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBitmap);
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

	// 더블 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBitmap = CreateCompatibleBitmap(m_hDC, m_resolution.cx, m_resolution.cy);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// DC가 처음 만들어질 때, 1 픽셀짜리의 비트맵이 만들어진다.
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// 1 픽셀짜리 비트맵은 사용하지 않을 것이므로, 곧바로 삭제한다.
	DeleteObject(hOldBitmap);

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
	// 화면 클리어
	Rectangle(m_hMemDC, -1, -1, m_resolution.cx + 1, m_resolution.cy + 1);

	const Vec2& position = object.GetPosition();
	const Vec2& scale = object.GetScale();

	Rectangle(m_hMemDC,
		(int)(position.m_x - scale.m_x / 2.0f),
		(int)(position.m_y - scale.m_y / 2.0f),
		(int)(position.m_x + scale.m_x / 2.0f),
		(int)(position.m_y + scale.m_y / 2.0f));

	// m_hMemDC에 그려진 내용을 m_hDC로 복사한다.
	BitBlt(m_hDC, 0, 0, m_resolution.cx, m_resolution.cy, m_hMemDC, 0, 0, SRCCOPY);
}

#include "pch.h"
#include "Core.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

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
	// GetDC �Լ��� ���� DC�� ReleaseDC �Լ��� �����Ѵ�.
	ReleaseDC(m_hWnd, m_hDC);
	
	// CreateCompatibleDC �Լ��� ���� DC�� DeleteDC �Լ��� �����Ѵ�.
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBitmap);
}

int CCore::Init(HWND hWnd, const SIZE& resolution)
{
	m_hWnd = hWnd;
	m_resolution = resolution;
	m_hDC = GetDC(m_hWnd);
	
	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rect = { 0, 0, m_resolution.cx, m_resolution.cy };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBitmap = CreateCompatibleBitmap(m_hDC, m_resolution.cx, m_resolution.cy);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// DC�� ó�� ������� ��, 1 �ȼ�¥���� ��Ʈ���� ���������.
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// 1 �ȼ�¥�� ��Ʈ���� ������� ���� ���̹Ƿ�, ��ٷ� �����Ѵ�.
	DeleteObject(hOldBitmap);

	// �Ŵ��� �ʱ�ȭ
	CTimeManager::GetInstance()->Init();
	CInputManager::GetInstance()->Init();
	CSceneManager::GetInstance()->Init();

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
	// �Ŵ��� ������Ʈ
	CTimeManager::GetInstance()->Update();
	CInputManager::GetInstance()->Update();
	CSceneManager::GetInstance()->Update();

	// ȭ�� Ŭ����
	Rectangle(m_hMemDC, -1, -1, m_resolution.cx + 1, m_resolution.cy + 1);

	CSceneManager::GetInstance()->Render(m_hMemDC);

	// m_hMemDC�� �׷��� ������ m_hDC�� �����Ѵ�.
	BitBlt(m_hDC, 0, 0, m_resolution.cx, m_resolution.cy, m_hMemDC, 0, 0, SRCCOPY);
}

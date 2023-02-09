#include "pch.h"
#include "Core.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"

#include "Object.h"

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
	m_hDC = ::GetDC(m_hWnd);
	
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
	CAssetManager::GetInstance()->Init();
	CSceneManager::GetInstance()->Init();

	return S_OK;
}

HWND CCore::GetHwnd()
{
	return m_hWnd;
}

const SIZE& CCore::GetResolution()
{
	return m_resolution;
}

HDC CCore::GetDC()
{
	return m_hDC;
}

void CCore::AdvanceFrame()
{
	// �Ŵ��� ������Ʈ
	CTimeManager::GetInstance()->Update();
	CInputManager::GetInstance()->Update();
	CCamera::GetInstance()->Update();
	CSceneManager::GetInstance()->Update();
	CCollisionManager::GetInstance()->Update();

	// ȭ�� Ŭ����
	Rectangle(m_hMemDC, -1, -1, m_resolution.cx + 1, m_resolution.cy + 1);

	CSceneManager::GetInstance()->Render(m_hMemDC);

	// m_hMemDC�� �׷��� ������ m_hDC�� �����Ѵ�.
	BitBlt(m_hDC, 0, 0, m_resolution.cx, m_resolution.cy, m_hMemDC, 0, 0, SRCCOPY);

	// �̹� �����ӿ� �߰��� �̺�Ʈ�� ó���Ѵ�.
	CEventManager::GetInstance()->Update();
}

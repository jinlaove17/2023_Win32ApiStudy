#pragma once

// <싱글톤 패턴>
// - 객체의 생성을 1개로 제한한다.
// - 어디서든 접근할 수 있어야 한다.

// <정적 변수>
// 1. 함수 내 생성
// 2. 파일 내 생성
// 3. 클래스 내 생성

class CCore : public CSingleton<CCore>
{
	friend class CSingleton;

private:
	// 메인 윈도우 핸들
	HWND    m_hWnd;

	// 메인 윈도우 해상도
	SIZE    m_resolution;

	// 메인 윈도우의 디바이스 컨택스트
	HDC     m_hDC;

	// 더블 버퍼링
	HBITMAP m_hBitmap;
	HDC		m_hMemDC;

	// 툴 씬에서 사용하기 위한 메뉴 핸들
	HMENU   m_hMenu;

private:
	CCore();
	~CCore();

public:
	int Init(HWND hWnd, const SIZE& resolution);

	HWND GetHwnd();
	const SIZE& GetResolution();
	HDC GetDC();

	void ShowMenu();
	void HideMenu();

	void PrepareRender();
	void AdvanceFrame();
};

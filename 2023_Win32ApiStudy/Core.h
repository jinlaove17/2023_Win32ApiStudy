#pragma once

// <싱글톤 패턴>
// - 객체의 생성을 1개로 제한한다.
// - 어디서든 접근할 수 있어야 한다.

// <정적 변수>
// 1. 함수 내 생성
// 2. 파일 내 생성
// 3. 클래스 내 생성

class CCore
{
	// 정적 멤버 함수, 인스턴스 없이 호출 가능 하지만 this가 없기 때문에 멤버 변수에 접근할 수 없다.
	SINGLETON(CCore);

private:
	// 메인 윈도우 핸들
	HWND m_hWnd;

	// 메인 윈도우 해상도
	SIZE m_resolution;

	// 메인 윈도우의 디바이스 컨택스트
	HDC m_hDC;
	
private:
	CCore();
	~CCore();

public:
	int Init(HWND hWnd, const SIZE& resolution);

	void AdvanceFrame();

private:
	void Update();
	void Render();
};

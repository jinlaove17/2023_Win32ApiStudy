#pragma once

// <�̱��� ����>
// - ��ü�� ������ 1���� �����Ѵ�.
// - ��𼭵� ������ �� �־�� �Ѵ�.

// <���� ����>
// 1. �Լ� �� ����
// 2. ���� �� ����
// 3. Ŭ���� �� ����

class CCore
{
	// ���� ��� �Լ�, �ν��Ͻ� ���� ȣ�� ���� ������ this�� ���� ������ ��� ������ ������ �� ����.
	SINGLETON(CCore);

private:
	// ���� ������ �ڵ�
	HWND    m_hWnd;

	// ���� ������ �ػ�
	SIZE    m_resolution;

	// ���� �������� ����̽� ���ý�Ʈ
	HDC     m_hDC;

	// ���� ���۸�
	HBITMAP m_hBitmap;
	HDC		m_hMemDC;

	// �� ������ ����ϱ� ���� �޴� �ڵ�
	HMENU   m_hMenu;

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

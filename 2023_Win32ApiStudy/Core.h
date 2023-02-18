#pragma once

// <�̱��� ����>
// - ��ü�� ������ 1���� �����Ѵ�.
// - ��𼭵� ������ �� �־�� �Ѵ�.

// <���� ����>
// 1. �Լ� �� ����
// 2. ���� �� ����
// 3. Ŭ���� �� ����

class CCore : public CSingleton<CCore>
{
	friend class CSingleton;

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

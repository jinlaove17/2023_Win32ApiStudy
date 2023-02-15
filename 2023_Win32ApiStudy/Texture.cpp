#include "pch.h"
#include "Texture.h"

#include "Core.h"

CTexture::CTexture() :
	m_hDC(),
	m_hBitmap(),
	m_bitmapInfo()
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBitmap);
}

void CTexture::Create(int width, int height)
{
	HDC hDC = CCore::GetInstance()->GetDC();

	m_hBitmap = CreateCompatibleBitmap(hDC, width, height);

	// 불러온 비트맵의 가로 세로 길이
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmapInfo);

	m_hDC = CreateCompatibleDC(hDC);

	// 비트맵과 DC 연결
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);

	// 기존 1 픽셀짜리 비트맵 삭제
	DeleteObject(hOldBitmap);
}

void CTexture::Load(const wstring& filePath)
{
	if (m_hBitmap == nullptr)
	{
		m_hBitmap = (HBITMAP)LoadImage(nullptr, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

		assert(m_hBitmap != nullptr);

		// 불러온 비트맵의 가로 세로 길이
		GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmapInfo);

		// 불러온 비트맵과 연결할 DC
		m_hDC = CreateCompatibleDC(CCore::GetInstance()->GetDC());

		// 비트맵과 DC 연결
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);

		// 기존 1 픽셀짜리 비트맵 삭제
		DeleteObject(hOldBitmap);
	}
}

HDC CTexture::GetDC()
{
	return m_hDC;
}

int CTexture::GetWidth()
{
	return m_bitmapInfo.bmWidth;
}

int CTexture::GetHeight()
{
	return m_bitmapInfo.bmHeight;
}

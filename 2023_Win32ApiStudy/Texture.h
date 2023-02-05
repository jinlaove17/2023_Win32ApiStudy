#pragma once
#include "Asset.h"

class CTexture : public CAsset
{
	friend class CAssetManager;

private:
	HDC     m_hDC;
	HBITMAP m_hBitmap;
	BITMAP  m_bitmapInfo;

private:
	CTexture();
	virtual ~CTexture();

public:
	void Load(const wstring& filePath);

	HDC GetDC();
	int GetWidth();
	int GetHeight();
};
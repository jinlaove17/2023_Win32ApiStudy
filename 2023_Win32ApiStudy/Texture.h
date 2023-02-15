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

public:
	virtual ~CTexture();

public:
	void Create(int width, int height);
	void Load(const wstring& filePath);

	HDC GetDC();
	int GetWidth();
	int GetHeight();
};

#pragma once

class CTexture;

class CAssetManager
{
	SINGLETON(CAssetManager);

private:
	wchar_t m_assetPath[255];

	unordered_map<wstring, CTexture*> m_textures;

public:
	void Init();

	CTexture* LoadTexture(const wstring& fileName, const wstring& key);
	CTexture* FindTexture(const wstring& key);
};

#include "pch.h"
#include "AssetManager.h"

#include "Texture.h"

CAssetManager::CAssetManager() :
	m_assetPath{},
	m_textures()
{
}

CAssetManager::~CAssetManager()
{
	SafeDelete(m_textures);
}

void CAssetManager::Init()
{
	// ������Ʈ ������ ����� �ǿ��� ���� ���丮�� �����ϸ� Visual Studio���� ���� ��, �ش� ��θ� �۾� �����丮�� �����Ѵ�.
	// ������, Debug�� ����� ������ ���� �����ϴ� ��쿡��, �ش� ���� ������ ��ΰ� �۾� ���丮�� �����ǹǷ�, ���� �۾� ���丮����
	// ���� ������ �� �� ���� ��, Release\\Asset\\���� �̵��Ͽ� ���ҽ��� ������ �� �ֵ��� �����.
	// ��, � ���� �����ϴ��� �۾� ���丮�� ��ġ�ϵ��� ����� �ش�.
	GetCurrentDirectory(255, m_assetPath);

	// ���� ���� ��θ� ���Ѵ�.
	for (int i = (int)wcslen(m_assetPath) - 1; i >= 0; --i)
	{
		if (m_assetPath[i] == '\\')
		{
			m_assetPath[i] = '\0';

			break;
		}
	}

	wcscat_s(m_assetPath, 255, L"\\Release\\Asset\\");
}

CTexture* CAssetManager::LoadTexture(const wstring& fileName, const wstring& key)
{
	CTexture* texture = FindTexture(key);

	if (texture == nullptr)
	{
		wstring filePath = m_assetPath;

		filePath += L"texture\\" + fileName;

		texture = new CTexture();
		texture->SetName(key);
		texture->SetFilePath(filePath);
		texture->Load(filePath);

		m_textures.emplace(key, texture);
	}

	return texture;
}

CTexture* CAssetManager::FindTexture(const wstring& key)
{
	auto iter = m_textures.find(key);

	if (iter == m_textures.end())
	{
		return nullptr;
	}

	return iter->second;
}

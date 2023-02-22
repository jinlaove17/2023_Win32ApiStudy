#include "pch.h"
#include "AssetManager.h"

#include "Texture.h"
#include "Sound.h"

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

wstring CAssetManager::GetAssetPath()
{
	return wstring(m_assetPath);
}

CTexture* CAssetManager::CreateTexture(const wstring& key, int width, int height)
{
	CTexture* texture = FindTexture(key);

	if (texture == nullptr)
	{
		texture = new CTexture();
		texture->Create(width, height);
		texture->SetName(key);

		m_textures.emplace(key, texture);
	}

	return texture;
}

CTexture* CAssetManager::LoadTexture(const wstring& fileName, const wstring& key)
{
	CTexture* texture = FindTexture(key);

	if (texture == nullptr)
	{
		wstring filePath = L"Texture\\" + fileName;

		texture = new CTexture();
		texture->SetName(key);
		texture->SetFilePath(filePath);
		texture->Load(m_assetPath + filePath);

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

CSound* CAssetManager::LoadSound(const wstring& fileName, const wstring& key)
{
	CSound* sound = FindSound(key);

	if (sound == nullptr)
	{
		wstring filePath = L"Sound\\" + fileName;

		sound = new CSound();
		sound->SetName(key);
		sound->SetFilePath(filePath);
		sound->Load(m_assetPath + filePath);

		m_sounds.emplace(key, sound);
	}

	return sound;
}

CSound* CAssetManager::FindSound(const wstring& key)
{
	auto iter = m_sounds.find(key);

	if (iter == m_sounds.end())
	{
		return nullptr;
	}

	return iter->second;
}

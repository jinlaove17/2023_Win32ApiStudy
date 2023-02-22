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
	// 프로젝트 설정의 디버깅 탭에서 현재 디렉토리를 설정하면 Visual Studio에서 실행 시, 해당 경로를 작업 디텍토리로 설정한다.
	// 하지만, Debug로 빌드된 파일을 직접 실행하는 경우에는, 해당 실행 파일의 경로가 작업 디렉토리로 설정되므로, 현재 작업 디렉토리에서
	// 상위 폴더로 한 번 나간 후, Release\\Asset\\으로 이동하여 리소스에 접근할 수 있도록 만든다.
	// 즉, 어떤 모드로 실행하더라도 작업 디렉토리를 일치하도록 만들어 준다.
	GetCurrentDirectory(255, m_assetPath);

	// 상위 폴더 경로를 구한다.
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

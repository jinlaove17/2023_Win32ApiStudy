#include "pch.h"
#include "Asset.h"

CAsset::CAsset() :
	m_name(),
	m_filePath()
{
}

CAsset::~CAsset()
{
}

void CAsset::SetName(const wstring& name)
{
	m_name = name;
}

const wstring& CAsset::GetName()
{
	return m_name;
}

void CAsset::SetFilePath(const wstring& filePath)
{
	m_filePath = filePath;
}

const wstring& CAsset::GetFilePath()
{
	return m_filePath;
}

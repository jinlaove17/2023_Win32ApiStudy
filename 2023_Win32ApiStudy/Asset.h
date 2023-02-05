#pragma once

class CAsset
{
private:
	wstring m_name;
	wstring m_filePath;

public:
	CAsset();
	virtual ~CAsset();

	void SetName(const wstring& name);
	const wstring& GetName();

	void SetFilePath(const wstring& filePath);
	const wstring& GetFilePath();
};

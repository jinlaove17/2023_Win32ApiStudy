#pragma once

template <typename T>
inline void SafeDelete(vector<T>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] != nullptr)
		{
			delete v[i];
			v[i] = nullptr;
		}
	}

	v.clear();
}

template <typename T, typename U>
inline void SafeDelete(unordered_map<T, U>& um)
{
	for (auto& p : um)
	{
		if (p.second != nullptr)
		{
			delete p.second;
			p.second = nullptr;
		}
	}

	um.clear();
}

void WriteString(FILE* file, const wstring& str);
void ReadString(FILE* file, wstring& str);

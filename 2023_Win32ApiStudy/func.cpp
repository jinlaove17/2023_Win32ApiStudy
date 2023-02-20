#include "pch.h"
#include "func.h"

void WriteString(FILE* file, const wstring& str)
{
	size_t len = str.length();

	// 문자열의 길이 및 내용 저장
	fwrite(&len, sizeof(size_t), 1, file);
	fwrite(str.c_str(), sizeof(wchar_t), len, file);
}

void ReadString(FILE* file, wstring& str)
{
	size_t len = 0;
	wchar_t buffer[256] = {};

	fread(&len, sizeof(size_t), 1, file);
	fread(&buffer, sizeof(wchar_t), len, file);

	str = buffer;
}

#pragma once
#pragma comment(lib, "Msimg32.lib")

// <미리 컴파일된 헤더>
// - 모든 cpp파일들은 이 헤더 파일을 포함해야한다.

#include "targetver.h"

// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN         

// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ 헤더 파일
#include <cmath>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

#include "define.h"
#include "struct.h"

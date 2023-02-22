#pragma once
#pragma comment(lib, "Msimg32.lib")

// <�̸� �����ϵ� ���>
// - ��� cpp���ϵ��� �� ��� ������ �����ؾ��Ѵ�.

#include "targetver.h"

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN         

// Windows ��� ����
#include <windows.h>

// C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commdlg.h>

// C++ ��� ����
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

// Sound ���� ��� ����(���� �߿�)
#define DIRECTINPUT_VERSION 0x0800

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#include "define.h"
#include "udt.h"
#include "func.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// 아래와 같은 매크로를 사용할 때는 연산자 우선 순위에 유의하자!
// #define ADD(a, b) a + b
// 아래 식의 결과 값은 500이 아닌 230이다.
// int n = 10 * ADD(20, 30);

#define CLONE(type)	  virtual type* Clone()\
					  {\
					  	return new type(*this);\
					  }

#define DT			  CTimeManager::GetInstance()->GetDeltaTime()

#define KEY_NONE(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::NONE
#define KEY_TAP(key)  CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::TAP
#define KEY_HOLD(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::HOLD
#define KEY_AWAY(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::AWAY
#define CURSOR		  CInputManager::GetInstance()->GetCursor()

#define PI			  3.1415926535f

#define TILE_SIZE	  64

using Event = function<void()>;

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	COUNT
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,

	COUNT
};

enum class SCENE_TYPE
{
	TOOL,
	TITLE,
	STAGE1,
	STAGE2,

	COUNT
};

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	GROUND,
	MONSTER,
	MONSTER_PROJ,
	PLAYER_PROJ,
	PLAYER,
	UI,

	COUNT
};

enum MONSTER_TYPE
{
	NORMAL,
	BOSS,

	COUNT
};

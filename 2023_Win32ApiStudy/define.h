#pragma once

// �Ʒ��� ���� ��ũ�θ� ����� ���� ������ �켱 ������ ��������!
// #define ADD(a, b) a + b
// �Ʒ� ���� ��� ���� 500�� �ƴ� 230�̴�.
// int n = 10 * ADD(20, 30);

#define SINGLETON(type) private:\
							type();\
							~type();\
						public:\
							static type* GetInstance()\
							{\
								 static type instance;\
								 return &instance;\
							}

#define CLONE(type)		virtual type* Clone()\
						{\
							return new type(*this);\
						}

#define DT				CTimeManager::GetInstance()->GetDeltaTime()

#define KEY_NONE(key)	CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::NONE
#define KEY_TAP(key)	CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::TAP
#define KEY_HOLD(key)	CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::HOLD
#define KEY_AWAY(key)	CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::AWAY
#define CURSOR			CInputManager::GetInstance()->GetCursor()

#define PI				3.1415926535f

#define TILE_SIZE		64

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
	MONSTER,
	MONSTER_PROJ,
	PLAYER_PROJ,
	PLAYER,

	COUNT
};

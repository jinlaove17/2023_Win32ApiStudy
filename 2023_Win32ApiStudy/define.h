#pragma once

// 아래와 같은 매크로를 사용할 때는 연산자 우선 순위에 유의하자!
// #define ADD(a, b) a + b
// 아래 식의 결과 값은 500이 아닌 230이다.
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

#define DT CTimeManager::GetInstance()->GetDeltaTime()

#define KEY_NONE(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::NONE
#define KEY_TAP(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::TAP
#define KEY_HOLD(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::HOLD
#define KEY_AWAY(key) CInputManager::GetInstance()->GetKeyState(key) == KEY_STATE::AWAY

enum class SCENE_TYPE
{
	TITLE,
	STAGE1,
	STAGE2,

	COUNT
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,

	COUNT
};

#pragma once

#include "Monster.h"

class CMonsterFactory
{
private:
	CMonsterFactory();
	~CMonsterFactory();

public:
	static CMonster* CreateMonster(MONSTER_TYPE monsterType, const Vec2& position);
};

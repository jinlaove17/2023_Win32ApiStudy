#include "pch.h"
#include "MonsterFactory.h"

CMonsterFactory::CMonsterFactory()
{
}

CMonsterFactory::~CMonsterFactory()
{
}

CMonster* CMonsterFactory::CreateMonster(MONSTER_TYPE monsterType, const Vec2& position)
{
	CMonster* monster = nullptr;
	MonsterInfo monsterInfo = {};

	switch (monsterType)
	{
	case MONSTER_TYPE::NORMAL:
	{
		monsterInfo.m_health = 100.0f;
		monsterInfo.m_speed = 150.0f;
		monsterInfo.m_recogRange = 200.0f;
		monsterInfo.m_attackRange = 60.0f;
		monsterInfo.m_attackDamage = 15.0f;

		monster = new CMonster();
		monster->SetName(L"Monster");
		monster->SetPosition(position);
		monster->SetScale(Vec2(50.0f, 50.0f));
		monster->SetInfo(monsterInfo);
	}
		break;
	case MONSTER_TYPE::BOSS:
		break;
	}

	return monster;
}

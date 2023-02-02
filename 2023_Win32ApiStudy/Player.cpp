#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "Missile.h"

#include "Scene.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Vec2 position = GetPosition();

	if (KEY_HOLD(KEY::W))
	{
		position.m_y -= 300.0f * DT;
	}

	if (KEY_HOLD(KEY::S))
	{
		position.m_y += 300.0f * DT;
	}

	if (KEY_HOLD(KEY::A))
	{
		position.m_x -= 300.0f * DT;
	}

	if (KEY_HOLD(KEY::D))
	{
		position.m_x += 300.0f * DT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPosition(position);
}

void CPlayer::CreateMissile()
{
	CMissile* missile = new CMissile();
	Vec2 missilePosition = GetPosition();

	missilePosition.m_y -= 0.5f * GetScale().m_y;
	missile->SetPosition(missilePosition);
	missile->SetScale(Vec2(20.0f, 20.0f));
	missile->SetDirection(Vec2(0.0f, -1.0f));

	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();

	currentScene->AddObject(GROUP_TYPE::DEFAULT, missile);
}

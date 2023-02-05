#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "SceneManager.h"

#include "Scene.h"

#include "Texture.h"
#include "Collider.h"

#include "Missile.h"

CPlayer::CPlayer()
{
	SetName(L"Player");

	SetTexture(CAssetManager::GetInstance()->LoadTexture(L"Player.bmp", L"Player"));

	CreateCollider();
	GetCollider()->SetOffset(Vec2(0.0f, -5.0f));
	GetCollider()->SetScale(Vec2(30.0f, 30.0f));
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

void CPlayer::Render(HDC hDC)
{
	const Vec2& position = GetPosition();

	CTexture* texture = GetTexture();
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	//BitBlt(hDC, (int)(position.m_x - 0.5f * width), (int)(position.m_y - 0.5f * height), width, height, texture->GetDC(), 0, 0, SRCCOPY);
	TransparentBlt(hDC, (int)(position.m_x - 0.5f * width), (int)(position.m_y - 0.5f * height), width, height, texture->GetDC(), 0, 0, width, height, RGB(255, 0, 255));

	ComponentRender(hDC);
}

void CPlayer::CreateMissile()
{
	CMissile* missile = new CMissile();
	Vec2 missilePosition = GetPosition();

	missilePosition.m_y -= 0.5f * GetScale().m_y;
	missile->SetPosition(missilePosition);
	missile->SetScale(Vec2(15.0f, 15.0f));
	missile->SetDirection(Vec2(0.0f, -1.0f));

	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();

	currentScene->AddObject(GROUP_TYPE::PLAYER_PROJ, missile);
}

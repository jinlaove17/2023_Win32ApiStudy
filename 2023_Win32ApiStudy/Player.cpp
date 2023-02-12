#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "EventManager.h"

#include "Texture.h"
#include "Collider.h"
#include "Animator.h"

#include "Missile.h"

CPlayer::CPlayer()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.0f, 65.0f));

	CTexture* texture = CAssetManager::GetInstance()->LoadTexture(L"Link.bmp", L"Player");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_UP", texture, Vec2(10, 8), 60, 10, 0.06f);
	GetAnimator()->CreateAnimation(L"WALK_DOWN", texture, Vec2(10, 8), 40, 10, 0.06f);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", texture, Vec2(10, 8), 50, 10, 0.06f);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", texture, Vec2(10, 8), 70, 10, 0.06f);
	GetAnimator()->Play(L"WALK_DOWN", true);
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

		GetAnimator()->Play(L"WALK_UP", true);
	}

	if (KEY_HOLD(KEY::S))
	{
		position.m_y += 300.0f * DT;

		GetAnimator()->Play(L"WALK_DOWN", true);
	}

	if (KEY_HOLD(KEY::A))
	{
		position.m_x -= 300.0f * DT;

		GetAnimator()->Play(L"WALK_LEFT", true);
	}

	if (KEY_HOLD(KEY::D))
	{
		position.m_x += 300.0f * DT;

		GetAnimator()->Play(L"WALK_RIGHT", true);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPosition(position);
}

void CPlayer::Render(HDC hDC)
{
	RenderComponent(hDC);
}

void CPlayer::CreateMissile()
{
	CMissile* missile = new CMissile();
	Vec2 missilePosition = GetPosition();

	missilePosition.m_y -= 0.5f * GetScale().m_y;
	missile->SetName(L"Missile(Player)");
	missile->SetPosition(missilePosition);
	missile->SetScale(Vec2(15.0f, 15.0f));
	missile->SetDirection(Vec2(0.0f, -1.0f));

	CEventManager::GetInstance()->CreateObject(GROUP_TYPE::PLAYER_PROJ, missile);
}

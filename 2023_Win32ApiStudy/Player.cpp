#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "EventManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"

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

	CreateRigidBody();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	CAnimator* animator = GetAnimator();
	CRigidBody* rigidBody = GetRigidBody();

	if (KEY_HOLD(KEY::W))
	{
		rigidBody->AddForce(Vec2(0.0f, -200.0f));
		animator->Play(L"WALK_UP", true);
	}

	if (KEY_HOLD(KEY::S))
	{
		rigidBody->AddForce(Vec2(0.0f, 200.0f));
		animator->Play(L"WALK_DOWN", true);
	}

	if (KEY_HOLD(KEY::A))
	{
		rigidBody->AddForce(Vec2(-200.0f, 0.0f));
		animator->Play(L"WALK_LEFT", true);
	}

	if (KEY_HOLD(KEY::D))
	{
		rigidBody->AddForce(Vec2(200.0f, 0.0f));
		animator->Play(L"WALK_RIGHT", true);
	}

	// 최대 속도에 이르기까지의 시간이 오래 걸리므로, 해당 방향으로 일정 속도를 추가하여 최소 속도를 증가시킨다.
	if (KEY_TAP(KEY::W))
	{
		rigidBody->AddVelocity(Vec2(0.0f, -100.0f));
	}

	if (KEY_TAP(KEY::S))
	{
		rigidBody->AddVelocity(Vec2(0.0f, 100.0f));
	}

	if (KEY_TAP(KEY::A))
	{
		rigidBody->AddVelocity(Vec2(-100.0f, 0.0f));
	}

	if (KEY_TAP(KEY::D))
	{
		rigidBody->AddVelocity(Vec2(100.0f, 0.0f));
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}
}

void CPlayer::Render(HDC hDC)
{
	if (CCamera::GetInstance()->IsVisible(this))
	{
		RenderComponent(hDC);
	}
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

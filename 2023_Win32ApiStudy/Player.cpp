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
#include "StateMachine.h"

#include "PlayerStates.h"

#include "Missile.h"

CPlayer::CPlayer() :
	m_direction(-1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.0f, 85.0f));
	GetCollider()->SetOffset(Vec2(0.0f, 20.0f));

	CTexture* leftTexture = CAssetManager::GetInstance()->LoadTexture(L"Kyo(Left).bmp", L"Player(Left)");
	CTexture* rightTexture = CAssetManager::GetInstance()->LoadTexture(L"Kyo(Right).bmp", L"Player(Right)");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle(Left)", leftTexture, Vec2(6, 4), 0, 5, 0.15f);
	GetAnimator()->CreateAnimation(L"Idle(Right)", rightTexture, Vec2(6, 4), 0, 5, 0.15f);
	GetAnimator()->CreateAnimation(L"Jump(Left)", leftTexture, Vec2(6, 4), 6, 5, 0.1f);
	GetAnimator()->CreateAnimation(L"Jump(Right)", rightTexture, Vec2(6, 4), 6, 5, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk(Left)", leftTexture, Vec2(6, 4), 12, 6, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk(Right)", rightTexture, Vec2(6, 4), 12, 6, 0.1f);

	CreateRigidBody();

	// �����ÿ��� Idle ���·� �����Ѵ�.
	CreateStateMachine();
	GetStateMachine()->SetCurrentState(CPlayerIdleState::GetInstance());
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetDirection(int direction)
{
	if (direction == 0)
	{
		return;
	}

	m_direction = direction;
}

int CPlayer::GetDirection()
{
	return m_direction;
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

void CPlayer::Render(HDC hDC)
{
	if (CCamera::GetInstance()->IsVisible(this))
	{
		RenderComponent(hDC);
	}
}

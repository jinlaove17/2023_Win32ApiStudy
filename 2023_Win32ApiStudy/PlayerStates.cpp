#include "pch.h"
#include "PlayerStates.h"

#include "InputManager.h"

#include "Player.h"

#include "Animator.h"
#include "RigidBody.h"
#include "StateMachine.h"

CPlayerIdleState::CPlayerIdleState()
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::Enter(CObject* object)
{
	CPlayer* player = (CPlayer*)object;
	CAnimator* animator = player->GetAnimator();

	if (player->GetDirection() < 0)
	{
		animator->Play(L"Idle(Left)", true);
	}
	else
	{
		animator->Play(L"Idle(Right)", true);
	}
}

void CPlayerIdleState::Exit(CObject* object)
{
}

void CPlayerIdleState::Update(CObject* object)
{
	CPlayer* player = (CPlayer*)object;

	if (KEY_HOLD(KEY::A) || KEY_HOLD(KEY::D))
	{
		player->GetStateMachine()->ChangeState(CPlayerWalkState::GetInstance());
	}

	if (KEY_TAP(KEY::SPACE))
	{
		player->GetStateMachine()->ChangeState(CPlayerJumpState::GetInstance());
	}
}



CPlayerJumpState::CPlayerJumpState()
{
}

CPlayerJumpState::~CPlayerJumpState()
{
}

void CPlayerJumpState::Enter(CObject* object)
{
	CPlayer* player = (CPlayer*)object;
	CAnimator* animator = player->GetAnimator();
	CRigidBody* rigidBody = object->GetRigidBody();

	if (player->GetDirection() < 0)
	{
		animator->Play(L"Jump(Left)", false);
	}
	else
	{
		animator->Play(L"Jump(Right)", false);
	}

	rigidBody->AddVelocity(Vec2(0.0f, -300.0f));
}

void CPlayerJumpState::Exit(CObject* object)
{
}

void CPlayerJumpState::Update(CObject* object)
{
	CPlayer* player = (CPlayer*)object;

	if (player->GetRigidBody()->IsLanded())
	{
		player->GetStateMachine()->ChangeState(CPlayerIdleState::GetInstance());
	}
	else
	{
		CAnimator* animator = object->GetAnimator();
		CRigidBody* rigidBody = object->GetRigidBody();

		if (KEY_HOLD(KEY::A))
		{
			player->SetDirection(-1);
			rigidBody->AddForce(Vec2(-200.0f, 0.0f));
		}

		if (KEY_HOLD(KEY::D))
		{
			player->SetDirection(1);
			rigidBody->AddForce(Vec2(200.0f, 0.0f));
		}
	}
}



CPlayerWalkState::CPlayerWalkState()
{
}

CPlayerWalkState::~CPlayerWalkState()
{
}

void CPlayerWalkState::Enter(CObject* object)
{
	CPlayer* player = (CPlayer*)object;
	CAnimator* animator = object->GetAnimator();
	CRigidBody* rigidBody = object->GetRigidBody();

	if (KEY_TAP(KEY::A))
	{
		player->SetDirection(-1);
		rigidBody->AddVelocity(Vec2(-200.0f, 0.0f));
		animator->Play(L"Walk(Left)", true);
	}

	if (KEY_TAP(KEY::D))
	{
		player->SetDirection(1);
		rigidBody->AddVelocity(Vec2(200.0f, 0.0f));
		animator->Play(L"Walk(Right)", true);
	}
}

void CPlayerWalkState::Exit(CObject* object)
{
}

void CPlayerWalkState::Update(CObject* object)
{
	CPlayer* player = (CPlayer*)object;

	if (KEY_NONE(KEY::A) && KEY_NONE(KEY::D) && (player->GetRigidBody()->GetSpeedX() <= FLT_EPSILON))
	{
		player->GetStateMachine()->ChangeState(CPlayerIdleState::GetInstance());
	}
	else if (KEY_TAP(KEY::SPACE))
	{
		player->GetStateMachine()->ChangeState(CPlayerJumpState::GetInstance());
	}
	else
	{
		CAnimator* animator = object->GetAnimator();
		CRigidBody* rigidBody = object->GetRigidBody();

		if (KEY_HOLD(KEY::A))
		{
			player->SetDirection(-1);
			rigidBody->AddForce(Vec2(-200.0f, 0.0f));
			animator->Play(L"Walk(Left)", true);
		}

		if (KEY_HOLD(KEY::D))
		{
			player->SetDirection(1);
			rigidBody->AddForce(Vec2(200.0f, 0.0f));
			animator->Play(L"Walk(Right)", true);
		}
	}
}

#include "pch.h"
#include "Ground.h"

#include "Collider.h"
#include "RigidBody.h"

CGround::CGround()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(290.0f, 90.0f));
}

CGround::~CGround()
{
}

void CGround::OnCollisionEnter(CCollider* collidedCollider)
{
	CObject* collidedObject = collidedCollider->GetOwner();

	collidedObject->GetRigidBody()->SetLanded(true);

	// 겹친 길이를 구하고, 해당 값만큼 올린다.
	float dist = 0.5f * (collidedCollider->GetScale().m_y + GetCollider()->GetScale().m_y) - abs(collidedCollider->GetPosition().m_y - GetCollider()->GetPosition().m_y);
	Vec2 position = collidedObject->GetPosition();

	position.m_y -= dist;
	collidedObject->SetPosition(position);
}

void CGround::OnCollision(CCollider* collidedCollider)
{
	CObject* collidedObject = collidedCollider->GetOwner();

	// 겹친 길이를 구하고, 해당 값만큼 올린다.
	float dist = 0.5f * (collidedCollider->GetScale().m_y + GetCollider()->GetScale().m_y) - abs(collidedCollider->GetPosition().m_y - GetCollider()->GetPosition().m_y);
	Vec2 position = collidedObject->GetPosition();

	position.m_y -= dist;
	collidedObject->SetPosition(position);
}

void CGround::OnCollisionExit(CCollider* collidedCollider)
{
	CObject* collidedObject = collidedCollider->GetOwner();

	collidedObject->GetRigidBody()->SetLanded(false);
}

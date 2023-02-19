#include "pch.h"
#include "Object.h"

#include "Camera.h"

#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "StateMachine.h"

CObject::CObject() :
	m_isActive(true),
	m_isDeleted(),
	m_name(),
	m_position(),
	m_localPosition(),
	m_scale(),
	m_texture(),
	m_collider(),
	m_animator(),
	m_rigidBody(),
	m_stateMachine(),
	m_parent(),
	m_children()
{
}

CObject::CObject(const CObject& rhs) :
	m_isActive(rhs.m_isActive),
	m_isDeleted(),
	m_name(rhs.m_name),
	m_position(rhs.m_position),
	m_localPosition(rhs.m_localPosition),
	m_scale(rhs.m_scale),
	m_texture(rhs.m_texture),
	m_collider(),
	m_animator(),
	m_rigidBody(),
	m_stateMachine(),
	m_parent(rhs.m_parent),
	m_children()
{
	if (rhs.m_collider != nullptr)
	{
		m_collider = new CCollider(*rhs.m_collider);
		m_collider->m_owner = this;
	}

	if (rhs.m_animator != nullptr)
	{
		m_animator = new CAnimator(*rhs.m_animator);
		m_animator->m_owner = this;
	}

	if (rhs.m_rigidBody != nullptr)
	{
		m_rigidBody = new CRigidBody(*rhs.m_rigidBody);
		m_rigidBody->m_owner = this;
	}

	if (rhs.m_stateMachine != nullptr)
	{
		m_stateMachine = new CStateMachine(*rhs.m_stateMachine);
		m_stateMachine->m_owner = this;
	}

	if (!rhs.m_children.empty())
	{
		m_children.reserve(rhs.m_children.size());

		for (int i = 0; i < rhs.m_children.size(); ++i)
		{
			AddChild(rhs.m_children[i]->Clone());
		}
	}
}

CObject::~CObject()
{
	if (m_collider != nullptr)
	{
		delete m_collider;
		m_collider = nullptr;
	}

	if (m_animator != nullptr)
	{
		delete m_animator;
		m_animator = nullptr;
	}

	if (m_rigidBody != nullptr)
	{
		delete m_rigidBody;
		m_rigidBody = nullptr;
	}

	if (m_stateMachine != nullptr)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}

	SafeDelete(m_children);
}

void CObject::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool CObject::IsActive()
{
	return m_isActive;
}

void CObject::SetDeleted(bool isDeleted)
{
	m_isDeleted = isDeleted;
}

bool CObject::IsDeleted()
{
	return m_isDeleted;
}

void CObject::SetName(const wstring& name)
{
	m_name = name;
}

const wstring& CObject::GetName()
{
	return m_name;
}

void CObject::SetPosition(const Vec2& position)
{
	m_position = position;
}

const Vec2& CObject::GetPosition()
{
	return m_position;
}

void CObject::SetLocalPosition(const Vec2& localPosition)
{
	m_localPosition = localPosition;
}

const Vec2& CObject::GetLocalPosition()
{
	return m_localPosition;
}

void CObject::SetScale(const Vec2& scale)
{
	m_scale = scale;
}

const Vec2& CObject::GetScale()
{
	return m_scale;
}

void CObject::SetTexture(CTexture* texture)
{
	m_texture = texture;
}

CTexture* CObject::GetTexture()
{
	return m_texture;
}

void CObject::CreateCollider()
{
	if (m_collider == nullptr)
	{
		m_collider = new CCollider();
		m_collider->m_owner = this;
	}
}

CCollider* CObject::GetCollider()
{
	return m_collider;
}

void CObject::CreateAnimator()
{
	if (m_animator == nullptr)
	{
		m_animator = new CAnimator();
		m_animator->m_owner = this;
	}
}

CAnimator* CObject::GetAnimator()
{
	return m_animator;
}

void CObject::CreateRigidBody()
{
	if (m_rigidBody == nullptr)
	{
		m_rigidBody = new CRigidBody();
		m_rigidBody->m_owner = this;
	}
}

CRigidBody* CObject::GetRigidBody()
{
	return m_rigidBody;
}

void CObject::CreateStateMachine()
{
	if (m_stateMachine == nullptr)
	{
		m_stateMachine = new CStateMachine();
		m_stateMachine->m_owner = this;
	}
}

CStateMachine* CObject::GetStateMachine()
{
	return m_stateMachine;
}

CObject* CObject::GetParent()
{
	return m_parent;
}

void CObject::AddChild(CObject* object)
{
	if (object != nullptr)
	{
		m_children.push_back(object);
		object->m_parent = this;
	}
}

const vector<CObject*>& CObject::GetChildren()
{
	return m_children;
}

void CObject::OnCollisionEnter(CCollider* collidedCollider)
{
}

void CObject::OnCollision(CCollider* collidedCollider)
{
}

void CObject::OnCollisionExit(CCollider* collidedCollider)
{
}

void CObject::UpdateChildren()
{
	for (int i = 0; i < m_children.size(); ++i)
	{
		if (m_children[i]->m_isActive && !m_children[i]->m_isDeleted)
		{
			m_children[i]->Update();
		}
	}
}

void CObject::Update()
{
	if (m_stateMachine != nullptr)
	{
		m_stateMachine->Update();
	}

	UpdateChildren();
}

void CObject::LateUpdate()
{
	if (m_parent != nullptr)
	{
		m_position = m_parent->GetPosition() + m_localPosition;
	}

	if (m_animator != nullptr)
	{
		m_animator->Update();
	}

	if (m_rigidBody != nullptr)
	{
		m_rigidBody->Update();
	}

	if (m_collider != nullptr)
	{
		m_collider->Update();
	}

	LateUpdateChildren();
}

void CObject::LateUpdateChildren()
{
	for (int i = 0; i < m_children.size(); ++i)
	{
		if (m_children[i]->m_isActive && !m_children[i]->m_isDeleted)
		{
			m_children[i]->LateUpdate();
		}
	}
}

void CObject::Render(HDC hDC)
{
	if (CCamera::GetInstance()->IsVisible(this))
	{
		Vec2 position = CCamera::GetInstance()->WorldToScreen(m_position);

		Rectangle(hDC,
			(int)(position.m_x - 0.5f * m_scale.m_x),
			(int)(position.m_y - 0.5f * m_scale.m_y),
			(int)(position.m_x + 0.5f * m_scale.m_x),
			(int)(position.m_y + 0.5f * m_scale.m_y));

		RenderComponent(hDC);
		RenderChildren(hDC);
	}
}

void CObject::RenderComponent(HDC hDC)
{
	if (m_collider != nullptr)
	{
		m_collider->Render(hDC);
	}

	if (m_animator != nullptr)
	{
		m_animator->Render(hDC);
	}
}

void CObject::RenderChildren(HDC hDC)
{
	for (int i = 0; i < m_children.size(); ++i)
	{
		if (m_children[i]->m_isActive && !m_children[i]->m_isDeleted)
		{
			m_children[i]->Render(hDC);
		}
	}
}

#include "pch.h"
#include "Camera.h"

#include "Core.h"

#include "TimeManager.h"
#include "InputManager.h"

#include "Object.h"

CCamera::CCamera() :
	m_lookAt(),
	m_finalLookAt(),
	m_diff(),
	m_target()
{
}

CCamera::~CCamera()
{
}

void CCamera::SetFinalLookAt(const Vec2& finalLookAt)
{
	m_finalLookAt = finalLookAt;
}

const Vec2& CCamera::GetFinalLookAt()
{
	return m_finalLookAt;
}

void CCamera::SetTarget(CObject* object)
{
	m_target = object;
}

CObject* CCamera::GetTarget()
{
	return m_target;
}

Vec2 CCamera::WorldToScreen(const Vec2& worldPosition)
{
	return worldPosition - m_diff;
}

Vec2 CCamera::ScreenToWorld(const Vec2& screenPosition)
{
	return screenPosition + m_diff;
}

void CCamera::Update()
{
	if (m_target != nullptr)
	{
		if (m_target->IsDeleted())
		{
			m_target = nullptr;
		}
		else
		{
			m_lookAt = m_target->GetPosition();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_lookAt.m_y -= 600.0f * DT;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		m_lookAt.m_y += 600.0f * DT;
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		m_lookAt.m_x -= 600.0f * DT;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		m_lookAt.m_x += 600.0f * DT;
	}

	Vec2 shift = m_finalLookAt - m_lookAt;

	// lookAt이 finalLookAt을 초과하는 경우 다시 돌아가기 위해 덜덜 떨리는 문제가 있기 때문에 두 벡터 간의 크기가 0.05f보다 클 때만 이동한다.
	if (shift.Length() <= 0.05f)
	{
		m_finalLookAt = m_lookAt;
	}
	else
	{
		m_lookAt += shift * 2.0f * DT;

		const SIZE& resolution = CCore::GetInstance()->GetResolution();
		Vec2 origin(resolution.cx / 2, resolution.cy / 2);

		m_diff = m_lookAt - origin;
	}
}

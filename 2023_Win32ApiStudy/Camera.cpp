#include "pch.h"
#include "Camera.h"

#include "Core.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "AssetManager.h"

#include "Object.h"

#include "Texture.h"

CCamera::CCamera() :
	m_lookAt(),
	m_finalLookAt(),
	m_diff(),
	m_target(),
	m_veilTexture(),
	m_effectQueue()
{
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	const SIZE& resolution = CCore::GetInstance()->GetResolution();

	m_veilTexture = CAssetManager::GetInstance()->CreateTexture(L"CameraVeil", resolution.cx, resolution.cy);
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

void CCamera::AddEffect(CAM_EFFECT effect, float duration)
{
	if (duration <= 0.0f)
	{
		return;
	}

	m_effectQueue.push(CamEffect{ effect, duration, 0.0f });
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
			m_finalLookAt = m_target->GetPosition();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_finalLookAt.m_y -= 600.0f * DT;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		m_finalLookAt.m_y += 600.0f * DT;
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		m_finalLookAt.m_x -= 600.0f * DT;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		m_finalLookAt.m_x += 600.0f * DT;
	}

	Vec2 shift = m_finalLookAt - m_lookAt;

	// lookAt�� finalLookAt�� �ʰ��ϴ� ��� �ٽ� ���ư��� ���� ���� ������ ������ �ֱ� ������ �� ���� ���� ũ�Ⱑ 0.05f���� Ŭ ���� �̵��Ѵ�.
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

void CCamera::Render(HDC hDC)
{
	if (m_effectQueue.empty())
	{
		return;
	}

	CamEffect& currentEffect = m_effectQueue.front();

	currentEffect.m_accTime += DT;

	float ratio = currentEffect.m_accTime / currentEffect.m_duration;

	// ���� �ð��� ���� �ð��� �ʰ��Ͽ�, ������ 0.0 ~ 1.0f�� ��� ��쿡�� ���� �������ش�.
	if (ratio < 0.0f)
	{
		ratio = 0.0f;
	}
	else if (ratio > 1.0f)
	{
		ratio = 1.0f;
	}

	switch (currentEffect.m_effect)
	{
	case CAM_EFFECT::FADE_IN:
	{
		// ���� ����(����ä���� ���� bmp������ �ʿ��ϴ�.)
		BLENDFUNCTION bf = {};

		bf.AlphaFormat = 0; // 0: ���� ����, AC_SRC_ALPHA: �κ� ����
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = (int)(255 * (1.0f - ratio)); // ���� �������� ���� ��(�ִ� 255)

		AlphaBlend(hDC,
			0,
			0,
			m_veilTexture->GetWidth(),
			m_veilTexture->GetHeight(),
			m_veilTexture->GetDC(),
			0,
			0,
			m_veilTexture->GetWidth(),
			m_veilTexture->GetHeight(),
			bf);
	}
		break;
	case CAM_EFFECT::FADE_OUT:
	{
		// ���� ����(����ä���� ���� bmp������ �ʿ��ϴ�.)
		BLENDFUNCTION bf = {};

		bf.AlphaFormat = 0; // 0: ���� ����, AC_SRC_ALPHA: �κ� ����
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = (int)(255 * ratio); // ���� �������� ���� ��(�ִ� 255)

		AlphaBlend(hDC,
			0,
			0,
			m_veilTexture->GetWidth(),
			m_veilTexture->GetHeight(),
			m_veilTexture->GetDC(),
			0,
			0,
			m_veilTexture->GetWidth(),
			m_veilTexture->GetHeight(),
			bf);
	}
		break;
	}

	// ȿ�� ����(�� �ڵ尡 ���� �������� �ִ� ������, ���� �ð��� ���� �ð��� �ʰ��� �� �����ӱ����� �������� �ϱ� ���ؼ���.)
	if (currentEffect.m_accTime >= currentEffect.m_duration)
	{
		m_effectQueue.pop();
	}
}

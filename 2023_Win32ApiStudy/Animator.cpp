#include "pch.h"
#include "Animator.h"

#include "Animation.h"

CAnimator::CAnimator() :
	m_isLoop(),
	m_animations(),
	m_playingAnimation(),
	m_owner()
{
}

CAnimator::CAnimator(const CAnimator& rhs) :
	m_isLoop(rhs.m_isLoop),
	m_animations(),
	m_playingAnimation(),
	m_owner()
{
	m_animations.reserve(rhs.m_animations.size());

	for (const auto& p : rhs.m_animations)
	{
		CAnimation* animation = new CAnimation(*p.second);

		animation->m_animator = this;
		m_animations.emplace(p.first, animation);
	}

	m_playingAnimation = m_animations[rhs.m_playingAnimation->GetName()];
}

CAnimator::~CAnimator()
{
	SafeDelete(m_animations);
}

CObject* CAnimator::GetOwner()
{
	return m_owner;
}

void CAnimator::CreateAnimation(const wstring& key, CTexture* texture, const Vec2& count, int startIndex, int frameCount, float duration)
{
	CAnimation* animation = FindAnimation(key);

	if (animation == nullptr)
	{
		animation = new CAnimation(key, this, texture, count, startIndex, frameCount, duration);

		m_animations.emplace(key, animation);
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& key)
{
	auto iter = m_animations.find(key);

	if (iter == m_animations.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::Play(const wstring& key, bool isLoop)
{
	CAnimation* animation = FindAnimation(key);

	assert(animation != nullptr);

	m_isLoop = isLoop;
	m_playingAnimation = animation;
}

void CAnimator::Update()
{
	if (m_playingAnimation != nullptr)
	{
		m_playingAnimation->Update();

		if (m_isLoop && m_playingAnimation->IsFinished())
		{
			m_playingAnimation->SetFrame(0);
		}
	}
}

void CAnimator::Render(HDC hDC)
{
	if (m_playingAnimation != nullptr)
	{
		m_playingAnimation->Render(hDC);
	}
}

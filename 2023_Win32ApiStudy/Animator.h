#pragma once
#include "Component.h"

class CAnimation;
class CTexture;

class CAnimator : public CComponent
{
	friend class CObject;

private:
	bool								m_isLoop;

	unordered_map<wstring, CAnimation*> m_animations;
	CAnimation*							m_playingAnimation;

private:
	CAnimator();
	CAnimator(const CAnimator& rhs);
	~CAnimator();

public:
	void CreateAnimation(const wstring& key, CTexture* texture, const Vec2& count, int startIndex, int frameCount, float duration);
	CAnimation* FindAnimation(const wstring& key);
	void Play(const wstring& key, bool isLoop);

	virtual void Update();

	virtual void Render(HDC hDC);
};

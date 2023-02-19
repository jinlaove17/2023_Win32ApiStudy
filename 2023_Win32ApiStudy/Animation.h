#pragma once

class CAnimator;
class CTexture;

struct AnimationFrame
{
public:
	Vec2  m_leftTop;
	Vec2  m_offset;
	Vec2  m_sliceSize;
	float m_duration;
};

class CAnimation
{
	friend class CAnimator;

private:
	wstring				   m_name;

	bool				   m_isFinished;

	vector<AnimationFrame> m_frames;
	int					   m_frameIndex;
	float				   m_accTime;

	CAnimator*			   m_animator;
	CTexture*			   m_texture;

private:
	CAnimation(const wstring& name, CAnimator* animator, CTexture* texture, const Vec2& count, int startIndex, int frameCount, float duration);
	CAnimation(const CAnimation& rhs);

public:
	~CAnimation();

public:
	void SetName(const wstring& name);
	const wstring& GetName();

	bool IsFinished();

	void SetFrame(int frameIndex);

	void Update();
	void Render(HDC hDC);
};

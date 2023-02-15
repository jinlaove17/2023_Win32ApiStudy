#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,

	COUNT
};

struct CamEffect
{
	CAM_EFFECT m_effect;

	float      m_duration; // 이펙트의 지속 시간
	float	   m_accTime;  // 이펙트의 누적 시간
};

class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2			 m_lookAt;	    // 현재 프레임에 카메라가 바라보는 위치
	Vec2			 m_finalLookAt; // 카메라가 바라 볼 최종 위치
	Vec2			 m_diff;	    // 해상도의 중심 위치와 현재 m_lookAt 간의 차이 값
					 			   	 
	CObject*		 m_target;	    // 카메라가 추적하는 객체
					 
	CTexture*		 m_veilTexture; // 페이드 효과를 구현하기 위한 검정색 가림막 텍스처
	queue<CamEffect> m_effectQueue;	// 추가된 이펙트를 저장하는 큐

public:
	void Init();

	void SetFinalLookAt(const Vec2& finalLookAt);
	const Vec2& GetFinalLookAt();

	void SetTarget(CObject* object);
	CObject* GetTarget();

	Vec2 WorldToScreen(const Vec2& worldPosition);
	Vec2 ScreenToWorld(const Vec2& screenPosition);

	void AddEffect(CAM_EFFECT effect, float duration);

	void Update();

	void Render(HDC hDC);
};

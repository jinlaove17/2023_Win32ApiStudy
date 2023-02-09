#pragma once

class CObject;

class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2     m_lookAt;	    // 현재 프레임에 카메라가 바라보는 위치
	Vec2     m_finalLookAt; // 카메라가 바라 볼 최종 위치
	Vec2	 m_diff;	    // 해상도의 중심 위치와 현재 m_lookAt 간의 차이 값
						   
	CObject* m_target;	    // 카메라가 추적하는 객체

public:
	void SetFinalLookAt(const Vec2& finalLookAt);
	const Vec2& GetFinalLookAt();

	void SetTarget(CObject* object);
	CObject* GetTarget();

	Vec2 WorldToScreen(const Vec2& worldPosition);
	Vec2 ScreenToWorld(const Vec2& screenPosition);

	void Update();
};

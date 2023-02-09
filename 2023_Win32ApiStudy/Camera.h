#pragma once

class CObject;

class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2     m_lookAt;	    // ���� �����ӿ� ī�޶� �ٶ󺸴� ��ġ
	Vec2     m_finalLookAt; // ī�޶� �ٶ� �� ���� ��ġ
	Vec2	 m_diff;	    // �ػ��� �߽� ��ġ�� ���� m_lookAt ���� ���� ��
						   
	CObject* m_target;	    // ī�޶� �����ϴ� ��ü

public:
	void SetFinalLookAt(const Vec2& finalLookAt);
	const Vec2& GetFinalLookAt();

	void SetTarget(CObject* object);
	CObject* GetTarget();

	Vec2 WorldToScreen(const Vec2& worldPosition);
	Vec2 ScreenToWorld(const Vec2& screenPosition);

	void Update();
};

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

	float      m_duration; // ����Ʈ�� ���� �ð�
	float	   m_accTime;  // ����Ʈ�� ���� �ð�
};

class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2			 m_lookAt;	    // ���� �����ӿ� ī�޶� �ٶ󺸴� ��ġ
	Vec2			 m_finalLookAt; // ī�޶� �ٶ� �� ���� ��ġ
	Vec2			 m_diff;	    // �ػ��� �߽� ��ġ�� ���� m_lookAt ���� ���� ��
					 			   	 
	CObject*		 m_target;	    // ī�޶� �����ϴ� ��ü
					 
	CTexture*		 m_veilTexture; // ���̵� ȿ���� �����ϱ� ���� ������ ������ �ؽ�ó
	queue<CamEffect> m_effectQueue;	// �߰��� ����Ʈ�� �����ϴ� ť

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

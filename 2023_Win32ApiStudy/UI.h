#pragma once
#include "Object.h"

class CUI : public CObject
{
private:
	bool m_isFixed;	     // ī�޶��� ������ ���� �ʴ� ������ ��ġ�� ��ġ�� UI
	bool m_isPressed;	 // ������ ���콺 ���� ��ư�� ���� ���� �ִ����� ���� ����
	bool m_isCursorOver; // ���� Ŀ���� ��ġ�� �� UI ���� �ִ����� ���� ����

public:
	CUI();
	CUI(const CUI& rhs);
	virtual ~CUI();

	virtual CUI* Clone() = 0;

	void SetFixed(bool isFixed);
	bool IsFixed();

	void SetPressed(bool isPressed);
	bool IsPressed();

	void CheckCursorOver();
	bool IsCursorOver();

	virtual void OnCursorOver();		    // ���� Ŀ���� ��ġ�� �� UI ���� ���� �� ȣ��
	virtual void OnCursorLeftButtonDown();  // ���� Ŀ���� ��ġ�� �� UI ���� �ְ�, ���� ���콺 ��ư�� ������ �� ȣ��
	virtual void OnCursorLeftButtonUp();    // ���� Ŀ���� ��ġ�� ��� ����, �� UI�� ������ ���Ȱ� ���� �����ӿ� ������ �� ȣ��
	virtual void OnCursorLeftButtonClick(); // ���� Ŀ���� ��ġ�� �� UI ���� �ְ�, ������ �������� ���� �����ӿ� ������ �� ȣ��

	virtual void Update();
	virtual void LateUpdate();

	virtual void Render(HDC hDC);
};

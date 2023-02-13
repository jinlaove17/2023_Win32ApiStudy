#pragma once
#include "Object.h"

class CUI : public CObject
{
private:
	bool m_isFixed;	     // 카메라의 영향을 받지 않는 고정된 위치에 배치된 UI
	bool m_isPressed;	 // 이전에 마우스 왼쪽 버튼이 눌린 적이 있는지에 대한 여부
	bool m_isCursorOver; // 현재 커서의 위치가 이 UI 위에 있는지에 대한 여부

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

	virtual void OnCursorOver();		    // 현재 커서의 위치가 이 UI 위에 있을 때 호출
	virtual void OnCursorLeftButtonDown();  // 현재 커서의 위치가 이 UI 위에 있고, 왼쪽 마우스 버튼이 눌렸을 때 호출
	virtual void OnCursorLeftButtonUp();    // 현재 커서의 위치에 상관 없이, 이 UI가 이전에 눌렸고 현재 프레임에 때졌을 때 호출
	virtual void OnCursorLeftButtonClick(); // 현재 커서의 위치가 이 UI 위에 있고, 이전에 눌렸으며 현재 프레임에 때졌을 때 호출

	virtual void Update();
	virtual void LateUpdate();

	virtual void Render(HDC hDC);
};

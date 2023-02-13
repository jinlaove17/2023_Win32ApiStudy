#pragma once
#include "UI.h"

class CButtonUI : public CUI
{
private:

public:
	CButtonUI();
	virtual ~CButtonUI();

	CLONE(CButtonUI);

	virtual void OnCursorOver();		    // 현재 커서의 위치가 이 UI 위에 있을 때 호출
	virtual void OnCursorLeftButtonDown();  // 현재 커서의 위치가 이 UI 위에 있고, 왼쪽 마우스 버튼이 눌렸을 때 호출
	virtual void OnCursorLeftButtonUp();    // 현재 커서의 위치에 상관 없이, 이 UI가 이전에 눌렸고 현재 프레임에 때졌을 때 호출
	virtual void OnCursorLeftButtonClick(); // 현재 커서의 위치가 이 UI 위에 있고, 이전에 눌렸으며 현재 프레임에 때졌을 때 호출
};

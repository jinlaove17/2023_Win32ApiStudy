#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI* m_focusedUI;
	CUI* m_targetUI;

public:
	void SetFocusedUI(CUI* ui);

	void Update();

private:
	CUI* GetFocusedUI();
	CUI* GetTargetUI(CUI* rootUI);
};

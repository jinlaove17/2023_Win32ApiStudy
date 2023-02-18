#pragma once

class CUI;

class CUIManager : public CSingleton<CUIManager>
{
	friend class CSingleton;

private:
	CUI* m_focusedUI;
	CUI* m_targetUI;

private:
	CUIManager();
	~CUIManager();

	CUI* GetFocusedUI();
	CUI* GetTargetUI(CUI* rootUI);

public:
	void SetFocusedUI(CUI* ui);

	void Update();
};

#pragma once
#include "UI.h"

class CButtonUI : public CUI
{
private:

public:
	CButtonUI();
	virtual ~CButtonUI();

	CLONE(CButtonUI);

	virtual void OnCursorOver();		    // ���� Ŀ���� ��ġ�� �� UI ���� ���� �� ȣ��
	virtual void OnCursorLeftButtonDown();  // ���� Ŀ���� ��ġ�� �� UI ���� �ְ�, ���� ���콺 ��ư�� ������ �� ȣ��
	virtual void OnCursorLeftButtonUp();    // ���� Ŀ���� ��ġ�� ��� ����, �� UI�� ������ ���Ȱ� ���� �����ӿ� ������ �� ȣ��
	virtual void OnCursorLeftButtonClick(); // ���� Ŀ���� ��ġ�� �� UI ���� �ְ�, ������ �������� ���� �����ӿ� ������ �� ȣ��
};

#include "pch.h"
#include "UIManager.h"

#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"

#include "UI.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::Update()
{
	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	const vector<CObject*>& uis = currentScene->GetGroupObject(GROUP_TYPE::UI);

	bool isLbuttonDown = KEY_TAP(KEY::LBUTTON);
	bool isLbuttonUp = KEY_AWAY(KEY::LBUTTON);

	for (int i = 0; i < uis.size(); ++i)
	{
		CUI* ui = (CUI*)uis[i];

		if (ui->IsCursorOver())
		{
			ui->OnCursorOver();

			if (isLbuttonDown)
			{
				ui->SetPressed(true);
				ui->OnCursorLeftButtonDown();
			}
			else if (isLbuttonUp)
			{
				ui->OnCursorLeftButtonUp();

				if (ui->IsPressed())
				{
					ui->OnCursorLeftButtonClick();
				}

				// ���� ��ư�� ����, ���� üũ�� �����Ѵ�.
				ui->SetPressed(false);
			}
		}
		else
		{
			// ���� ��ư�� ����, ���� üũ�� �����Ѵ�.
			if (isLbuttonUp)
			{
				ui->SetPressed(false);
			}
		}
	}
}

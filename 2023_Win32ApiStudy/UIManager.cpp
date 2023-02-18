#include "pch.h"
#include "UIManager.h"

#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"

#include "UI.h"

CUIManager::CUIManager() :
	m_focusedUI(),
	m_targetUI()
{
}

CUIManager::~CUIManager()
{
}

CUI* CUIManager::GetFocusedUI()
{
	// ������ ��Ŀ�� �� UI�� �����ϰ�, ����Ǿ����� Ȯ���Ѵ�.
	CUI* focusedUI = m_focusedUI;

	// ���� ��ư�� ������ ��, ��Ŀ���� ��ȯ�ȴ�.
	if (KEY_TAP(KEY::LBUTTON))
	{
		CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
		vector<CObject*>& uis = const_cast<vector<CObject*>&>(currentScene->GetGroupObject(GROUP_TYPE::UI));

		focusedUI = nullptr;

		for (int i = (int)uis.size() - 1; i >= 0; --i)
		{
			if (((CUI*)uis[i])->IsCursorOver())
			{
				focusedUI = (CUI*)uis[i];
				swap(uis[i], uis[uis.size() - 1]);

				break;
			}
		}
	}

	return focusedUI;
}

CUI* CUIManager::GetTargetUI(CUI* rootUI)
{
	// ������ Ÿ���� �� UI�� �����ϰ�, ����Ǿ����� Ȯ���Ѵ�.
	CUI* targetUI = m_targetUI;

	if (rootUI == nullptr)
	{
		targetUI = nullptr;
	}
	else
	{
		// ť�� �̿��Ͽ� rootUI���� ���� ��ȸ�Ѵ�.
		queue<CUI*> uiQueue;

		uiQueue.push(rootUI);

		while (!uiQueue.empty())
		{
			CUI* ui = uiQueue.front();

			uiQueue.pop();

			// ������ Ÿ���� �� UI�� ������ ���� ���·� Ÿ���� ���̶��, ���̻� �ڽ��� ��ȸ�� �ʿ� ���� Ÿ���� UI�� �����Ǿ�� �Ѵ�.
			if ((ui == m_targetUI) && ui->IsPressed())
			{
				targetUI = ui;

				break;
			}

			// ť���� ���� UI�� Ÿ���� ������ Ȯ���Ѵ�.
			// Ÿ���� �� UI�� �� �� �켱������ ���� ���� �� ���� ������ UI�̴�.
			if (ui->IsCursorOver())
			{
				targetUI = ui;
			}

			const vector<CObject*>& children = ui->GetChildren();

			for (int i = 0; i < children.size(); ++i)
			{
				uiQueue.push((CUI*)children[i]);
			}
		}
	}

	// ������ Ÿ�� UI�� ���ο� Ÿ�� UI�� �ٸ� ��쿡�� ���� üũ�� �����Ѵ�.
	if ((m_targetUI != nullptr) && (m_targetUI != targetUI))
	{
		m_targetUI->SetPressed(false);
	}

	return targetUI;
}

void CUIManager::SetFocusedUI(CUI* ui)
{
	// �̹� ��Ŀ�� �� UI�� ��Ŀ���Ϸ��� ���
	if (m_focusedUI == ui)
	{
		return;
	}

	// ��Ŀ�� UI ����
	m_focusedUI = ui;

	// ��Ŀ���� �����ϴ� ���
	if (m_focusedUI == nullptr)
	{
		return;
	}

	CScene* currentScene = CSceneManager::GetInstance()->GetCurrentScene();
	vector<CObject*>& uis = const_cast<vector<CObject*>&>(currentScene->GetGroupObject(GROUP_TYPE::UI));

	for (int i = 0; i < uis.size(); ++i)
	{
		if (m_focusedUI == uis[i])
		{
			swap(uis[i], uis[uis.size() - 1]);

			break;
		}
	}
}

void CUIManager::Update()
{
	// 1. ���� ��Ŀ�� �� UI�� Ȯ���Ѵ�.
	m_focusedUI = GetFocusedUI();

	// 2. ��Ŀ�� �� UI ��(�ڽ� ����)���� ���� Ÿ���� �� UI�� Ȯ���Ѵ�.
	m_targetUI = GetTargetUI(m_focusedUI);

	if (m_targetUI != nullptr)
	{
		// Ÿ���� �� UI�� GetTargetUI() �Լ����� �̹� Ŀ���� ���� ���������� �˻������Ƿ�, ��ٷ� �Լ��� ȣ���Ѵ�.
		m_targetUI->OnCursorOver();

		if (KEY_TAP(KEY::LBUTTON))
		{
			m_targetUI->SetPressed(true);
			m_targetUI->OnCursorLeftButtonDown();
		}
		else if (KEY_AWAY(KEY::LBUTTON))
		{
			m_targetUI->OnCursorLeftButtonUp();

			if (m_targetUI->IsPressed())
			{
				m_targetUI->OnCursorLeftButtonClick();
			}

			// ���� ��ư�� ����, ���� üũ�� �����Ѵ�.
			m_targetUI->SetPressed(false);
		}
	}
}

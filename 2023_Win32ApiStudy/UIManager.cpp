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
	// 기존에 포커싱 된 UI를 저장하고, 변경되었는지 확인한다.
	CUI* focusedUI = m_focusedUI;

	// 왼쪽 버튼이 눌렸을 때, 포커싱이 전환된다.
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
	// 기존에 타겟팅 된 UI를 저장하고, 변경되었는지 확인한다.
	CUI* targetUI = m_targetUI;

	if (rootUI == nullptr)
	{
		targetUI = nullptr;
	}
	else
	{
		// 큐를 이용하여 rootUI부터 레벨 순회한다.
		queue<CUI*> uiQueue;

		uiQueue.push(rootUI);

		while (!uiQueue.empty())
		{
			CUI* ui = uiQueue.front();

			uiQueue.pop();

			// 이전에 타겟팅 된 UI가 아직도 눌린 상태로 타겟팅 중이라면, 더이상 자식을 순회할 필요 없이 타겟팅 UI는 유지되어야 한다.
			if ((ui == m_targetUI) && ui->IsPressed())
			{
				targetUI = ui;

				break;
			}

			// 큐에서 꺼낸 UI가 타겟팅 중인지 확인한다.
			// 타겟팅 된 UI들 중 더 우선순위가 높은 것은 더 하위 계층의 UI이다.
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

	// 이전의 타겟 UI가 새로운 타겟 UI와 다른 경우에는 눌림 체크를 해제한다.
	if ((m_targetUI != nullptr) && (m_targetUI != targetUI))
	{
		m_targetUI->SetPressed(false);
	}

	return targetUI;
}

void CUIManager::SetFocusedUI(CUI* ui)
{
	// 이미 포커싱 된 UI를 포커싱하려는 경우
	if (m_focusedUI == ui)
	{
		return;
	}

	// 포커싱 UI 변경
	m_focusedUI = ui;

	// 포커싱을 해제하는 경우
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
	// 1. 현재 포커싱 된 UI를 확인한다.
	m_focusedUI = GetFocusedUI();

	// 2. 포커싱 된 UI 내(자식 포함)에서 실제 타겟팅 된 UI를 확인한다.
	m_targetUI = GetTargetUI(m_focusedUI);

	if (m_targetUI != nullptr)
	{
		// 타겟팅 된 UI는 GetTargetUI() 함수에서 이미 커서가 오버 상태인지를 검사했으므로, 곧바로 함수를 호출한다.
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

			// 왼쪽 버튼을 떼면, 눌림 체크를 해제한다.
			m_targetUI->SetPressed(false);
		}
	}
}

#include "pch.h"
#include "InputManager.h"

CInputManager::CInputManager() :
	m_virtualKey{ VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_MENU, VK_CONTROL, VK_LSHIFT, VK_SPACE, VK_RETURN, VK_ESCAPE, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' },
	m_keyInfo{}
{
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init()
{
	for (int i = 0; i < (int)KEY::COUNT; ++i)
	{
		m_keyInfo[i].m_isPressed = false;
		m_keyInfo[i].m_state = KEY_STATE::NONE;
	}
}

KEY_STATE CInputManager::GetKeyState(KEY key)
{
	return m_keyInfo[(int)key].m_state;
}

void CInputManager::Update()
{
	// ���� �����찡 ��Ŀ�� �������� �˾Ƴ���.
	HWND hWnd = GetFocus();

	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::COUNT; ++i)
		{
			// �̹� �����ӿ� Ű�� ���ȴ�.
			if (GetAsyncKeyState(m_virtualKey[i]) & 0x8000)
			{
				// ���� �����ӿ��� Ű�� ���� �־���.
				if (m_keyInfo[i].m_isPressed)
				{
					m_keyInfo[i].m_state = KEY_STATE::HOLD;
				}
				else
				{
					m_keyInfo[i].m_state = KEY_STATE::TAP;
				}

				m_keyInfo[i].m_isPressed = true;
			}
			else
			{
				// ���� �����ӿ� Ű�� ���� �־���.
				if (m_keyInfo[i].m_isPressed)
				{
					m_keyInfo[i].m_state = KEY_STATE::AWAY;
				}
				else
				{
					m_keyInfo[i].m_state = KEY_STATE::NONE;
				}

				m_keyInfo[i].m_isPressed = false;
			}
		}
	}
	// ������ ��Ŀ���� ������ ���
	else
	{
		for (int i = 0; i < (int)KEY::COUNT; ++i)
		{
			switch (m_keyInfo[i].m_state)
			{
			case KEY_STATE::TAP:
			case KEY_STATE::HOLD:
				m_keyInfo[i].m_state = KEY_STATE::AWAY;
				break;
			case KEY_STATE::AWAY:
				m_keyInfo[i].m_state = KEY_STATE::NONE;
				break;
			}

			m_keyInfo[i].m_isPressed = false;
		}
	}
}

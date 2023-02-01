#pragma once

enum class KEY
{
	UP, DOWN, LEFT, RIGHT, ALT, CTRL, SHIFT, SPACE, ENTER, ESC,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

	COUNT
};

enum class KEY_STATE
{
	NONE, // �������� ������ �ʾҰ�, ���絵 ������ ���� ����
	TAP,  // ������ ������ �ʾҰ�, ���� ���� ����
	HOLD, // ������ ���Ȱ�, ���絵 ���� ����
	AWAY, // ������ ���Ȱ�, ���� ���� ����
};

struct KeyInfo
{
	bool	  m_isPressed; // ���� �����ӿ� ���ȴ����� ���� ����
	KEY_STATE m_state;     // ���� Ű�� ����
};

// 1. ������ ����ȭ
//   - ���� ������ ������ ���� Ű�� ���ؼ�, ������ �̺�Ʈ�� �������� �Ѵ�.
// 2. Ű �Է� ���� ó��
//    - Tap, Hold, Away
class CInputManager
{
	SINGLETON(CInputManager);

private:
	// ���� Ű ���� KEY�� ������ ��ġ�ؾ� �Ѵ�.
	int     m_virtualKey[(int)KEY::COUNT];

	KeyInfo m_keyInfo[(int)KEY::COUNT];

public:
	void Init();

	KEY_STATE GetKeyState(KEY key);

	void Update();
};

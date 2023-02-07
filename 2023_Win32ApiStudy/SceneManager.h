#pragma once

class CScene;

class CSceneManager
{
	friend class CEventManager;

	SINGLETON(CSceneManager);

private:
	CScene* m_scenes[(int)SCENE_TYPE::COUNT];
	CScene* m_currentScene;

public:
	void Init();

	CScene* GetCurrentScene();

	void Update();
	void Render(HDC hDC);

private:
	// ���� ���� ��ü�ϴ� ChangeScene() �Լ��� ������ CEventManager�� ȣ���� �� �ֵ��� �����.
	void ChangeScene(SCENE_TYPE scene);
};

#pragma once

class CScene;

class CSceneManager : public CSingleton<CSceneManager>
{
	friend class CSingleton;
	friend class CEventManager;

private:
	CScene* m_scenes[(int)SCENE_TYPE::COUNT];
	CScene* m_currentScene;

private:
	CSceneManager();
	~CSceneManager();

	// ���� ���� ��ü�ϴ� ChangeScene() �Լ��� ������ CEventManager�� ȣ���� �� �ֵ��� �����.
	void ChangeScene(SCENE_TYPE scene);

public:
	void Init();

	CScene* GetCurrentScene();

	void Update();

	void Render(HDC hDC);
};

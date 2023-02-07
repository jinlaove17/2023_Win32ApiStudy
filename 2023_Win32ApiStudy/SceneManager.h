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
	// 실제 씬을 교체하는 ChangeScene() 함수는 오로지 CEventManager만 호출할 수 있도록 만든다.
	void ChangeScene(SCENE_TYPE scene);
};

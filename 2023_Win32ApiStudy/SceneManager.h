#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

private:
	CScene* m_scenes[(int)SCENE_TYPE::COUNT];
	CScene* m_currentScene;

public:
	void Init();

	void Update();
	void Render(HDC hDC);
};

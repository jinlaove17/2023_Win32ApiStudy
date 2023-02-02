#pragma once

class CObject;

class CScene
{
private:
	wstring			 m_name;

	vector<CObject*> m_objects[(int)GROUP_TYPE::COUNT];

public:
	CScene();
	virtual ~CScene();

	void SetName(const wstring& name);
	const wstring& GetName();

	void AddObject(GROUP_TYPE group, CObject* object);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void Update();
	void Render(HDC hDC);
};

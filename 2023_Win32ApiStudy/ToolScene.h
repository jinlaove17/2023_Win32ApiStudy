#pragma once
#include "Scene.h"

class CToolScene : public CScene
{
private:
	int m_tileXCount;
	int m_tileYCount;

public:
	CToolScene();
	virtual ~CToolScene();

	void ArrangeTiles(int tileXCount, int tileYCount);

	virtual void SaveData();
	virtual void LoadData();

	virtual void Enter();
	virtual void Exit();
	
	virtual void Update();
};

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

	virtual void Enter();
	virtual void Exit();

	void ArrangeTiles(int tileXCount, int tileYCount);

	virtual void Update();
};

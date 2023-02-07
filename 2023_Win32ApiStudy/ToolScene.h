#pragma once
#include "Scene.h"

class CToolScene : public CScene
{
public:
	CToolScene();
	virtual ~CToolScene();

	virtual void Enter();
	virtual void Exit();

	virtual void Update();
};

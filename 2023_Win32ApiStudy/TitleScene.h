#pragma once
#include "Scene.h"

class CTitleScene : public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();

	virtual void SaveData();
	virtual void LoadData();

	virtual void Enter();
	virtual void Exit();

	virtual void Update();
};

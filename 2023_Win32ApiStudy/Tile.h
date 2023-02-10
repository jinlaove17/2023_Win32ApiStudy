#pragma once
#include "Object.h"

class CTile : public CObject
{
private:
	int m_index;

public:
	CTile();
	virtual ~CTile();

	CLONE(CTile);

	void SetIndex(int index);
	int GetIndex();

	virtual void Update();

	virtual void Render(HDC hDC);
};

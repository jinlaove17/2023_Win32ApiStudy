#pragma once
#include "Object.h"

class CComponent
{
	friend class CObject;

private:
	CObject* m_owner;

protected:
	CComponent();
	virtual ~CComponent();

public:
	CObject* GetOwner();

	virtual void Update() = 0;

	virtual void Render(HDC hDC) = 0;
};

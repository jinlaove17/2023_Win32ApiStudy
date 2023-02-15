#include "pch.h"
#include "Tile.h"

#include "Texture.h"

#include "Camera.h"

CTile::CTile() :
	m_index()
{
}

CTile::~CTile()
{
}

void CTile::SetIndex(int index)
{
	CTexture* texture = GetTexture();
	const Vec2& scale = GetScale();
	int xCount = (int)(texture->GetWidth() / scale.m_x);
	int yCount = (int)(texture->GetHeight() / scale.m_y);

	if ((index < 0) || (index >= xCount * yCount))
	{
		index = 0;
	}

	m_index = index;
}

int CTile::GetIndex()
{
	return m_index;
}

void CTile::Update()
{
}

void CTile::Render(HDC hDC)
{
	if (CCamera::GetInstance()->IsVisible(this))
	{
		Vec2 position = CCamera::GetInstance()->WorldToScreen(GetPosition());
		const Vec2& scale = GetScale();

		CTexture* texture = GetTexture();
		int xCount = (int)(texture->GetWidth() / scale.m_x);

		BitBlt(hDC,
			(int)(position.m_x),
			(int)(position.m_y),
			(int)(scale.m_x),
			(int)(scale.m_y),
			texture->GetDC(),
			(int)(scale.m_x * (m_index % xCount)),
			(int)(scale.m_y * (m_index / xCount)),
			SRCCOPY);
	}
}

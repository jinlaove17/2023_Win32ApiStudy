#pragma once

struct Vec2
{
public:
	float m_x;
	float m_y;

public:
	Vec2() :
		m_x(),
		m_y()
	{
	}

	Vec2(float x, float y) :
		m_x(x),
		m_y(y)
	{
	}

	Vec2(int x, int y) :
		m_x((float)x),
		m_y((float)y)
	{
	}

	Vec2(LONG x, LONG y) :
		m_x((float)x),
		m_y((float)y)
	{
	}

	Vec2(const SIZE& size) :
		m_x((float)size.cx),
		m_y((float)size.cy)
	{
	}

	Vec2& operator =(const SIZE& size)
	{
		m_x = (float)size.cx;
		m_y = (float)size.cy;

		return *this;
	}
};

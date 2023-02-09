#pragma once

// RAII�� Ȱ���Ͽ� GDI�� �����ϴ� ��ü
struct GDIObject
{
public:
	// ���� ����ϴ� GDI ��ü
	static HPEN    m_hPens[(int)PEN_TYPE::COUNT];
	static HBRUSH  m_hBrushes[(int)BRUSH_TYPE::COUNT];

	HDC			   m_hDC;
	HPEN		   m_hOldPen;
	HBRUSH		   m_hOldBrush;

public:
	GDIObject(HDC hDC, PEN_TYPE penType) :
		m_hDC(hDC),
		m_hOldPen(),
		m_hOldBrush()
	{
		m_hOldPen = (HPEN)SelectObject(hDC, m_hPens[(int)penType]);
	}

	GDIObject(HDC hDC, BRUSH_TYPE brushType) :
		m_hDC(hDC),
		m_hOldPen(),
		m_hOldBrush()
	{
		m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrushes[(int)brushType]);
	}

	GDIObject(HDC hDC, PEN_TYPE penType, BRUSH_TYPE brushType) :
		m_hDC(hDC),
		m_hOldPen(),
		m_hOldBrush()
	{
		m_hOldPen = (HPEN)SelectObject(hDC, m_hPens[(int)penType]);
		m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrushes[(int)brushType]);
	}

	~GDIObject()
	{
		if (m_hOldPen != nullptr)
		{
			SelectObject(m_hDC, m_hOldPen);
		}

		if (m_hOldBrush != nullptr)
		{
			SelectObject(m_hDC, m_hOldBrush);
		}
	}
};

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

	// �Լ��� �ڿ� const�� ������ ������ const Vec2& Ÿ���� ������ operator�� ������ �� ����.
	Vec2 operator +(const Vec2& other) const
	{
		return Vec2(m_x + other.m_x, m_y + other.m_y);
	}

	Vec2& operator +=(const Vec2& other)
	{
		m_x += other.m_x;
		m_y += other.m_y;

		return *this;
	}

	Vec2 operator -(const Vec2& other) const
	{
		return Vec2(m_x - other.m_x, m_y - other.m_y);
	}

	Vec2 operator *(int i)
	{
		return Vec2(i * m_x, i * m_y);
	}

	Vec2 operator *(float f)
	{
		return Vec2(f * m_x, f * m_y);
	}

	Vec2 operator /(float f)
	{
		assert(f != 0.0f);

		return Vec2(m_x / f, m_y / f);
	}

	float Length()
	{
		return sqrtf(m_x * m_x + m_y * m_y);
	}

	Vec2& Normalize()
	{
		float length = Length();

		assert(length != 0.0f);

		m_x /= length;
		m_y /= length;

		return *this;
	}
};

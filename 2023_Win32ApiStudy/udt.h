#pragma once

// 싱글톤 패턴을 위한 최상위 객체
template <typename T>
class CSingleton
{
protected: // 이 객체를 상속 받은 자식 객체에서 부모인 이 클래스의 생성자를 호출해야하므로, 접근 지정자를 protected로 설정하였다.
	CSingleton()
	{
	}

	~CSingleton()
	{
	}

public:
	static T* GetInstance()
	{
		static T instance = {};

		return &instance;
	}
};

// RAII를 활용하여 GDI를 세팅하는 객체
class CGdiController
{
private:
	// 자주 사용하는 GDI 객체
	static HPEN    m_hPens[(int)PEN_TYPE::COUNT];
	static HBRUSH  m_hBrushes[(int)BRUSH_TYPE::COUNT];

	HDC			   m_hDC;
	HPEN		   m_hOldPen;
	HBRUSH		   m_hOldBrush;

public:
	CGdiController(HDC hDC, PEN_TYPE penType) :
		m_hDC(hDC),
		m_hOldPen(),
		m_hOldBrush()
	{
		m_hOldPen = (HPEN)SelectObject(hDC, m_hPens[(int)penType]);
	}

	CGdiController(HDC hDC, BRUSH_TYPE brushType) :
		m_hDC(hDC),
		m_hOldPen(),
		m_hOldBrush()
	{
		m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrushes[(int)brushType]);
	}

	CGdiController(HDC hDC, PEN_TYPE penType, BRUSH_TYPE brushType) :
		m_hDC(hDC),
		m_hOldPen(),
		m_hOldBrush()
	{
		m_hOldPen = (HPEN)SelectObject(hDC, m_hPens[(int)penType]);
		m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrushes[(int)brushType]);
	}

	~CGdiController()
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

	Vec2 operator -()
	{
		return Vec2(-m_x, -m_y);
	}

	Vec2& operator =(const SIZE& size)
	{
		m_x = (float)size.cx;
		m_y = (float)size.cy;

		return *this;
	}

	// 함수명 뒤에 const를 붙히지 않으면 const Vec2& 타입의 변수에 operator를 적용할 수 없다.
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

	Vec2& operator -=(const Vec2& other)
	{
		m_x -= other.m_x;
		m_y -= other.m_y;

		return *this;
	}

	Vec2 operator *(int i)
	{
		return Vec2(i * m_x, i * m_y);
	}

	Vec2 operator *(float f)
	{
		return Vec2(f * m_x, f * m_y);
	}

	Vec2& operator *=(float f)
	{
		m_x *= f;
		m_y *= f;

		return *this;
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

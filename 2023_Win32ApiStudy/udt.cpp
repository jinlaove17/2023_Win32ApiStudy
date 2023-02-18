#include "pch.h"
#include "udt.h"

HPEN CGdiController::m_hPens[(int)PEN_TYPE::COUNT] =
{
	(HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0)),
	(HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0)),
	(HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255))
};

HBRUSH CGdiController::m_hBrushes[(int)BRUSH_TYPE::COUNT] =
{
	(HBRUSH)GetStockObject(HOLLOW_BRUSH),
	(HBRUSH)GetStockObject(BLACK_BRUSH)
};

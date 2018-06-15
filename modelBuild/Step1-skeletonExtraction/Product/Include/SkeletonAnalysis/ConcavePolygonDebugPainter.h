// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   11/17/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CONCAVEPOLYGONDEBUGPAINTER_173711172007_H
#define CONCAVEPOLYGONDEBUGPAINTER_173711172007_H

#include "ConcavePolygon2.h"

WING_BEGIN

class ConcavePolygonDebugPainter
{
public:
	AnalysisExport ConcavePolygonDebugPainter();
	AnalysisExport virtual ~ConcavePolygonDebugPainter();

	AnalysisExport void Clear();
	AnalysisExport void Build(const ConcavePolygon2& polygon);
	AnalysisExport void Build(const ConcavePolygon2& polygon, size_t newSize);

	AnalysisExport void Paint(HDC hdc, HPEN hPen, int x, int y);
	AnalysisExport void PaintConvex(
		const ConcavePolygon2& polygon, 
		HDC hdc, HPEN hPen, int x, int y);

	inline int GetX() const;
	inline int GetY() const;

	inline void SetX(int x);
	inline void SetY(int y);

private:
	AnalysisExport void CleanMembers();

private:
	ConcavePolygonDebugPainter(const ConcavePolygonDebugPainter& from);
	ConcavePolygonDebugPainter& operator = (const ConcavePolygonDebugPainter& from);

private:
	int m_x;
	int m_y;
	TDynArray<Vector2> m_PaintVertices;
};

inline int ConcavePolygonDebugPainter::GetX() const
{
	return m_x;
}

inline int ConcavePolygonDebugPainter::GetY() const
{
	return m_y;
}

inline void ConcavePolygonDebugPainter::SetX(int x)
{
	m_x = x;
}

inline void ConcavePolygonDebugPainter::SetY(int y)
{
	m_y = y;
}

WING_END

#endif // #ifndef CONCAVEPOLYGONDEBUGPAINTER_173711172007_H
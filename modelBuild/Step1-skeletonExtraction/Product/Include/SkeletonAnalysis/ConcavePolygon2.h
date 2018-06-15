// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   11/15/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CONCAVEPOLYGON2_93911152007_H
#define CONCAVEPOLYGON2_93911152007_H

#include "AnalysisBase.h"
#include "Geometry/AxisAlignedBox2.h"
#include <windows.h>

WING_BEGIN

class ConcavePolygon2
{
public:
	AnalysisExport ConcavePolygon2();
	AnalysisExport ConcavePolygon2(const ConcavePolygon2& from);
	AnalysisExport ~ConcavePolygon2();

	AnalysisExport ConcavePolygon2& operator = (const ConcavePolygon2& from);
	AnalysisExport void Swap(ConcavePolygon2& from);

	AnalysisExport bool Load(const IBufPtr& pStream);
	AnalysisExport bool Save(const OBufPtr& pStream) const;

	AnalysisExport void Clear();
	AnalysisExport void Insert(size_t index, const Vector2& pos);
	AnalysisExport void Erase(size_t index);
	AnalysisExport void Erase(size_t index, size_t count);
	AnalysisExport void Append(const Vector2& pos);
	AnalysisExport void Invert();

	AnalysisExport bool IsInBound(size_t leftBound, size_t rightBound, size_t index) const;
	AnalysisExport bool WeldRecursiveNearbyVertex(real nearByPercent);
	AnalysisExport void AdjustDirection();

	AnalysisExport void BuildBoundingBox(OUT AxisAlignBox2& bbox);
	AnalysisExport void TransformToFirstQuadrant();
	AnalysisExport void Scale(real sx, real sy);
	AnalysisExport void Transform(real tx, real ty);

	inline size_t GetVertexCount() const;
	inline const Vector2& GetVertex(size_t i) const;
	inline size_t GetPrevIndex(size_t i) const;
	inline size_t GetNextIndex(size_t i) const;
	inline const Vector2& GetPrevVertex(size_t i) const;
	inline const Vector2& GetNextVertex(size_t i) const;

	inline size_t IncreaseIndex(size_t i, size_t increase) const;
	inline size_t DecreaseIndex(size_t i, size_t decrease) const;

	inline size_t GetConvexCount() const;
	inline const TriangleI& GetConvexTriangle(size_t i) const;

	inline real GetRoundness() const;
	inline real GetPseudoRadius() const;
	inline real GetArea() const;
	inline real GetPerimeter() const;

private:
	AnalysisExport void CleanMembers();
	inline void DirtyConvexPolygonCache();
	AnalysisExport bool _WeldNearbyVertex(real nearbyDistanceSq);
	AnalysisExport void UpdateConvexPolygonCache() const;
	AnalysisExport bool RebuildConvexPolygons();
	AnalysisExport real CalculateArea();
	AnalysisExport real CalculatePerimeter();
	AnalysisExport real CalculateRoundness(real perimeter, real actuallArea);

private:
	vector<Vector2> m_vertices;
	bool m_bConvexDirty;
	real m_roundness;
	real m_radius;
	real m_area;
	real m_perimeter;
	vector<TriangleI> m_ConvexPolygons;
};

AnalysisExport bool operator << (CBinaryOStream& stream, const ConcavePolygon2& polygon);
AnalysisExport bool operator >> (CBinaryIStream& stream, ConcavePolygon2& polygon);

inline size_t ConcavePolygon2::GetVertexCount() const
{
	return m_vertices.size();
}

inline const Vector2& ConcavePolygon2::GetVertex(size_t i) const
{
	return m_vertices[i];
}

inline size_t ConcavePolygon2::GetPrevIndex(size_t i) const
{
	DbgAssert(m_vertices.size() > 0);
	return (i+m_vertices.size()-1)%(m_vertices.size());
}

inline size_t ConcavePolygon2::GetNextIndex(size_t i) const
{
	DbgAssert(m_vertices.size() > 0);
	return (i+1)%(m_vertices.size());
}

inline const Vector2& ConcavePolygon2::GetPrevVertex(size_t i) const
{
	DbgAssert(m_vertices.size() > 0);
	return m_vertices[(i+m_vertices.size()-1)%(m_vertices.size())];
}

inline const Vector2& ConcavePolygon2::GetNextVertex(size_t i) const
{
	DbgAssert(m_vertices.size() > 0);
	return m_vertices[(i+1)%(m_vertices.size())];
}

inline size_t ConcavePolygon2::IncreaseIndex(size_t i, size_t increase) const
{
	DbgAssert(m_vertices.size() > 0);
	return (i+increase)%(m_vertices.size());
}

inline size_t ConcavePolygon2::DecreaseIndex(size_t i, size_t decrease) const
{
	DbgAssert(m_vertices.size() > 0);
	return (i+m_vertices.size()-decrease)%(m_vertices.size());
}

inline size_t ConcavePolygon2::GetConvexCount() const
{
	if (m_bConvexDirty)
	{
		UpdateConvexPolygonCache();
	}

	return m_ConvexPolygons.size();
}

inline const TriangleI& ConcavePolygon2::GetConvexTriangle(size_t i) const
{
	if (m_bConvexDirty)
	{
		UpdateConvexPolygonCache();
	}

	return m_ConvexPolygons[i];
}


inline real ConcavePolygon2::GetRoundness() const
{
	if (m_bConvexDirty)
	{
		UpdateConvexPolygonCache();
	}

	return m_roundness;
}

inline real ConcavePolygon2::GetPseudoRadius() const
{
	if (m_bConvexDirty)
	{
		UpdateConvexPolygonCache();
	}

	return m_radius;
}

inline real ConcavePolygon2::GetArea() const
{
	if (m_bConvexDirty)
	{
		UpdateConvexPolygonCache();
	}

	return m_area;
}

inline real ConcavePolygon2::GetPerimeter() const
{
	if (m_bConvexDirty)
	{
		UpdateConvexPolygonCache();
	}

	return m_perimeter;
}


inline void ConcavePolygon2::DirtyConvexPolygonCache()
{
	m_bConvexDirty = true;
}

WING_END

#endif // #ifnef CONCAVEPOLYGON2_93911152007_H
// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/09/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CDISKCUTPLANE_14371292007_H
#define CDISKCUTPLANE_14371292007_H

#include "Mesh/TriMesh.h"
#include "CMeshGroup.h"
#include "ConcavePolygon2.h"
#include "CRoughPolygon.h"
#include "Mesh/CVectorRenderer.h"

WING_BEGIN

class CDiskCutPlane
{
public:
	AnalysisExport CDiskCutPlane();
	AnalysisExport virtual ~CDiskCutPlane();

	AnalysisExport void Destroy();
	AnalysisExport void SetEpsilon(real epsilon);

	AnalysisExport void BeginCut(
		const Vector3& keyPoint, 
		// y axis
		const Vector3& faceNormal, 
		// x axis
		const Vector3& referenceDir);
	AnalysisExport bool Cut(
		const Vector3& v1, 
		const Vector3& v2, 
		const Vector3& v3, 
		size_t faceIndex);
	AnalysisExport bool EndCut();
	AnalysisExport void BuildAverageDotValue(const CMeshGroup& meshGroup);
	AnalysisExport real GetAverageDotValue() const;
	AnalysisExport real GetWeight() const;

	AnalysisExport real GetRoundness() const;
	AnalysisExport real GetRadius() const;
	AnalysisExport const Vector3& GetNormal() const;
	AnalysisExport Vector3 CalculateBaryCenter() const;

	AnalysisExport void Render(const RenderSystemPtr& pRenderSystem);

	inline size_t GetCircleFaceCount() const;
	inline size_t GetCircleFace(size_t circleIndex) const;

	AnalysisExport const ConcavePolygon2& GetConcavePolygon() const;

private:
	AnalysisExport void DirtyConcavePolygon();
	AnalysisExport void BuildConcavePolygon() const;
	AnalysisExport void BuildConcavePolygon();

	AnalysisExport void DirtyVisualizeData();
	AnalysisExport void BuildVisualizeData();

private:
	AnalysisExport void CleanMembers();

private:
	CDiskCutPlane(const CDiskCutPlane& from);
	CDiskCutPlane& operator = (const CDiskCutPlane& from);

private:
	real m_epsilon;

	const Vector3* m_pKeyPoint;
	const Vector3* m_pFaceNormal;
	Vector3 m_referenceDir;

	Plane m_plane;
	CRoughPolygon m_roughPolygon;

	real m_averageDotValue;

private:
	bool m_bConcavePolygonDirty;
	ConcavePolygon2 m_concavePolygon;

private:
	bool m_bVisualizDirty;
	vector<UserPrimitiveVertex> m_cutPlane;
	vector<UserPrimitiveVertex> m_cutPlaneLine;
	CVectorRenderer m_vecFaceDir;
	CVectorRenderer m_vecReferenceDir;
};

inline size_t CDiskCutPlane::GetCircleFaceCount() const
{
	return m_roughPolygon.GetCircleVertCount();
}

inline size_t CDiskCutPlane::GetCircleFace(size_t circleIndex) const
{
	return m_roughPolygon.GetFaceIndex(circleIndex);
}

WING_END

#endif // #ifndef CDISKCUTPLANE_14371292007_H

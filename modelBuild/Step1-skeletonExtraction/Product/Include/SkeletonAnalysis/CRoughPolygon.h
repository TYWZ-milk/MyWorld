// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/08/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CROUGHPOLYGON_20071282007_H
#define CROUGHPOLYGON_20071282007_H

#include "ConcavePolygon2.h"
#include "RenderSystem/IRenderDevice.h"

WING_BEGIN

class CRoughPolygon
{
public:
	AnalysisExport CRoughPolygon();
	AnalysisExport virtual ~CRoughPolygon();

	AnalysisExport void Destroy();

	AnalysisExport void Reserve(size_t vertCount);

	AnalysisExport void AddPointPair(
		const Vector3& v1, 
		const Vector3& v2, 
		size_t faceIndex, 
		real epsilon);

	// we only consider to connect a circle from the first vertex
	AnalysisExport bool ConnectCircle(real epsilon);

	AnalysisExport size_t GetCircleVertCount() const;

	AnalysisExport const Vector3& GetCircleVert(size_t circleIndex) const;

	AnalysisExport size_t GetFaceIndex(size_t circleIndex) const;

	AnalysisExport Vector3 CalculateBaryCenter() const;

	AnalysisExport void Render(const RenderSystemPtr& pRenderSystem);

private:
	AnalysisExport void DirtyVisualizeData();

	AnalysisExport void BuildVisualizeData();

private:
	AnalysisExport void CleanMembers();

private:
	vector<Vector3> m_roughPointPair;
	vector<uint32> m_circlePoints;
	vector<size_t> m_faceIndices;

	// temporary used
	vector<uint8> m_deleted;

private:
	bool m_bVisualizeDataDirty;
	vector<UserPrimitiveVertex> m_visualizeVertices;
};

WING_END

#endif // #ifndef CROUGHPOLYGON_20071282007_H
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

#ifndef CDISKCUTTER_13421292007_H
#define CDISKCUTTER_13421292007_H

#include "CDiskCutPlane.h"

WING_BEGIN

class CDiskCutter
{
public:
	AnalysisExport CDiskCutter();
	AnalysisExport virtual ~CDiskCutter();

	AnalysisExport void Destroy();

	AnalysisExport void SetEpsilon(real epsilon);

	AnalysisExport bool Cut(
		TriMesh& mesh, 
		const CMeshGroup& meshGroup, 
		const Vector3& keyPoint, 
		size_t nTriangleIndex);

	AnalysisExport real GetWeight() const;
	AnalysisExport real GetRoundness() const;
	AnalysisExport real GetRadius() const;
	AnalysisExport Vector3 CalculateBaryCenter() const;
	AnalysisExport const Vector3& GetNormal() const;

	AnalysisExport size_t GetBestEdgeCutPlane() const;
	AnalysisExport size_t GetEdgeCutPlaneCount() const;
	AnalysisExport void RenderEdgeCutPlane(const RenderSystemPtr& pRenderSystem, size_t i);
	AnalysisExport size_t GetBestTryCutPlane() const;
	AnalysisExport size_t GetTryCutPlaneCount() const;
	AnalysisExport bool IsEdgeCutPlaneBest() const;
	AnalysisExport void RenderTryCutPlane(const RenderSystemPtr& pRenderSystem, size_t i);
	AnalysisExport const ConcavePolygon2& GetEdgeCutPlanePolygon(size_t edgeCutPlaneIndex) const;
	AnalysisExport const ConcavePolygon2& GetTryCutPlanePolygon(size_t tryCutPlaneIndex) const;

private:
	CDiskCutter(const CDiskCutter& from);
	CDiskCutter& operator = (const CDiskCutter& from);

private:
	AnalysisExport void CleanMembers();
	AnalysisExport bool CutMesh(
		IN OUT CDiskCutPlane& cutPlane, 
		IN TriMesh& mesh, 
		IN const CMeshGroup& meshGroup, 
		IN size_t nTriangleIndex);
	AnalysisExport void BuildRotateAxisMatrix(
		OUT Matrix44& matIdentity, 
		IN const Vector3& vAxis, 
		IN real sineValue, 
		IN real cosValue);
	AnalysisExport void MarkBestCircleFaces(TriMesh& mesh);

private:
	enum 
	{
		TryCutCount = 32, 
	};

private:
	// temporary members

	real m_epsilon;

	// 切割的关键点
	Vector3 m_keyPoint;

	// 选中的面的法线方向
	Vector3 m_faceNormal;
	// 选中面的三条边的方向
	Vector3 m_edgeDirs[3];

	// 将边和面的法线构建出来的用于切割的面
	CDiskCutPlane m_edgeCutPlane[3];

	size_t m_tryCutPlaneCount;
	CDiskCutPlane m_cutPlane[TryCutCount];

	Matrix44 m_matRotation;
	real m_sinAngles[TryCutCount];
	real m_cosAngles[TryCutCount];

	// 最佳的切割结果
	size_t m_bestEdgeCutPlane;
	size_t m_bestTryCutPlane;
	CDiskCutPlane* m_pBestCutPlane;

	// 以下两个变量标记哪些面修改过了
	TDynArray<uint32> m_adjoiningFaces;
	TDynArray<uint32> m_flagChangedFaces;
};

WING_END

#endif // #ifndef CDISKCUTTER_13421292007_H
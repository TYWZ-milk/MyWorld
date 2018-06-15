// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/10/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CTREESKELETONANALYSER_144212102007_H
#define CTREESKELETONANALYSER_144212102007_H

#include "CDiskCutter.h"
#include "CLimbPicker.h"
#include "CLimbConnector.h"

WING_BEGIN

class CTreeSkeletonAnalyser
{
public:
	AnalysisExport CTreeSkeletonAnalyser();
	AnalysisExport virtual ~CTreeSkeletonAnalyser();

	AnalysisExport void Destroy();

	AnalysisExport bool LoadObjFile(const TCHAR* objFileName);
	AnalysisExport bool LoadTriFile(const TCHAR* triFileName);
	AnalysisExport const AxisAlignBox& GetBoundingBox() const;
	AnalysisExport const TCHAR* GetRawMeshName() const;

	// method 1 : one step analyze
	AnalysisExport bool Analyse(OUT StdSkeletonLimb& root);

	// method 2 : step-by-step analyze
	AnalysisExport bool BeginCutDisk();
	AnalysisExport bool CutNextDisk();
	AnalysisExport void EndCutDisk();

	AnalysisExport bool BeginPickLimb();
	AnalysisExport bool PickNextLimb();
	AnalysisExport void EndPickLimb();

	AnalysisExport void ConnectLimbs();
	AnalysisExport void BuildStdSkeletonLimb(OUT StdSkeletonLimb& root);
	AnalysisExport bool SaveStdSkeletonLimb(const TCHAR* fileName);

	inline const TriMesh& GetTriMesh() const;
	inline const CD3DMeshData& GetD3DMeshData() const;

	AnalysisExport void Render(const RenderSystemPtr& pRenderSystem);
	AnalysisExport void ViewNextCutPlane();
	AnalysisExport void ViewPrevCutPlane();
	AnalysisExport void ViewBestCutPlane();
	AnalysisExport const ConcavePolygon2* GetCurrentConcavePolygon() const;

private:
	AnalysisExport bool CutLimbDisk(
		LimbDisk& disk, 
		const Vector3& vPoint, 
		size_t nTriangleIndex);
	AnalysisExport void RenderDebugDisks();
	AnalysisExport size_t GetBestEdgeCutPlane() const;
	AnalysisExport size_t GetEdgeCutPlaneCount() const;
	AnalysisExport void RenderEdgeCutPlane(const RenderSystemPtr& pRenderSystem, size_t i);
	AnalysisExport size_t GetBestTryCutPlane() const;
	AnalysisExport size_t GetTryCutPlaneCount() const;
	AnalysisExport void RenderTryCutPlane(const RenderSystemPtr& pRenderSystem, size_t i);
	AnalysisExport bool IsEdgeCutPlaneBest() const;
	AnalysisExport void RenderCurrentCutFace(const RenderSystemPtr& pRenderSystem);

private:
	AnalysisExport void CleanMembers();

private:
	size_t m_bestCutPlane;
	size_t m_currentFace;
	size_t m_currentPhase;
	bool m_bCutSucceeded;
	vector<UserPrimitiveVertex> m_cutTriangle;

private:
	tstring m_rawMeshName;
	AxisAlignBox m_bbox;
	// for analyzing
	TriMesh m_triMesh;
	// for rendering
	CD3DMeshData m_d3dMesh;
	CMeshGroup m_meshGroup;
	CDiskCutter m_diskCutter;
	CDiskContainer m_diskContainer;
	CLimbPicker m_limbPicker;
	CLimbConnector m_limbConnector;
};

inline const TriMesh& CTreeSkeletonAnalyser::GetTriMesh() const
{
	return m_triMesh;
}

inline const CD3DMeshData& CTreeSkeletonAnalyser::GetD3DMeshData() const
{
	return m_d3dMesh;
}

WING_END

#endif // #ifndef CTREESKELETONANALYSER_144212102007_H
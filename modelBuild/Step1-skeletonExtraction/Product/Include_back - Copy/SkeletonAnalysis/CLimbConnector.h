// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/12/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CLIMBCONNECTOR_194912122007_H
#define CLIMBCONNECTOR_194912122007_H

#include "CLimbPicker.h"
#include "TreeLimb.h"

WING_BEGIN

class CLimbConnector
{
public:
	AnalysisExport CLimbConnector();
	AnalysisExport virtual ~CLimbConnector();

	AnalysisExport void Destroy();
	AnalysisExport void ConnectLimbs(
		const CDiskContainer& diskContainer, 
		const CLimbPicker& picker);

	AnalysisExport void BuildStdSkeletonLimb(OUT StdSkeletonLimb& limb);
	AnalysisExport bool SaveStdSkeletonLimb(const TCHAR* fileName);

	AnalysisExport void Render(const RenderSystemPtr& pRenderSystem);

private:
	AnalysisExport void CleanMembers();
	AnalysisExport void BuildConnectLimbs();
	AnalysisExport void FindBestRoot();
	AnalysisExport void InsertNecessaryDisks();

private:
	// configurations
	real m_connect_negative_alpha_threshold;
	real m_connect_negative_tangent_alpha_threshold;
	real m_connect_bigger_limb_to_smaller_limb_threshold;

private:
	const CDiskContainer* m_pDiskContainer;
	const CLimbPicker* m_pDiskPicker;

private:
	TDynArray<TreeLimb> m_limbs;
	TreeLimb* m_pBestLimbRoot;
};

WING_END

#endif // #ifndef CLIMBCONNECTOR_194912122007_H
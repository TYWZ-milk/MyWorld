// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/17/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CLIMBAXIS_95512172007_H
#define CLIMBAXIS_95512172007_H

#include "Mesh/CVectorRenderer.h"
#include "StatisticsBase.h"

WING_BEGIN

class CLimbAxis
{
public:
	TreeStatExport CLimbAxis();
	TreeStatExport virtual ~CLimbAxis();

	TreeStatExport void Destroy();
	TreeStatExport void Create(const StdSkeletonLimb& limb);

	TreeStatExport void Render(const RenderSystemPtr& pRenderSystem);

private:
	TreeStatExport void CleanMembers();

private:
	struct CoodinateRenderer
	{
		CVectorRenderer x;
		CVectorRenderer y;
		CVectorRenderer z;
	};

	vector<CoodinateRenderer> m_nodeCoodinates;
};

WING_END

#endif // #ifndef CLIMBAXIS_95512172007_H
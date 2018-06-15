// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/16/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CTERMINALVANGLEVARIATION_133312162007_H
#define CTERMINALVANGLEVARIATION_133312162007_H

#include "StatisticsBase.h"
#include "CSampleCurve1D.h"

WING_BEGIN

class CTerminalVAngleVariation
{
public:
	TreeStatExport CTerminalVAngleVariation();
	TreeStatExport virtual ~CTerminalVAngleVariation();

	TreeStatExport void Destroy();
	TreeStatExport void InputTree(StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

	TreeStatExport size_t GetDataCount() const;
	TreeStatExport size_t GetBranchOrder(size_t dataIndex) const;
	TreeStatExport real GetVerticalAngle(size_t dataIndex) const;
    TreeStatExport const CSampleCurve1D& GetSampleCurve() const;

public:
	TreeStatExport real Sample(size_t branchOrder);

private:
	TreeStatExport void CleanMembers();

private:
	size_t m_maximalBranchOrder;
	CSampleCurve1D m_sampleCurve;
	// terminal的枝条都需要branch order来表明它是第几个孩子，因为terminal是围圈长的。
	vector<size_t> m_branchOrders;
	vector<real> m_verticalAngles;
};

WING_END

#endif // #ifndef CTERMINALVANGLEVARIATION_133312162007_H
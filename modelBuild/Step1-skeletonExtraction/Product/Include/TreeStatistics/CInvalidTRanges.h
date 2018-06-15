// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/14/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CINVALIDTRANGES_174812142007_H
#define CINVALIDTRANGES_174812142007_H

#include "StatisticsBase.h"
#include "CDistribution1D.h"

WING_BEGIN

// 记录每根枝条顶端有多长一段没有侧枝
class CInvalidTRanges
{
public:
	TreeStatExport CInvalidTRanges();
	TreeStatExport virtual ~CInvalidTRanges();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(const StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

	TreeStatExport size_t GetDataCount() const;
	TreeStatExport real GetData(size_t dataIndex) const;

public:
	TreeStatExport real Sample();

private:
	TreeStatExport void CleanMembers();

private:
	CDistribution1D m_distribution;
	vector<real> m_invalidTRangeDatas;
};

WING_END

#endif // #ifndef CINVALIDTRANGES_174812142007_H
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

#ifndef CINTERNODELENGTHS_181112142007_H
#define CINTERNODELENGTHS_181112142007_H

#include "StatisticsBase.h"
#include "CSampleCurve1D.h"

WING_BEGIN

// 记录侧枝分叉间隔的长度
class CInternodeLengths
{
public:
	TreeStatExport CInternodeLengths();
	TreeStatExport virtual ~CInternodeLengths();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(const StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;
	TreeStatExport const CSampleCurve1D& GetSampleCurve() const;

	TreeStatExport real GetMaximalLimbLength() const;
	TreeStatExport size_t GetDataCount() const;
	TreeStatExport real GetDistanceToApex(size_t dataIndex) const;
	TreeStatExport real GetInternodeLength(size_t dataIndex) const;

public:
	TreeStatExport real Sample(real distanceToApex);
	TreeStatExport bool Sample(real distanceToApex, real tau, real minimalInverval, real tolerant, OUT vector<real>& lengthArray );

private:
	TreeStatExport void CleanMembers();

private:
	CSampleCurve1D m_sampleCurve;
	real m_maximalLimbLength;
	vector<real> m_distanceToApex;
	vector<real> m_nodeLengths;
};

WING_END

#endif // #ifndef CINTERNODELENGTHS_181112142007_H
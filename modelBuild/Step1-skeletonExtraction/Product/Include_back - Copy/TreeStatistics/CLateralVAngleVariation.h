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

#ifndef CLATERALVANGLEVARIATION_191912142007_H
#define CLATERALVANGLEVARIATION_191912142007_H

#include "StatisticsBase.h"
#include "CSampleCurve1D.h"

WING_BEGIN

class CLateralVAngleVariation
{
public:
	TreeStatExport CLateralVAngleVariation();
	TreeStatExport virtual ~CLateralVAngleVariation();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

	TreeStatExport real GetMaximalLimbLength() const;
	TreeStatExport size_t GetDataCount() const;
	TreeStatExport real GetDistanceToApex(size_t dataIndex) const;
	TreeStatExport real GetVAngleDegree(size_t dataIndex) const;
    TreeStatExport const CSampleCurve1D& GetSampleCurve() const;
    TreeStatExport const real GetMaexLen() const;
    
public:
	TreeStatExport real Sample(real distanceToApex);

private:
	TreeStatExport void CleanMembers();

private:
	CSampleCurve1D m_sampleCurve;
	real m_maximalLimbLength;
	vector<real> m_distanceToApex;
	vector<real> m_vAngleDegree;
};

WING_END

#endif // #ifndef CLATERALVANGLEVARIATION_191912142007_H

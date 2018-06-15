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

#ifndef CLIMBCURVE_111812172007_H
#define CLIMBCURVE_111812172007_H

#include "StatisticsBase.h"
#include "CCurvatureFunction.h"
#include "CLimbCurveDistribution.h"

WING_BEGIN

class CLimbCurve
{
public:
	TreeStatExport CLimbCurve();
	TreeStatExport virtual ~CLimbCurve();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(StdSkeletonLimb& limb);
	TreeStatExport void BuildCurve();
	TreeStatExport bool IsCurveValid();

	TreeStatExport void BuildLimbCurve(
		StdSkeletonLimb& limb, 
		const Vector3& vInitialPosition, 
		const Coordinate3& initialCoordinate, 
		real totalLimbLength);

private:
	TreeStatExport void CleanMembers();
	TreeStatExport void GetLimbXDir(
		Vector3& limbXDir, 
		Vector3& limbHDir, 
		const Vector3& vStartDir);

private:
	vector<CurvatureFunctionPtr> m_curvatureFunction;
	CLimbCurveDistribution m_curveDistribution;
};

WING_END

#endif // #ifndef CLIMBCURVE_111812172007_H

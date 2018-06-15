// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   01/09/2008 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CLIMBCURVEDISTRIBUTION_1401192008_H
#define CLIMBCURVEDISTRIBUTION_1401192008_H

#include "CCurvatureFunction.h"
#include "CDistribution1D.h"

WING_BEGIN

class CLimbCurveDistribution
{
public:
	TreeStatExport CLimbCurveDistribution();
	TreeStatExport virtual ~CLimbCurveDistribution();

	TreeStatExport void Destroy();
	TreeStatExport void InputCurves(vector<CurvatureFunctionPtr>& curves);

	TreeStatExport LimbTrend GetTrend() const;
	TreeStatExport real GetDegreeToTrend(real initialVerticalDegree) const;
	TreeStatExport Vector3 GetTrendDirection(
		const Vector3& vLimbHDir, 
		const Vector3& currentDir) const;
	TreeStatExport real GetRandomBeforeCurveRatio() const;
	TreeStatExport real GetRandomCurvatureToTrend() const;
	TreeStatExport real GetAverageInterknotLength() const;

	TreeStatExport real GetRandomHAngleLength() const;
	TreeStatExport real GetRandomVAngleLength() const;
	TreeStatExport real GetRandomHAngle() const;
	TreeStatExport real GetRandomVAngle() const;

private:
	TreeStatExport void CleanMembers();

private:
	LimbTrend m_trend;
	CDistribution1D m_beforeCurveRatio;
	CDistribution1D m_curvatureToTrend;
	real m_averageInterknotLength;

private:
	// noise waves
	CDistribution1D m_PossibleHAngles;
	CDistribution1D m_PossibleVAngles;
	CDistribution1D m_PossibleHAngleLength;
	CDistribution1D m_PossibleVAngleLength;
};

WING_END

#endif // #ifndef CLIMBCURVEDISTRIBUTION_1401192008_H

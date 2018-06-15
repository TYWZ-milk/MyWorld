// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   01/04/2008 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CANGLEWAVE_1835142008_H
#define CANGLEWAVE_1835142008_H

#include "StatisticsBase.h"

WING_BEGIN

class CAngleWave
{
public:
	TreeStatExport CAngleWave();
	TreeStatExport virtual ~CAngleWave();

	TreeStatExport void Destroy();
	TreeStatExport void Create(
		real minimalWaveLength, 
		real maximalWaveVariance);
	TreeStatExport bool OnInput(
		real length, 
		real rotateDegree);

	TreeStatExport size_t GetCurvatureCount() const;
	TreeStatExport real GetAverageCurvature() const;

	TreeStatExport bool IsValidWave() const;
	TreeStatExport void MergeTo(CAngleWave& outputWave) const;

	TreeStatExport size_t GetInputCount() const;
	TreeStatExport real GetInputAngle(size_t i) const;
	TreeStatExport real GetInputLength(size_t i) const;

private:
	TreeStatExport void CleanMembers();
	TreeStatExport real CalculateVarianceSum(real meanValue);

private:
	real m_minimalWaveLength;
	real m_maximalWaveVariance;
	real m_totalLength;
	real m_totalAngle;
	vector<real> m_angles;
	vector<real> m_lengths;
};

WING_END

#endif // #ifndef CANGLEWAVE_1835142008_H
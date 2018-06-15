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

#ifndef CDISTRIBUTION1D_161912162007_H
#define CDISTRIBUTION1D_161912162007_H

#include "StatisticsBase.h"

WING_BEGIN

class CDistribution1D
{
public:
	TreeStatExport CDistribution1D();
	TreeStatExport virtual ~CDistribution1D();

	TreeStatExport void Destroy();

	TreeStatExport void BeginInputSample(real range0, real range1);
	TreeStatExport void InputSample(real value);
	TreeStatExport bool EndInputSample();

	TreeStatExport bool IsValid() const;

	TreeStatExport real RandomSample() const;

	TreeStatExport real GetMinimalSample() const;
	TreeStatExport real GetMaximalSample() const;

private:
	TreeStatExport void CleanMembers();

private:
	bool m_bValid;
	real m_range0;
	real m_range1;
	real m_minimalSample;
	real m_maximalSample;
	vector<real> m_samples;
	vector<real> m_cdfSamples;
	GSLMathUtilPtr m_gslMath;
};

WING_END

#endif // #ifndef CDISTRIBUTION1D_161912162007_H
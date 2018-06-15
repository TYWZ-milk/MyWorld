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

#ifndef CTERMINALCHILDLENGTHS_211212142007_H
#define CTERMINALCHILDLENGTHS_211212142007_H

#include "StatisticsBase.h"
#include "CSampleCurve1D.h"

WING_BEGIN

class CTerminalChildLengths
{
public:
	TreeStatExport CTerminalChildLengths();
	TreeStatExport virtual ~CTerminalChildLengths();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(const StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

	TreeStatExport real GetMaximalLimbLength() const;
	TreeStatExport size_t GetDataCount() const;
	TreeStatExport real GetParentLimbRadius(size_t dataIndex) const;
	TreeStatExport real GetParentLimbLength(size_t dataIndex) const;
	TreeStatExport real GetTerminalChildLength(size_t dataIndex) const;
    TreeStatExport const CSampleCurve1D& GetSampleCurve() const;
    
public:
	TreeStatExport real Sample(real parentLimbLength);
	TreeStatExport bool Sample(const real* parentLimbLength, size_t n, real tolerant, OUT real* y);

private:
	TreeStatExport void CleanMembers();

private:
	CSampleCurve1D m_sampleCurve;
	real m_maximalLimbLength;
	vector<real> m_parentLimbRadius;
	vector<real> m_parentLimbLength;
	vector<real> m_terminalChildLength;
};

WING_END

#endif // #ifndef CTERMINALCHILDLENGTHS_211212142007_H
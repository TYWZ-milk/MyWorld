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

#ifndef CLIMBREBUILDDATA_151312162007_H
#define CLIMBREBUILDDATA_151312162007_H

#include "StatisticsBase.h"

WING_BEGIN

/*
struct LimbRebuildInput
{
	Vector3 origin;
	Vector3 direction;
	real length;
};
*/

struct LimbRebuildData
{
	vector<real> m_radius;
	vector<real> m_internodeLengths;
	vector<vector<real> > m_lateralChildHAngles;
	vector<vector<real> > m_lateralChildVAngles;
	vector<vector<real> > m_lateralChildLengths;
	vector<real> m_terminalChildHAngles;
	vector<real> m_terminalChildLengths;
};

WING_END

#endif // #ifndef CLIMBREBUILDDATA_151312162007_H
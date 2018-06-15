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

#ifndef CLIMBGROUPDATA_150712162007_H
#define CLIMBGROUPDATA_150712162007_H

#include "CFirstRamificationLength.h"
#include "CInternodeLengths.h"
#include "CInvalidTRanges.h"
#include "CLateralChildLengths.h"
#include "CLateralHAngleRotation.h"
#include "CLateralVAngleVariation.h"
#include "CProductionTypes.h"
#include "CRadiusSample.h"
#include "CTerminalChildLengths.h"
#include "CLimbRebuildData.h"
#include "CLimbCurve.h"

#include "CAverageHAngleRotation.h"

WING_BEGIN

struct lineCoeff
{
    real a;
    real b;
};

struct GroupSamplePoly
{
    CPolynomial terminalVAngleP;
    CPolynomial lateralVAngleP;
    CPolynomial terminalLengthP;
    CPolynomial lateralLengthP;
    CPolynomial radiusP;

	lineCoeff  terminalVAngleCoeff;
    lineCoeff  lateralVAngleCoeff;
	lineCoeff  terminalLengthCoeff;
	lineCoeff  lateralLengthCoeff;
	lineCoeff  radiusCoeff;

    real maxLimbLen;
};

struct SampleCurveInfo
{
	uint32 groupId;
	TCHAR* sampleName;
	const CSampleCurve1D* sampleCurve;
};

struct HorizontalAngleUpdateInfo
{
	real internode_length;
	vector<bool> is_constraints;
	vector<real> horizontal_angles;
};

class CLimbGroupData
{
public:
	TreeStatExport CLimbGroupData();
	TreeStatExport virtual ~CLimbGroupData();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(StdSkeletonLimb& limb);
	TreeStatExport void BuildCurves();
    TreeStatExport bool GetCurvesInfo(GroupSamplePoly& groupSamplePoly);

	// new function to get a group's samples' curves,
	// like firstRamificationLength, internodeLengths, invalidTRanges, lateralChildLengths, lateralHAngleRotation, lateralVAngleVariation,
	// productionTypes, radiusSample, terminalChildLengths, ...
	TreeStatExport bool GetAllSampleCurve( uint32 groupId, vector<SampleCurveInfo>& vSampleCurveInfo );

	TreeStatExport void RandomSampleLimb(OUT LimbRebuildData& data, IN real limbLength);

	TreeStatExport CLimbCurve& GetLimbCurve();

private:
	TreeStatExport void CleanMembers();
	TreeStatExport void BuildRadiusArray(
		OUT vector<real>& radiusArray, IN real limbLength);
	TreeStatExport void BuildInternodeLength(
		OUT vector<real>& internodeLengthArray, 
		IN real limbLength, 
		IN real minimalInternodeLength);
	TreeStatExport void BuildLateralChildHAngles(
		OUT vector<vector<real> >& lateralHAngles, 
		IN const vector<real>& internodeLengthArray);
	TreeStatExport void BuildLateralChildVAngles(
		OUT vector<vector<real> >& lateralVAngles, 
		IN const vector<vector<real> >& lateralHAngles, 
		IN const vector<real>& internodeLengthArray, 
		IN real limbLength);
	TreeStatExport void BuildLateralChildLengths(
		OUT vector<vector<real> >& lateralLengths, 
		IN const vector<vector<real> >& lateralHAngles, 
		IN const vector<real>& internodeLengthArray, 
		IN real limbLength);
	TreeStatExport void BuildTerminalChildAngles(
		OUT vector<real>& terminalHAngles);
	TreeStatExport void BuildTerminalChildLengths(
		OUT vector<real>& terminalLengths, 
		IN const vector<real>& terminalHAngles, 
		IN real limbLength);
	TreeStatExport void BuildChildHAngles(
		OUT vector<vector<real>>& lateralHAngles,
		OUT vector<real>& terminalHAngles,
		IN const vector<real>& internodeLengthArray);
	TreeStatExport void AdjustChildHAngles( vector<HorizontalAngleUpdateInfo>& hAngleInfo );

private:
	CFirstRamificationLength m_firstRamificationLength;
	CInternodeLengths m_internodeLengths;
	CInvalidTRanges m_invalidTRanges;
	CLateralChildLengths m_lateralChildLengths;
	CLateralHAngleRotation m_lateralHAngleRotation;
	CLateralVAngleVariation m_lateralVAngleVariation;
	CProductionTypes m_productionTypes;
	CRadiusSample m_radiusSample;
	CTerminalChildLengths m_terminalChildLengths;

	CAverageHAngleRotation m_averageHAngleRotation;
	
	CLimbCurve m_limbCurve;

	//vector<real> internode;
	//vector<vector<real>> lateral;
	//vector<real> terminal;
	//vector<vector<real>> vangles;
};

WING_END

#endif // #ifndef CLIMBGROUPDATA_150712162007_H
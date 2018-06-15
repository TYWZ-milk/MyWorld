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

#ifndef CPRODUCTIONTYPES_205312142007_H
#define CPRODUCTIONTYPES_205312142007_H

#include "StatisticsBase.h"
#include "CDistribution1D.h"

WING_BEGIN

struct ProductionType
{
	TreeStatExport ProductionType();

	TreeStatExport void InputHorizontalAngles(vector<real>& hAngles);

	TreeStatExport bool BuildCurve();

	TreeStatExport bool IsCurveValid() const;

	TreeStatExport void SampleHAngleDistances(OUT vector<real>& hAngleAngles) const;

	real probability;
	size_t sampleCount;
	size_t childCount;
	vector<real> hAngleDistances;
	CDistribution1D distribution;
};

class CProductionTypes
{
public:
	TreeStatExport CProductionTypes();
	TreeStatExport virtual ~CProductionTypes();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(const StdSkeletonLimb& limb);

	TreeStatExport size_t GetLateralProductionTypeCount() const;
	TreeStatExport const ProductionType& GetLateralProductionType(size_t dataIndex) const;

	TreeStatExport size_t GetTerminalProductionTypeCount() const;
	TreeStatExport const ProductionType& GetTerminalProductionType(size_t dataIndex) const;

	TreeStatExport bool BuildCurve();

	TreeStatExport const ProductionType* SampleLateralProduction();

	TreeStatExport const ProductionType* SampleTerminalProduction();

private:
	TreeStatExport void CleanMembers();

private:
	TreeStatExport void BuildProbability();

	TreeStatExport ProductionType& AddLimbData(
		OUT vector<ProductionType>& productionArray, 
		IN size_t childCount);

	TreeStatExport void BuildProbability(OUT vector<ProductionType>& productionArray);

	TreeStatExport const ProductionType* FindRandomProduction(
		IN const vector<ProductionType>& productionArray) const;

	TreeStatExport real GetDegreeDistance(real degree1, real degree2) const;

private:
	vector<ProductionType> m_lateralProductions;
	vector<ProductionType> m_terminalProductions;
};

WING_END

#endif // #ifndef CPRODUCTIONTYPES_205312142007_H
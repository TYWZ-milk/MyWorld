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

#ifndef CLATERALHANGLEROTATION_185812142007_H
#define CLATERALHANGLEROTATION_185812142007_H

#include "StatisticsBase.h"
#include "CDistribution1D.h"

WING_BEGIN

class CLateralHAngleRotation
{
public:
	TreeStatExport CLateralHAngleRotation();
	TreeStatExport virtual ~CLateralHAngleRotation();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData(StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

	TreeStatExport size_t GetDataCount() const;
	TreeStatExport size_t GetNodeCountToApex(size_t dataIndex) const;
	TreeStatExport real GetRelativeRotationDegree(size_t dataIndex) const;
    TreeStatExport const CDistribution1D& GetDistribution() const;

public:
	TreeStatExport real Sample(size_t n);

private:
	TreeStatExport void CleanMembers();

private:
	TreeStatExport real GetClusterRotationAngle(
		const StdSkeletonLimb& limb, 
		size_t cluster0, 
		size_t cluster1) const;

	TreeStatExport real GetMinimalRotationAngle(
		const StdSkeletonLimb& limb, 
		size_t cluster, 
		real horizontalAngle) const;

	TreeStatExport real GetDegreeDistance(
		real angleDegree1, 
		real angleDegree2) const;

private:
	vector<real> m_hAngles;
	CDistribution1D m_distribution;
	vector<size_t> m_nodeCountToApex;
	vector<real> m_relativeRotationDegrees;
};

WING_END

#endif // #ifndef CLATERALHANGLEROTATION_185812142007_H

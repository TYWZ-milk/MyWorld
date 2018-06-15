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

#ifndef CTERMINALHANGLEROTATION_131612162007_H
#define CTERMINALHANGLEROTATION_131612162007_H

#include "StatisticsBase.h"
#include "CDistribution1D.h"

WING_BEGIN

class CTerminalHAngleRotation
{
public:
	TreeStatExport CTerminalHAngleRotation();
	TreeStatExport virtual ~CTerminalHAngleRotation();

	TreeStatExport void Destroy();
	TreeStatExport void InputTree(StdSkeletonLimb& limb);
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

	TreeStatExport size_t GetDataCount() const;
	TreeStatExport size_t GetBranchOrder(size_t dataIndex) const;
	TreeStatExport real GetRotationAngle(size_t dataIndex) const;
    TreeStatExport const CDistribution1D& GetDistribution() const;
    
public:
	TreeStatExport real Sample();

private:
	TreeStatExport void CleanMembers();

private:
	TreeStatExport bool GetTerminalRoationHAngle(
		real& rotationAngle, 
		const StdSkeletonLimb& limb0, 
		const StdSkeletonLimb& limb1) const;

	TreeStatExport real GetMinimalRotationHAngle(
		const StdSkeletonLimb& limb0, 
		real horizontalAngle) const;

	TreeStatExport real GetDegreeDistance(
		real angleDegree1, 
		real angleDegree2) const;

private:
	CDistribution1D m_distribution;
	vector<size_t> m_branchOrders;
	vector<real> m_rotationAngles;
};

WING_END

#endif // #ifndef CTERMINALHANGLEROTATION_131612162007_H
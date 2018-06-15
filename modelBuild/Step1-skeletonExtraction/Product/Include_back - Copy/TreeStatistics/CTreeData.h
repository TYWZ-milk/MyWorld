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

#ifndef CTREEDATA_154412162007_H
#define CTREEDATA_154412162007_H

#include "CTerminalHAngleRotation.h"
#include "CTerminalVAngleVariation.h"
#include "CLimbGroupData.h"
#include "Utility/StlMap.h"
#include "Utility/IDAllocator.h"

WING_BEGIN

struct GroupInfo
{
	uint32 groupId;
	uint32 lateralGroupId;
	uint32 terminalGroupId;
};

struct GroupSamplePoly;
struct SampleCurveInfo;

class CTreeData
{
public:
	TreeStatExport CTreeData();
	TreeStatExport virtual ~CTreeData();

	TreeStatExport void Destroy();
	TreeStatExport void BeginInput();
	TreeStatExport void InputTree(StdSkeletonLimb& limb);
	TreeStatExport void EndInput();

	TreeStatExport void OutputTree(
		OUT StdSkeletonLimb& root, 
		IN const Vector3& vOrigin);

	TreeStatExport void OutputTree(
		OUT StdSkeletonLimb& root, 
		IN const Vector3& vOrigin, 
		IN const Coordinate3& coordinate);
    
    TreeStatExport map<uint32, GroupSamplePoly>* GetGroupSamplePoly();

	// new function to get all the sample curves
	// including a terminalHAngleRotation, a terminalVAngleVariation and serveral groups' sample curves
	TreeStatExport bool GetAllSampleCurve( vector<SampleCurveInfo>& vSampleCurveInfo );
	TreeStatExport void SetLegthRatio(real lengthRatio);

private:
	// 把枝干加入到指定的group，并且它会递归地将其子枝干加入到适当的group。
	// 每个group它对应一个GroupInfo, 其中记录了它的lateral child应该属于哪个group，它的terminal child应该属于哪个group， 它们groupid都是由IDAllocator分配的。
	TreeStatExport void InputSubTree(uint32 groupId, StdSkeletonLimb& limb);
	TreeStatExport CLimbGroupData& NewGroupData(uint32 groupId);
	TreeStatExport CLimbGroupData* FindGroupData(uint32 groupId);

	TreeStatExport void OutputLimb(
		StdSkeletonLimb& limb, 
		uint32 branchOrder, 
		uint32 groupId, 
		real totalLimbLength, 
		real terminalRotation, 
		const Vector3& vOrigin, 
        const real parentKnotRadius,
		const Coordinate3& coordinate3);
	
private:
	TreeStatExport void CleanMembers();
	TreeStatExport GroupInfo GetGroupInfo(uint32 groupId);

private:
	IDAllocator m_groupIdAlloc;
	uint32 m_rootGroup;
	real m_minimalRootLength;
	real m_maximalRootLength;
	CTerminalHAngleRotation m_terminalHAngleRotation;
	CTerminalVAngleVariation m_terminalVAngleVariation;
	map<uint32, CLimbGroupData*> m_groups;
	map<uint32, GroupInfo> m_groupInfo;
    
    // to store sample trend polynomial
    map<uint32, GroupSamplePoly> m_groupSamplePoly;
    CStdSkeletonLimbHelper  limbHelper;
	real m_lengthRatio;
};

WING_END

#endif // #ifndef CTREEDATA_154412162007_H
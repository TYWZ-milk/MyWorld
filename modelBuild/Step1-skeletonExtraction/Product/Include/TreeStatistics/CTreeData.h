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
	// 注意terminal的转角和偏角是对整棵树而言的，并不分group，也就是说每一层都遵循这个自相似的规则。
	// 但是lateral的转角和偏角是分group来统计的。 因此不在该CTreeData里存储而是在CLimbGroupData存储。
	CTerminalHAngleRotation m_terminalHAngleRotation;
	CTerminalVAngleVariation m_terminalVAngleVariation;
	// 记录单个group内的枝干特征
	map<uint32, CLimbGroupData*> m_groups;
	// 记录group之间的逻辑关系，主要分为lateral和terminal关系
	map<uint32, GroupInfo> m_groupInfo;
    
    // to store sample trend polynomial
    map<uint32, GroupSamplePoly> m_groupSamplePoly;
    CStdSkeletonLimbHelper  limbHelper;
	real m_lengthRatio;
};

WING_END

#endif // #ifndef CTREEDATA_154412162007_H
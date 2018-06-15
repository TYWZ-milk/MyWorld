// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   11/18/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef TREELIMB_122411182007_H
#define TREELIMB_122411182007_H

#include "TreeLimbDisk.h"
#include "StdSkeletonLimb.h"
#include "Utility/StlDeque.h"
#include "RenderSystem/IRenderDevice.h"

WING_BEGIN

const Color4 DEFAULT_LIMB_START_COLOR = Color4(0xff000000);
const Color4 DEFAULT_LIMB_END_COLOR = Color4(0xff000000);
const Color4 DEFAULT_SELECTED_LIMB_START_COLOR = Color4(0xffff0000);
const Color4 DEFAULT_SELECTED_LIMB_END_COLOR = Color4(0xffff0000);

class TreeLimbImpl;

class TreeLimb
{
public:
	AnalysisExport TreeLimb();
	AnalysisExport virtual ~TreeLimb();

	AnalysisExport void Clear();

public:
	// create functions
	AnalysisExport void PushBack(const TreeLimb& limb);
	AnalysisExport void PushFront(const TreeLimb& limb);

	AnalysisExport void PushBack(const LimbDisk& disk);
	AnalysisExport void PushFront(const LimbDisk& disk);
	AnalysisExport void PopBack();
	AnalysisExport void PopFront();

public:
	AnalysisExport void AddChild(TreeLimb* pChild);
	AnalysisExport void SetChild(size_t index, TreeLimb* pChild);
	AnalysisExport void DelChild(size_t index);
	AnalysisExport size_t GetChildCount() const;
	AnalysisExport TreeLimb* GetChild(size_t index);

	AnalysisExport void SetParent(TreeLimb* pParent);
	AnalysisExport void SetParentStartDiskIndex(size_t startDiskIndex);
	AnalysisExport void SetConnectParentDisk(const LimbDisk& disk);
	AnalysisExport TreeLimb* GetParent() const;
	AnalysisExport size_t GetParentStartDiskIndex() const;
	AnalysisExport const LimbDisk& GetConnectParentDisk() const;

	AnalysisExport size_t GetDiskCount() const;
	AnalysisExport const LimbDisk& GetDisk(size_t i) const;

public:
	// member data get functions
	AnalysisExport real GetMaximalDiskDistance() const;
	AnalysisExport real GetTangentAlpha() const;
	AnalysisExport real GetLimbLength() const;
	AnalysisExport real GetMaximalRadius() const;
	AnalysisExport real GetMinimalRadius() const;
	AnalysisExport real GetAverageRadius() const;
	AnalysisExport real GetSmoothStartDiskRadius() const;
	AnalysisExport real GetSmoothEndDiskRadius() const;

private:
	AnalysisExport void BuildTopoData();

public:
	// algorithms
	AnalysisExport bool IsOverlapped(const TreeLimb& limb) const;
	AnalysisExport bool IsAncestor(const TreeLimb* pAncestor) const;
	AnalysisExport void InvertDirection();
	AnalysisExport bool TryConnect(
		// 探测出的disk
		OUT LimbDisk& connect_disk, 
		// 探测出的交点在父亲枝条上的哪个disk？
		OUT size_t& parentStartDiskIndex, 
		// 可能的父亲枝条
		IN const TreeLimb& possible_parent, 
		// 从端点开始探测多少距离？
		IN real detectDistance, 
		// 尝试起点去探测还是终点去探测？
		IN bool start_disk);
	AnalysisExport size_t CalculateAllChildrenCount() const;
	AnalysisExport void InsertNecessaryDisks();
	AnalysisExport bool RayTrace(
		OUT real& scale, 
		IN const Vector3& vStart, 
		IN const Vector3& vDir);
	AnalysisExport TreeLimb* RayTraceLimbTree(
		OUT real& scale, 
		IN const Vector3& vStart, 
		IN const Vector3& vDir);

public:
	// conversion functions
	AnalysisExport void BuildStdSkeletonLimb(OUT StdSkeletonLimb& limb);
	AnalysisExport bool SaveStdSkeletonLimb(const TCHAR* fileName);

public:
	AnalysisExport const AxisAlignBox& GetBoundingBox() const;
	AnalysisExport const AxisAlignBox& GetTreeBoundingBox() const;

private:
	// bounding box functions
	AnalysisExport void DirtyBoundingBox();
	AnalysisExport void DirtyTreeBoundingBox();
	AnalysisExport void BuildBoundingBox() const;
	AnalysisExport void BuildTreeBoundingBox() const;
	AnalysisExport void BuildBoundingBox_S(AxisAlignBox& bbox) const;
	AnalysisExport void BuildBoundingBox_R(AxisAlignBox& bbox) const;

public:
	// debug functions
	AnalysisExport void BuildDebugVertices(
		const Color4 color1 = DEFAULT_LIMB_START_COLOR, 
		const Color4 color2 = DEFAULT_LIMB_END_COLOR);
	AnalysisExport void BuildTreeDebugVertices(
		const Color4 color1 = DEFAULT_LIMB_START_COLOR, 
		const Color4 color2 = DEFAULT_LIMB_END_COLOR);
	AnalysisExport Color4 GetDebugStartColor() const;
	AnalysisExport Color4 GetDebugEndColor() const;
	AnalysisExport void RenderDebugVertices(const RenderSystemPtr& pRenderSystem);

private:
	AnalysisExport void CleanMembers();

private:
	TreeLimb(const TreeLimb& from);
	TreeLimb& operator = (const TreeLimb& from);

private:
	TreeLimbImpl* mpImpl;
	TDynArray<TreeLimb*> m_children;
	TreeLimb* m_pParent;
	size_t m_parentStartDiskIndex;
	LimbDisk m_connectParentDisk;
	// ---------------------------------
	// Tangent alpha
	// ---------------------------------
	//   last disk
	//       __
	//      /  \   |
	//     /    \  |
	//    /      \A|
	//   /        \|
	//  ------------
	//   first disk
	real m_tangentAlpha;
	// 最大的两个disk之间的距离
	real m_maximalDistance;
	// 粗略估计的limb长度
	real m_limbLength;
	// 所有disk中最大的半径
	real m_maximalRadius;
	// 所有disk中最小的半径
	real m_minimalRadius;
	// 所有disk的平均半径
	real m_averageRadius;
	// 起始点的半径
	real m_smoothStartRadius;
	// 结束点的半径
	real m_smoothEndRadius;
	bool m_topoDirty;

	mutable AxisAlignBox m_boundingBox;
	mutable AxisAlignBox m_treeBoundingBox;
	mutable bool m_bBoundingBoxDirty;
	mutable bool m_bTreeBoundingBoxDirty;

	// for debug
	TDynArray<UserPrimitiveVertex> m_debugVertices;
};

WING_END

#endif // #ifndef TREELIMB_122411182007_H
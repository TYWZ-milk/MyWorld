// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   11/21/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef STDSKELETONLIMB_102111212007_H
#define STDSKELETONLIMB_102111212007_H

#include "AnalysisBase.h"
#include "TreeLimbDisk.h"
#include "Utility/StlDeque.h"
#include "RenderSystem/IRenderDevice.h"
#include "Geometry/Coordinate3.h"
#include "StdSkeletonLimbHelper.h"

WING_BEGIN

// 圆盘结构，包含中心坐标和半径，圆盘的朝向根据前后两个中心点的连线决定
struct LimbKnotPoint
{
	Vector3 knot;
	real radius;
};

// record one ramification event
struct RamificationEvent
{
	size_t parentNodeIndex;	  // 指的是父亲枝干的节点index，这个跟下面的childIndex所指的不太一样
	size_t childIndex;		// 指的是在孩子枝干数组m_children中的index，也就是枝干的index
	real ramificationTime;
	// the following angle are in degrees
	real horizontalAngle;
	real verticalAngle;
};

// 用于表示internode的两端圆盘间的圆盘数据
struct KnotData
{
	// internode之间的所有圆盘的中心坐标都存在coordinateArr中
    TDynArray<Coordinate3> coordinateArr;
	// 每两个相邻圆盘间距离与总距离的比例数组
    TDynArray<real>        lenPercentArr;
};

// 两个圆盘间连线结构，具体怎么赋值的可以参见RebuildNode函数
struct InterNodeSampleData
{
	// 开始knot在StdSkeletonLimb::m_knots中的索引
	size_t firstKnotIndex;
	// 结束knot在StdSkeletonLimb::m_knots中的索引，如果开始为0，结束为size-1，表示是整个枝条
	size_t lastKnotIndex;
	// internode的长度，根据其间圆盘距离的累积来算出
	real length;
	real firstRadius;
	real lastRadius;

	// 起始点的坐标
	Coordinate3 coordinate;
	real startTime;
	real growthTime;
	real age;
	//LimbCurvePtr radiusCurve;
	//LimbCurvePtr lengthCurve;

    KnotData knotData;
};

struct SimilarityData 
{   
    size_t groupID;
    
    real   verticalAngle;
    real   horizontalAngle;
    real   distToParentApex;
    
    real   biasVAngle;
    real   biasHAngle;
    real   biasdist;

    bool   bExistFlag;
};

typedef TDynArray<RamificationEvent> RamificationEvents;

// lateral分支的聚类，对于相邻的lateral圆盘，把它们聚为一类
struct LateralRamificationCluster
{
	RamificationEvents events;
	size_t nodeIndex;
};

// 一个枝条有多个lateral圆盘的聚类，用这个数组存储
typedef TDynArray<LateralRamificationCluster> LateralRamificationClusters;

class StdSkeletonLimb;
class CStdSkeletonLimbHelper;

typedef SharedPtr<StdSkeletonLimb> StdSkeletonLimbPtr;

class StdSkeletonLimb
{
public:
	AnalysisExport StdSkeletonLimb();
	AnalysisExport virtual ~StdSkeletonLimb();

	AnalysisExport void Destroy();

public:
	// -------------------------------------------------------------------------
	// Limb IO functions
	// -------------------------------------------------------------------------
	AnalysisExport bool Load(const TCHAR* fileName);
	AnalysisExport bool Save(const TCHAR* fileName) const;
	AnalysisExport bool Load(const IBufPtr& pStream);
	AnalysisExport bool Save(const OBufPtr& pStream) const;

	AnalysisExport void ValidateTree();

	AnalysisExport void TryConnectTerminalLimb(
		real degreeThreshold = 15, 
		bool recursive = true);
	AnalysisExport void CreateOriginStartRoot();
	AnalysisExport void ScaleTo(
		OUT StdSkeletonLimb& skeleton, 
		IN real scale);

private:
	AnalysisExport void TryConnectTerminalLimb_R(
		real degreeThreshold, 
		bool recursive);

public:
	// -------------------------------------------------------------------------
	// Member set/get functions
	// -------------------------------------------------------------------------
	AnalysisExport size_t GetInParentKnotIndex() const;

	AnalysisExport size_t GetKnotPointCount() const;
	AnalysisExport void SetKnotPoint(size_t i, const Vector3& pos, real radius);
	AnalysisExport void SetKnotPosition(size_t i, const Vector3& pos);
	AnalysisExport void SetKnotRadius(size_t i, real radius);
	AnalysisExport const LimbKnotPoint& GetKnotPoint(size_t i) const;

	AnalysisExport size_t GetChildCount() const;
	AnalysisExport StdSkeletonLimb& GetChild(size_t i);
	AnalysisExport const StdSkeletonLimb& GetChild(size_t i) const;
	AnalysisExport uint32 GetChildKnotIndex(size_t i) const;
	AnalysisExport StdSkeletonLimb* GetParent() const;

	AnalysisExport void EraseChild(size_t i);
	AnalysisExport StdSkeletonLimb& AddChild(size_t knotIndex);

	AnalysisExport void EraseKnotPoint(size_t i);
	AnalysisExport void EraseKnotPoint(size_t startIndex, size_t count);
	AnalysisExport void EraseAllKnotPoints();
	AnalysisExport void InsertKnotPoint(size_t i, const Vector3& position, real radius);
	AnalysisExport void InsertKnotPoint(size_t i, const LimbKnotPoint& knot);
	AnalysisExport void InsertKnotPoint(size_t i, const LimbKnotPoint* pKnots, size_t count);
	AnalysisExport void PushBackKnotPoint(const Vector3& position, real radius);
	AnalysisExport void PushBackKnotPoint(const LimbKnotPoint& knot);
	AnalysisExport void PushBackKnotPoint(const LimbKnotPoint* pKnots, size_t count);
	AnalysisExport void PushFrontKnotPoint(const Vector3& position, real radius);
	AnalysisExport void PushFrontKnotPoint(const LimbKnotPoint& knot);
	AnalysisExport void PushFrontKnotPoint(const LimbKnotPoint* pKnots, size_t count);
	AnalysisExport void InvertDirection();

	AnalysisExport size_t NewKnotPoint(real distanceFromStartPoint);

private:
	AnalysisExport void DirtyMergeKnots();
	AnalysisExport void DirtyBottomRamification();

	AnalysisExport void ValidateBottomRamification_R();
	AnalysisExport void ValidateBottomRamification();
	AnalysisExport void MergeNearbyKnots_R();
public:

	AnalysisExport void MergeNearbyKnots();
	AnalysisExport void SetParent(StdSkeletonLimb* pParent, size_t knotIndex);

public:
	// -------------------------------------------------------------------------
	// Limb statistic functions
	// -------------------------------------------------------------------------
	AnalysisExport size_t GetTerminalRamificationEventCount() const;
	AnalysisExport const RamificationEvent& GetTerminalRamificationEvent(size_t ramification) const;

	AnalysisExport size_t GetLateralClusterCount() const;
	AnalysisExport size_t GetLateralClusterRamificationCount(size_t cluster) const;
	AnalysisExport const RamificationEvent& GetLateralClusterRamificationEvent(
		size_t cluster, size_t ramification) const;

	AnalysisExport size_t GetNodeCount() const;
	AnalysisExport const InterNodeSampleData& GetNodeData(size_t nodeIndex) const;
	AnalysisExport const InterNodeSampleData& GetLimbData() const;

	AnalysisExport const Coordinate3& GetKnotCoordinate(size_t knotIndex) const;

	// 返回该limb是属于哪个group的
	AnalysisExport uint32 GetBranchOrder() const;

	AnalysisExport real GetSubTreeLength() const;
	AnalysisExport void CaculateSubTreeLength();
    AnalysisExport void SetGroupID(size_t groupID);
    AnalysisExport size_t GetGroupID();

private:
	AnalysisExport void DirtyChildrenClusters();
	AnalysisExport void RebuildChildLimbClusters() const;
	AnalysisExport void RebuildChildLimbClusters();
	AnalysisExport bool IsNearbyKnots(size_t lhsKnotIndex, size_t rhsKnotIndex) const;
	AnalysisExport real CalculateNodeLength(size_t nodeIndex) const;
	AnalysisExport real CalculateLimbLength() const;
	AnalysisExport size_t GetNodeFirstKnotIndex(size_t nodeIndex) const;
	AnalysisExport size_t GetNodeLastKnotIndex(size_t nodeIndex) const;

	AnalysisExport void DirtyNodeData();
	AnalysisExport void RebuildNodeData() const;
	AnalysisExport void RebuildNodeData();
	AnalysisExport void BuildChildRotationAngle(
		OUT ChildLimbRotation& rotation, size_t child_index);

	AnalysisExport void DirtyKnotCoordinate();
	AnalysisExport void BuildKnotCoordinate() const;
	AnalysisExport void BuildKnotCoordinate();

	AnalysisExport void DirtyBranchOrders();
	AnalysisExport void BuildBranchOrders() const;
	AnalysisExport void BuildBranchOrders();

public:
	// -------------------------------------------------------------------------
	// Time and age functions
	// -------------------------------------------------------------------------
	AnalysisExport void EstimateTimeAndAge(real growth_rate);

private:
	AnalysisExport real GetMaximalAge(const RamificationEvents& events);
	AnalysisExport void EstimateAge(real growth_rate);
	AnalysisExport void EstimateStartTime(
		real parent_startTime, 
		real parent_length, 
		real growth_rate);

public:
	// -------------------------------------------------------------------------
	// Edit functions
	// -------------------------------------------------------------------------
	AnalysisExport void SetSelect(bool select);
	AnalysisExport void SetSelectTree(bool select);
	AnalysisExport bool IsSelected() const;

	AnalysisExport void BuildBoundingBox(AxisAlignBox& bbox);
	AnalysisExport void BuildTreeBoundingBox(AxisAlignBox& bbox);

private:
	AnalysisExport void BuildBoundingBox_S(AxisAlignBox& bbox);
	AnalysisExport void BuildBoundingBox_R(AxisAlignBox& bbox);

public:
	AnalysisExport bool RayTrace(
		OUT real& scale, 
		IN const Vector3& vStart, 
		IN const Vector3& vDir);
	AnalysisExport StdSkeletonLimb* RayTraceLimbTree(
		OUT real& scale, 
		IN const Vector3& vStart, 
		IN const Vector3& vDir);

	AnalysisExport bool RayNearestPoint(
		IN const LineSegment3& rhs_line,
		OUT real& nearestDistance, 
		OUT int& indexKnot,
		OUT Vector3& vNearPoint);
	AnalysisExport bool RayTreeNearestPoint(
		IN const LineSegment3& rhs_line,
		OUT real& nearestDistance, 
		OUT StdSkeletonLimb* &pLimb,
		OUT int& indexKnot,
		OUT Vector3& vNearPoint);

	AnalysisExport void RotateLimbKnot(const Vector3& axis, const Vector3& basePoint, real angleRadian);
	AnalysisExport void SetTermMergeDirtyFlag(bool dirty);
	AnalysisExport bool GetTermMergeDirtyFlag();
    AnalysisExport bool SetTriPrismDirtyFlag(bool bDirty);
    AnalysisExport bool GetTriPrismDirtyFlag();
    AnalysisExport bool SetUseVeticalDir(Vector3 vDir);
    AnalysisExport Vector3 GetUseVeticalDir();
    AnalysisExport bool SetVerticalAngle(real verticalAngle);
    AnalysisExport real GetVerticalAngle();
    AnalysisExport bool SetHorizontalAngle(real verticalAngle);
    AnalysisExport real GetHorizontalAngle() const;
    AnalysisExport bool SetDistToParentApex(real verticalAngle);
    AnalysisExport real GetDistToParentApex();
    AnalysisExport const SimilarityData& GetSimilarityData();
    



public:
	// -------------------------------------------------------------------------
	// Rendering functions
	// -------------------------------------------------------------------------

	AnalysisExport bool IsBSplineRendering() const;
	AnalysisExport void SetBSplineRendering(bool bSpline);
	AnalysisExport void RenderTree();

private:
	AnalysisExport void Render_R(const RenderSystemPtr& pRenderSystem);
	AnalysisExport void Render_R_BSpline(const RenderSystemPtr& pRenderSystem);

	AnalysisExport void DirtyRenderVertices();
	AnalysisExport void BuildRenderVertices();
	AnalysisExport void BuildRenderVertices_BSpline();

	AnalysisExport void DirtyVertexColor();
	AnalysisExport void UpdateVertexColor();

public:
	// -------------------------------------------------------------------------
	// Expand functions
	// -------------------------------------------------------------------------
	inline const InterfacePtr<Interface>& GetUserData() const;
	inline void SetUserData(const InterfacePtr<Interface>& pUserdata);

protected:
	AnalysisExport void CleanMembers();

protected:
	friend class TreeLimb;
	InterfacePtr<Interface> m_pUserData;

protected:
	bool m_bMergKnotDirty;
	bool m_bBottomRamificationDirty;
	// 父亲枝条
	StdSkeletonLimb* m_pParent;
	// 孩子枝条数组
	TDynArray<StdSkeletonLimbPtr> m_children;
	// 本枝条所有的圆盘中心坐标和半径，每个圆盘只用记录坐标和半径即可，方向是由它和下一个圆盘的中心决定
	deque<LimbKnotPoint> m_knots;
	// 第i个孩子枝干是从哪个knot point长出来的， 这个数组记录这个。
	TDynArray<uint32> m_children_knot_indices;
	// 父亲limb是从第几个圆盘生出我的^_^
	size_t m_InParentKnotIndex;

protected:
	bool m_bBranchOrderDirty;
	uint32 m_branchOrder;

	real m_subTreeLength;

protected:
	// edit related members

	bool m_bVertexDirty;
	bool m_bColorDirty;

	// the curve of the limb
	TDynArray<UserPrimitiveVertex> m_limbCurveVertices;
	// all limb disks
	TDynArray<LimbDiskRenderer> m_limbDisks;

	// if this limb is selected
	bool m_bIsSelected;

	// If use b-spline to display
	bool m_bSpline;

protected:
	// cluster related members
	bool m_bClusterDirty;

	// terminal ramification:  terminal分支集合
	RamificationEvents m_terminal_ramification;
	// lateral ramification clusters:   lateral分支集合
	LateralRamificationClusters m_lateral_ramification_clusters;

protected:
	bool m_bNodeDataDirty;

	// 节点间连线结构数组, m_nodeDatas[0]的length代表firstRamification的长度
	TDynArray<InterNodeSampleData> m_nodeDatas;
	// 起始点和终点连线结构，代表整个枝条的数据
	InterNodeSampleData m_limbData;

protected:
	bool m_bKnotCoordinateDirty;
	// 圆盘坐标数组
	TDynArray<Coordinate3> m_knotCoordinates;

protected:
    bool m_dirtyTerminalMerge;
    bool m_dirtyTriPrism;
    
    Vector3 m_verticalDir;

	// belong to which group
    size_t m_groupID;
    SimilarityData m_simData;

public:
    friend class CStdSkeletonLimbHelper;
};

inline const InterfacePtr<Interface>& StdSkeletonLimb::GetUserData() const
{
	return m_pUserData;
}

inline void StdSkeletonLimb::SetUserData(const InterfacePtr<Interface>& pUserdata)
{
	m_pUserData = pUserdata;
}

WING_END

#endif // #ifndef STDSKELETONLIMB_102111212007_H
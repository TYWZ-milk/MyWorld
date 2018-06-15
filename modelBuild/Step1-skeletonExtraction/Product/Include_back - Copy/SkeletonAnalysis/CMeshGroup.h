// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/09/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CMESHGROUP_18091292007_H
#define CMESHGROUP_18091292007_H

#include "Mesh/TriMesh.h"
#include "TreeLimbDisk.h"

WING_BEGIN

class CMeshGroup
{
public:
	AnalysisExport CMeshGroup();
	AnalysisExport virtual ~CMeshGroup();

	AnalysisExport void Destroy();
	AnalysisExport bool Create(TriMesh& mesh);
	AnalysisExport bool RayTrace(
		OUT real& fScale, 
		OUT bool& bHitFront, 
		OUT uint32& nTriangleIndex, 
		IN const TriMesh& mesh, 
		IN const Vector3& vStart, 
		IN const Vector3& vDir, 
		IN uint32 meshGroup) const;
	AnalysisExport bool IsCollectableDisk(
		IN TriMesh& mesh, 
		IN const Vector3& vStart, 
		IN const Vector3& vEnd, 
		IN uint32 group1, 
		IN uint32 group2, 
		IN real radius);

public:
	inline const Plane& GetFacePlane(size_t faceIndex) const;
	inline uint32 GetFaceGroup(size_t faceIndex) const;
	inline real GetMaximalEdgeLength(size_t faceIndex) const;

	inline const Vector3& GetEdgeDir(size_t faceIndex, size_t edgeIndex) const;
	inline real GetEdgeLength(size_t faceIndex, size_t edgeIndex) const;

private:
	AnalysisExport void CleanMembers();
	AnalysisExport bool IsCollide(
		IN TriMesh& mesh, 
		IN uint32 group1, 
		IN uint32 group2, 
		IN const LimbDisk& disk);

private:
	// 三角面片所在平面数组，大小是n
	vector<Plane> m_facePlanes;
	// 边的方向数组，大小是3n
	vector<Vector3> m_edgeDirs;
	// 边长度数组，大小是3n
	vector<real> m_edgeLength;
	// 记录每个面片最长边的长度，大小是n
	vector<real> m_maximalEdgeLength;
	// 记录索引号为i的片面属于哪个group， 每个group对应一个island， island内的面片是连通的
	vector<uint32> m_faceGroups;
	
	// 这个只是一个temp变量，用来存储一个group里的面
	vector<uint32> m_connectedFaces;

private:
	vector<size_t> m_collideEdges;
};

inline const Plane& CMeshGroup::GetFacePlane(size_t faceIndex) const
{
	return m_facePlanes[faceIndex];
}

inline uint32 CMeshGroup::GetFaceGroup(size_t faceIndex) const
{
	return m_faceGroups[faceIndex];
}

inline real CMeshGroup::GetMaximalEdgeLength(size_t faceIndex) const
{
	return m_maximalEdgeLength[faceIndex];
}

inline const Vector3& CMeshGroup::GetEdgeDir(size_t faceIndex, size_t edgeIndex) const
{
	return m_edgeDirs[faceIndex*3+edgeIndex];
}

inline real CMeshGroup::GetEdgeLength(size_t faceIndex, size_t edgeIndex) const
{
	return m_edgeLength[faceIndex*3+edgeIndex];
}

WING_END

#endif // #ifndef CMESHGROUP_18091292007_H
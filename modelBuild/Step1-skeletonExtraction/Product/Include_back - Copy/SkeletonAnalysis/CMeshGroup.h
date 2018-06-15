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
	// ������Ƭ����ƽ�����飬��С��n
	vector<Plane> m_facePlanes;
	// �ߵķ������飬��С��3n
	vector<Vector3> m_edgeDirs;
	// �߳������飬��С��3n
	vector<real> m_edgeLength;
	// ��¼ÿ����Ƭ��ߵĳ��ȣ���С��n
	vector<real> m_maximalEdgeLength;
	// ��¼������Ϊi��Ƭ�������ĸ�group�� ÿ��group��Ӧһ��island�� island�ڵ���Ƭ����ͨ��
	vector<uint32> m_faceGroups;
	
	// ���ֻ��һ��temp�����������洢һ��group�����
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
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

#ifndef CDISKCONTAINER_19301292007_H
#define CDISKCONTAINER_19301292007_H

#include "Mesh/TriMesh.h"
#include "CMeshGroup.h"
#include "Mesh/OctTree.h"
#include "TreeLimbDisk.h"
#include "SkeletonAnalysis/CDiskCollector.h"

WING_BEGIN

class CDiskContainer
{
public:
	AnalysisExport CDiskContainer();
	AnalysisExport virtual ~CDiskContainer();

	AnalysisExport void Destroy();
	AnalysisExport void Create(const AxisAlignBox& bbox, real minimalNodeSize);
	AnalysisExport void AddLimbDisk(const LimbDisk& disk);
	AnalysisExport void MergeNearbyDisks();
	AnalysisExport size_t CalculateAllNodeCount() const;

	inline size_t GetLimbDiskCount() const;
	inline const LimbDisk& GetLimbDisk(size_t diskItem) const;

	inline bool CheckDiskFlag(size_t diskItem, const Bitfields& flag) const;
	inline Bitfields GetDiskFlag(size_t diskItem) const;
	inline void SetDiskFlag(size_t diskItem, const Bitfields& flag);
	inline void ClearDiskFlag(size_t diskItem, const Bitfields& flag);
	AnalysisExport void ClearAllDiskFlags(const Bitfields& flag);

	inline real GetMaximalEdgeLength() const;

	AnalysisExport void RenderDebugVertices();

public:
	AnalysisExport void CollectNearbyDisks(size_t diskIndex);
	AnalysisExport void CollectNearbyDisks(const Sphere3& sphere);

	inline size_t GetCollectedDiskCount() const;
	inline const LimbDisk& GetCollectedDisk(size_t index) const;
	inline size_t GetCollectDiskIndex(size_t index) const;

protected:
	friend class CDiskAppender;
	AnalysisExport void OnAddNewItemToNode(OctTreeNode* pNode);
	AnalysisExport bool IsMergable(uint32 diskItem1, uint32 diskItem2) const;
	AnalysisExport void Merge(uint32 diskItem1, uint32 diskItem2);
	AnalysisExport const Sphere3& GetDiskItemSphere(uint32 diskItem) const;

protected:
	AnalysisExport void DirtyDisk(size_t dirtyDiskIndex);
	AnalysisExport void DirtyAllDisk();
	AnalysisExport void BuildDebugVertices();

private:
	AnalysisExport void CleanMembers();

private:
	real m_minimalNodeSize;
	real m_maximalSphereRadius;
	real m_maximalEdgeLength;
	OctTree m_octTree;
	vector<LimbDisk> m_disks;
	vector<Bitfields> m_flags;
	vector<Sphere3> m_diskSpheres;
	vector<OctTreeNode*> m_newlyAddedToNodes;
	TPointerArray<vector<LimbDisk> > m_needToWeldDisks;
	CDiskCollector m_diskCollector;

private:
	// for debug
	size_t m_lastDirtyDisk;
	bool m_bDirtyAll;
	LimbDiskCenterRenderer m_debugCenterInfo;
	vector<LimbDiskRenderer> m_diskRenderer;
};

inline size_t CDiskContainer::GetLimbDiskCount() const
{
	return m_disks.size();
}

inline const LimbDisk& CDiskContainer::GetLimbDisk(size_t diskItem) const
{
	return m_disks[diskItem];
}

inline bool CDiskContainer::CheckDiskFlag(size_t diskItem, const Bitfields& flag) const
{
	return m_flags[diskItem].CheckFlag(flag);
}

inline Bitfields CDiskContainer::GetDiskFlag(size_t diskItem) const
{
	return m_flags[diskItem];
}

inline void CDiskContainer::SetDiskFlag(size_t diskItem, const Bitfields& flag)
{
	m_flags[diskItem].SetFlag(flag);
}

inline void CDiskContainer::ClearDiskFlag(size_t diskItem, const Bitfields& flag)
{
	m_flags[diskItem].ClearFlag(flag);
}

inline real CDiskContainer::GetMaximalEdgeLength() const
{
	return m_maximalEdgeLength;
}

inline size_t CDiskContainer::GetCollectedDiskCount() const
{
	return m_diskCollector.GetCollectedDiskCount();
}

inline const LimbDisk& CDiskContainer::GetCollectedDisk(size_t index) const
{
	return m_diskCollector.GetCollectedDisk(index);
}

inline size_t CDiskContainer::GetCollectDiskIndex(size_t index) const
{
	return m_diskCollector.GetCollectDiskIndex(index);
}

WING_END

#endif // #ifndef CDISKCONTAINER_19301292007_H

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

#ifndef CDISKCOLLECTOR_20411292007_H
#define CDISKCOLLECTOR_20411292007_H

#include "TreeLimbDisk.h"
#include "Mesh/OctTree.h"

WING_BEGIN

class CDiskContainer;

class CDiskCollector : public IOctTreeVisitor
{
public:
	AnalysisExport CDiskCollector();
	AnalysisExport virtual ~CDiskCollector();

	AnalysisExport void Destroy();
	AnalysisExport void CollectDisks(
		IN CDiskContainer& diskContainer, 
		IN OctTree& tree, 
		IN const Sphere3& sphere);

	AnalysisExport size_t GetCollectedDiskCount() const;
	AnalysisExport const LimbDisk& GetCollectedDisk(size_t index) const;
	AnalysisExport size_t GetCollectDiskIndex(size_t index) const;

protected:
	AnalysisExport virtual VisitorIntent VisitNode(OctTreeNode* pNode);

private:
	AnalysisExport void CleanMembers();
	AnalysisExport void ResetFlags();
	AnalysisExport void OnCollect(uint32 itemIndex);

private:
	CDiskContainer* m_pDiskContainer;
	OctTree* m_pOctTree;
	Sphere3 m_sphere;
	vector<uint32> m_Collected;
	vector<bool> m_IsCollected;
};

WING_END

#endif // #ifndef CDISKCOLLECTOR_20411292007_H
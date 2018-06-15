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

#ifndef CDISKAPPENDER_20401292007_H
#define CDISKAPPENDER_20401292007_H

#include "TreeLimbDisk.h"
#include "Mesh/OctTree.h"

WING_BEGIN

class CDiskContainer;

class CDiskAppender : public IOctTreeVisitor
{
public:
	AnalysisExport CDiskAppender();
	AnalysisExport virtual ~CDiskAppender();

	AnalysisExport void Destroy();

	AnalysisExport void AppendDisk(
		IN CDiskContainer& diskContainer, 
		IN OUT OctTree& octTree, 
		IN real minimalNodeSize, 
		IN uint32 diskItemId);

	AnalysisExport bool IsMergedToExistingDisk() const;

protected:
	AnalysisExport void Create(
		IN CDiskContainer& diskContainer, 
		IN real minimalNodeSize, 
		IN uint32 diskItemId, 
		IN bool merge);

	AnalysisExport virtual VisitorIntent VisitNode(OctTreeNode* pNode);

	AnalysisExport bool MergeToNode(OctTreeNode* pNode);

private:
	AnalysisExport void CleanMembers();

private:
	CDiskContainer* m_pDiskContainer;
	uint32 m_diskItemId;
	const Sphere3* m_pSphere;
	real m_minimalNodeSize;
	bool m_bMerge;
	bool m_bSuccessfullyMerged;
};

WING_END

#endif // #ifndef CDISKAPPENDER_20401292007_H
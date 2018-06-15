// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/10/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CLIMBPICKER_113112102007_H
#define CLIMBPICKER_113112102007_H

#include "CDiskContainer.h"
#include "CMeshGroup.h"
#include "Utility/StlDeque.h"

WING_BEGIN

class CLimbPicker
{
public:
	AnalysisExport CLimbPicker();
	AnalysisExport virtual ~CLimbPicker();

	AnalysisExport void Destroy();

	// set configurations
	AnalysisExport void SetEdgeDistanceEpsilon(real edgeDistanceEpsilon);
	AnalysisExport void SetNegativeAlphaThreshold(real negativeAlphaDegreeThreshold);
	AnalysisExport void SetPositiveAlphaThreshold(real positiveAlphaDegreeThreshold);
	AnalysisExport void SetBetaThreshold(real betaDegreeThreshold);
	AnalysisExport void SetSameFaceEpsilon(real sameFaceEpsilon);

	AnalysisExport bool BeginPickLimbs(
		IN TriMesh& mesh, 
		IN CMeshGroup& meshGroup, 
		IN CDiskContainer& diskContainer);

	AnalysisExport bool PickNextLimbDisk();

	AnalysisExport void RenderLimbConnections(const RenderSystemPtr& pRenderSystem);

	inline size_t GetPickedLimbCount() const;
	inline size_t GetPickedLimbDiskCount(size_t limbIndex) const;
	inline size_t GetPickedLimbDisk(size_t limbIndex, size_t diskIndex) const;

private:
	AnalysisExport void NewPickLimbData();
	AnalysisExport bool PickNextLimbDisk(
		OUT size_t& pickedDiskIndex, 
		IN size_t prevStartIndex, 
		IN size_t prevEndIndex, 
		IN bool acropetal);
	AnalysisExport bool PickMaximalRadiusDisk(OUT size_t& maximalRadiusDisk);
	// member output: 
	//     - m_diskDistance
	//     - m_possibleDiskTanAlpha
	//     - m_possibleDiskCosBeta
	//     - m_possibleDisks
	AnalysisExport void SearchPossibleDisks(
		IN size_t selectedDiskIndex, 
		IN const Vector3* pPreviousDirection, 
		IN bool acropetal);
	AnalysisExport bool CheckCollision(
		IN const LimbDisk& from_disk, 
		IN const LimbDisk& dest_disk1, 
		IN const LimbDisk& dest_disk2);

private:
	AnalysisExport void CleanMembers();

private:
	// configurations
	real m_edge_distance_epsilon;
	real m_edge_distance_epsilonSq;
	real m_negative_alpha_threshold;
	real m_positive_alpha_threshold;
	real m_beta_threshold;
	real m_tangent_negative_alpha_threshold;
	real m_tangent_positive_alpha_threshold;
	real m_cos_beta_threshold;
	real m_same_face_epsilon;

private:
	// source data
	TriMesh* m_pMesh;
	CMeshGroup* m_pMeshGroup;
	CDiskContainer* m_pDiskContainer;

private:
	// temporary data
	vector<real> m_diskDistance;
	// ---------------------------------
	// Tangent alpha
	// ---------------------------------
	//      disk2
	//       __
	//      /  \   |
	//     /    \  |
	//    /      \A|
	//   /        \|
	//  ------------
	//      disk1
	vector<real> m_possibleDiskTanAlpha;
	// ---------------------------------
	// Cosine beta
	// ---------------------------------
	//        disk2
	//     |   /
	//     |  /
	//     |B/
	//     |/
	//    disk1
	vector<real> m_possibleDiskCosBeta;
	vector<uint32> m_possibleDisks;
	vector<uint32> m_tempararyPossibleDisks;

private:
	struct PickLimbData
	{
		size_t m_prevStartIndex;
		size_t m_prevEndIndex;
		size_t m_pickedDiskIndex;
		size_t m_firstTwoDiskIndex[2];
		size_t m_picked_count;
		bool m_bAcropetalOver;
		bool m_bCounterpetalOver;
		deque<size_t> m_pickedDisks;

		bool m_bDebugVerticesDirty;
		vector<UserPrimitiveVertex> m_debugVertices;
	};
	// output data
	vector<PickLimbData> m_pickData;
};

inline size_t CLimbPicker::GetPickedLimbCount() const
{
	return m_pickData.size();
}

inline size_t CLimbPicker::GetPickedLimbDiskCount(size_t limbIndex) const
{
	return m_pickData[limbIndex].m_pickedDisks.size();
}

inline size_t CLimbPicker::GetPickedLimbDisk(size_t limbIndex, size_t diskIndex) const
{
	return m_pickData[limbIndex].m_pickedDisks[diskIndex];
}

WING_END

#endif // #ifndef CLIMBPICKER_113112102007_H
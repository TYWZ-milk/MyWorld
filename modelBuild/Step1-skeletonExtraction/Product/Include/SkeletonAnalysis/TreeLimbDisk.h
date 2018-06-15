// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   11/17/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef TREELIMBDISK_205111172007_H
#define TREELIMBDISK_205111172007_H

#include "AnalysisBase.h"
#include "RenderSystem/IRenderDevice.h"

WING_BEGIN

const Color4 DEFAULT_LIMB_DISK_COLOR = Color4(0xff00ff00);

#define GROUP_MESH TRUE

class LimbDisk
{
public:

	inline real GetRadiusEquality(const LimbDisk& other_disk) const
	{
		return GetEqualityPercent(radius, other_disk.radius);
	}

	inline real GetDistanceSquared(const LimbDisk& other_disk) const
	{
		return (center - other_disk.center).GetLengthSquared();
	}

	AnalysisExport bool IntersectionLineSegment(
		OUT Vector3& vOut, 
		IN const Vector3& vStart, 
		IN const Vector3& vEnd, 
		IN real epsilon) const;

public:
	Vector3 center;
	Vector3 normal;
	real radius;
	real maxEdgeLength;
#if (GROUP_MESH)
	uint32 meshGroup;
#endif
	real weight;
};

AnalysisExport bool IsIntersected(
	// 两条线段的最短距离
	OUT real& nearestDistance, 
	// lhs 线上距离 rhs线段最近的点
	OUT Vector3& lhs_nearest_point, 
	// rhs 线上距离 lhs线段最近的点
	OUT Vector3& rhs_nearest_point, 
	IN const LimbDisk& lhs_disk1, 
	IN const LimbDisk& lhs_disk2, 
	IN const LimbDisk& rhs_disk1, 
	IN const LimbDisk& rhs_disk2, 
	IN const real epsilon);

AnalysisExport bool IsOverlapped(
	IN const LimbDisk& lhs_disk1, 
	IN const LimbDisk& lhs_disk2, 
	IN const LimbDisk& rhs_disk1, 
	IN const LimbDisk& rhs_disk2, 
	IN const real epsilon);

class LimbDiskRenderer
{
public:

	AnalysisExport void Create(
		const LimbDisk& disk, 
		real minimalLineSegment, 
		const Color4& color);
	AnalysisExport void UpdateColor(const Color4& color);
	AnalysisExport void Render(const RenderSystemPtr& pRenderSystem);

public:
	TDynArray<UserPrimitiveVertex> m_circle;
};

class LimbDiskCenterRenderer
{
public:
	AnalysisExport void Clear();
	AnalysisExport void AddDisk(const LimbDisk& disk);
	AnalysisExport size_t GetDiskCount() const;
	AnalysisExport void SetDisk(size_t index, const LimbDisk& disk);
	AnalysisExport void Render(const RenderSystemPtr& pRenderSystem);

public:
	TDynArray<UserPrimitiveVertex> m_centerPoints;
};

struct LimbDiskRadiusLess : public std::binary_function<LimbDisk, LimbDisk, bool>
{
	bool operator()(const LimbDisk& lhs, const LimbDisk& rhs) const
	{
		return lhs.radius < rhs.radius;
	}
};

struct LimbDiskRadiusGreater : public std::binary_function<LimbDisk, LimbDisk, bool>
{
	bool operator()(const LimbDisk& lhs, const LimbDisk& rhs) const
	{
		return lhs.radius > rhs.radius;
	}
};

WING_END

#endif // #ifndef TREELIMBDISK_205111172007_H
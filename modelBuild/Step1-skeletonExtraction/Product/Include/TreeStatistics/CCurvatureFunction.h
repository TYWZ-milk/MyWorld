// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   01/04/2008 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CCURVATUREFUNCTION_1127142008_H
#define CCURVATUREFUNCTION_1127142008_H

#include "StatisticsBase.h"
#include "Utility/SharedPtr.h"
#include "CAngleWave.h"

WING_BEGIN

enum LimbTrend
{
	Trend_Unknown, 
	Trend_Up, 
	Trend_Horizontal, 
	Trend_Down, 

	Trend_Count, 
};

class CCurvatureFunction
{
public:
	TreeStatExport CCurvatureFunction();
	TreeStatExport virtual ~CCurvatureFunction();

	TreeStatExport void Destroy();
	TreeStatExport void Create(const StdSkeletonLimb& limb);

	TreeStatExport real GetLimbLength() const;
	TreeStatExport LimbTrend GetTrend() const;
	TreeStatExport real GetAverageCurvature() const;
	TreeStatExport real GetAverageInterknotLength() const;
	TreeStatExport real GetBeforeCurveLength() const;
	TreeStatExport real GetCurveLength() const;
	TreeStatExport real GetRotateToTrendDegree() const;
	TreeStatExport real GetFinalDegree() const;

	TreeStatExport size_t GetPossibleHAngleCount() const;
	TreeStatExport real GetPossibleHAngle(size_t i) const;
	TreeStatExport size_t GetPossibleHAngleLengthCount() const;
	TreeStatExport real GetPossibleHAngleLength(size_t i) const;

	TreeStatExport size_t GetPossibleVAngleCount() const;
	TreeStatExport real GetPossibleVAngle(size_t i) const;
	TreeStatExport size_t GetPossibleVAngleLengthCount() const;
	TreeStatExport real GetPossibleVAngleLength(size_t i) const;

private:
	TreeStatExport void CleanMembers();
	TreeStatExport void InputSample(
		const Vector3& thisPosition, 
		const Coordinate3& thisCoordinate, 
		real thisInterknotLength);
	TreeStatExport void EndInput();
	TreeStatExport void BuildAverageInterknotLength();
	TreeStatExport void BuildAverageCurvature();
	TreeStatExport void BuildTrend();
	TreeStatExport void BuildCurvatureToTrend();

private:
	// utility functions
	TreeStatExport Vector3 GetLastEndPosition() const;
	TreeStatExport void GetFirstPartInformation(
		Vector3& vFirstDir, 
		// [0, nFirstLineEndIndex)
		size_t& nFirstLineEndIndex, 
		real& firstLineLength);
	TreeStatExport void GetLastPartInformation(
		Vector3& vLastDir, 
		// [nLastLineStartIndex, end)
		size_t& nLastLineStartIndex, 
		real& lastLineLength);
	TreeStatExport real GetRotateToTrendDegree(
		real verticalDegree0, 
		real verticalDegree1);

private:

	struct InputData
	{
		real interknotLength;
		Vector3 position;
		Coordinate3 thisCoordinate;
	};

	real m_limbLength;
	LimbTrend m_trend;
	real m_averageCurvature;
	real m_averageInterknotLength;
	real m_beforeCurveLength;
	real m_curveLength;
	real m_rotateToTrendDegree;
	real m_finalDegree;

	vector<real> m_rotateHAngles;
	vector<real> m_rotateVAngles;
	vector<real> m_rotateHAngleLengths;
	vector<real> m_rotateVAngleLengths;
	vector<InputData> m_inputDatas;
};

typedef SharedPtr<CCurvatureFunction> CurvatureFunctionPtr;

WING_END

#endif // #ifndef CCURVATUREFUNCTION_1127142008_H

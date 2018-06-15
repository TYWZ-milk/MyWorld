// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/16/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CSAMPLECURVE1D_9381242007_H
#define CSAMPLECURVE1D_9381242007_H

#include "CPolynomial.h"
#include "CCardinalSpline.h"

WING_BEGIN

struct IndexOfTLess : public std::binary_function<size_t, size_t, bool>
{
public:
	IndexOfTLess(const vector<real>& ts) : m_ts(ts) {}
	IndexOfTLess(const IndexOfTLess& from) : m_ts(from.m_ts) {}

	inline bool operator()(size_t lhs, size_t rhs)
	{
		return m_ts[lhs] < m_ts[rhs];
	}

private:
	IndexOfTLess();
	IndexOfTLess& operator = (const IndexOfTLess& from);

private:
	const vector<real>& m_ts;
};

class CSampleCurve1D
{
public:
	TreeStatExport CSampleCurve1D();
	TreeStatExport virtual ~CSampleCurve1D();

	TreeStatExport void Destroy();

	TreeStatExport virtual void BeginInputSample();
	TreeStatExport virtual void InputSample(real t, real value);
	TreeStatExport virtual real GetMaximalT() const;
	TreeStatExport virtual void ShiftRight(real shiftValue);
	TreeStatExport virtual bool EndInputSample(size_t degree, real angle = (real)DEFAULT_TANGENT_ANGLE, int monotonicity = 0 );
	TreeStatExport virtual bool IsValid() const;

	TreeStatExport virtual real EvaluateMin(real t) const;
	TreeStatExport virtual real EvaluateBest(real t) const;
	TreeStatExport virtual real EvaluateMax(real t) const;
	TreeStatExport virtual real EvaluateRandom(real t);
	TreeStatExport virtual bool EvaluateRandom(const real* x, size_t n, real tolerant, OUT real* y);
	TreeStatExport virtual bool EvaluateRandom(
		// 最大的x
		real bp, 
		// 最小的x
		real tau, 
		// 最小的x间隔
		real minimalInterval, 
		// 方差的误差百分比
		real tolerant, 
		OUT vector<real>& vx, 
		OUT vector<real>& vy);

public:
	TreeStatExport virtual size_t GetInputSampleCount() const;
	TreeStatExport virtual const real& GetInputSampleT(size_t index) const;
	TreeStatExport virtual const real& GetInputSampleV(size_t index) const;
	TreeStatExport const CPolynomial& GetBestPolynomial() const;
	TreeStatExport const bool GetBestPolynomial(real& a, real& b);

public:
	TreeStatExport virtual void BuildDebugVertices();
	TreeStatExport virtual void RenderDebugVertices( bool renderRandom = true ) const;

	TreeStatExport virtual void BuildDebugVertices( real x, real y );
	TreeStatExport virtual void BuildDebugVertices( const real* x, const real* y, size_t n );
	TreeStatExport virtual void BuildDebugVertices( const vector<real>& vx, const vector<real>& vy );
	TreeStatExport virtual void TestEvaluateRandom();

	TreeStatExport virtual void UnifyDebugVertices( const Vector3& origin, const Vector2& size );

private:
	TreeStatExport void CleanMembers();

private:
	GSLMathUtilPtr m_pMathUtil;
	real m_minimalT;
	real m_maximalT;
	real m_minimalV;
	real m_maximalV;
	CPolynomial m_bestPolynomial;
	real m_minimalMin;
	real m_maximalMax;
	vector<real> m_ts;
	vector<real> m_vs;
	real m_tScale;
	real m_vScale;
	vector<real> m_scaledTs;
	vector<real> m_scaledVs;
	bool m_bValid;

	CCardinalSpline m_minSpline;
	CCardinalSpline m_maxSpline;
	real m_mean_square_deviation;

private:
	// for debug
	vector<UserPrimitiveVertex> m_bestLine;
	vector<UserPrimitiveVertex> m_minLine;
	vector<UserPrimitiveVertex> m_maxLine;
	vector<AxisAlignBox> m_samplePoints;

	vector<AxisAlignBox> m_randomPoints1;
	vector<AxisAlignBox> m_randomPoints2;
	vector<AxisAlignBox> m_randomPoints3;

	static bool m_bHaveSaved;
};

WING_END

#endif // #ifndef CSAMPLECURVE1D_9381242007_H
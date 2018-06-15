// -----------------------------------------------------------------------------
// History: 
//   11/29/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef ICURVE1D_202511292007_H
#define ICURVE1D_202511292007_H

#include "StatisticsBase.h"
#include "B_Spline/BSpline1D.h"
#include "IRandomWeightCurve.h"

WING_BEGIN

class ICurve1D;
typedef InterfacePtr<ICurve1D> Curve1DPtr;

class ICurve1D : public Interface
{
public:
	static inline InterfaceID IID() { return InterfaceID(0xb9f6e60, 0x7dac1d4b); };

	virtual void BeginInputSample() = 0;
	virtual void InputSample(real t, real value) = 0;
	virtual real GetMaximalT() const = 0;
	virtual void ShiftRight(real offset) = 0;
	virtual void EndInputSample() = 0;
	virtual void SetBoundaryDerivative(
		real leftBoundaryDerivative, 
		real rightBoundaryDerivative) = 0;

	virtual void ScaleT(real scaleValue) = 0;
	virtual void ScaleValue(real scaleValue) = 0;

	virtual void BuildReciprocalCurve() = 0;
	virtual void BuildIntegralCurve() = 0;
	virtual Curve1DPtr Clone() const = 0;
	virtual void CopyFrom(const Curve1DPtr& pCurve) = 0;

	virtual void BuildDebugVertices(
		real minimalSegment, 
		real scaleT, 
		real scaleValue, 
		uint32 color, 
		bool linear = false) = 0;
	virtual void RenderDebugVertices() = 0;

	virtual void BuildBSpline() = 0;

	virtual real Evaluate(real t) const = 0;
	virtual real EvaluateLinear(real t) const = 0;

	virtual size_t LowerBound(real t) const = 0;
	virtual size_t GetKeyPointCount() const = 0;
	virtual real GetKeyPointT(size_t keyPointIndex) const = 0;
	virtual real GetKeyPointValue(size_t keyPointIndex) const = 0;

	virtual void WeldRedundantT() = 0;
	virtual void MakeSameKeyPointCount(
		const Curve1DPtr& pCurve1, 
		const Curve1DPtr& pCurve2) = 0;

	virtual void UniformKeyPointCount(size_t keyPointCount) = 0;
	virtual void MultiplyWeight(const RandomWeightCurvePtr& pWeight) = 0;
	virtual void Add(const Curve1DPtr& pCurve) = 0;
};

WING_END

#endif // #ifndef ICURVE1D_202511292007_H
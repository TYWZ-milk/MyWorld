// -----------------------------------------------------------------------------
// History: 
//   11/29/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef ICURVE3D_212111292007_H
#define ICURVE3D_212111292007_H

#include "ICurve1D.h"

WING_BEGIN

class ICurve3D : public Interface
{
public:
	static inline InterfaceID IID() { return InterfaceID(0x1c5a496e, 0xaa243b); };

	virtual void BeginInputSample() = 0;
	virtual void InputSample(real t, const Vector3& value) = 0;
	virtual void EndInputSample() = 0;

	virtual void Create(
		const Curve1DPtr& pCurveX, 
		const Curve1DPtr& pCurveY, 
		const Curve1DPtr& pCurveZ) = 0;

	virtual real GetMaximalT() const = 0;
	virtual void ScaleT(real scaleValue) = 0;
	virtual void ScaleValue(real scaleValue) = 0;

	virtual Vector3 Evaluate(real t) const = 0;

	virtual Curve1DPtr GetCurveX() const = 0;
	virtual Curve1DPtr GetCurveY() const = 0;
	virtual Curve1DPtr GetCurveZ() const = 0;
};

typedef InterfacePtr<ICurve3D> Curve3DPtr;

WING_END

#endif // #ifndef ICURVE3D_212111292007_H
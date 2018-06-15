// -----------------------------------------------------------------------------
// History: 
//   11/30/2007 Yuan.YUAN Created.
// -----------------------------------------------------------------------------

#ifndef IGSL_MATH_UTIL_yy_H
#define IGSL_MATH_UTIL_yy_H

#include "Utility/Interface.h"
#include "Utility/InterfacePtr.h"

WING_BEGIN

class IGSLMathUtil : public Interface
{
public:
	static inline InterfaceID IID() { return InterfaceID(0x6fa52d72, 0x6fa54713); };

	// random number
	virtual real Random() = 0;
	virtual real Ran_Gaussian( real mu, real sigma ) = 0;

	// least squares fitting
	virtual bool FitWLinear( const real* x, const real* y, const real* w, size_t n,
					/*OUT*/	 real* c0, real* c1, real* chisq ) = 0;
	virtual bool MultiFitWLinear( const real* x, const real* y, const real* w, size_t n, size_t mag,
					/*OUT*/	 real* c, real* chisq ) = 0;
	virtual bool MultiFitNonLinear( const real* x, const real* y, size_t n, size_t mag,
					/*OUT*/	 real* c, real* chisq_dof, bool log = false ) = 0;
	virtual bool MultiFitNonLinearLine( const real* x, const real* y, size_t n, real angle, int monotonicity,
					/*OUT*/	 real* c0, real* c1, real* chisq_dof, bool log = false ) = 0;

	// interpolation
	virtual bool SplineInitial( const real* x, const real* y, size_t n, int type = 2 ) = 0;	// type: 0-linear, 1-polynomial, 2-cubic
	virtual bool SplineFree() = 0;
	virtual bool SplineEval( real x, /*OUT*/ real* y ) = 0;
	virtual bool SplineEvalDeriv( real x, real* d ) = 0;
	virtual bool SplineEvalDeriv2( real x, real* d2 ) = 0;
	virtual bool SplineEvalInteg( real a, real b, real* result ) = 0;

	// fast fourier transforms
	virtual bool FFTRealTransform( const real* data, size_t n, /*OUT*/ real* amplitude ) = 0;
};

typedef InterfacePtr<IGSLMathUtil> GSLMathUtilPtr;

WING_END

#endif // end of #ifndef IGSL_MATH_UTIL_yy_H
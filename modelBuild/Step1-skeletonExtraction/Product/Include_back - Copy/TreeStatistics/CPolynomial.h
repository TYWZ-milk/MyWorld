// -----------------------------------------------------------------------------
// History: 
//   12/04/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef CPOLYNOMIAL_13371242007_H
#define CPOLYNOMIAL_13371242007_H

#include "StatisticsBase.h"

WING_BEGIN

#define DEFAULT_TANGENT_ANGLE 0.7853982

class CPolynomial
{
public:
	TreeStatExport CPolynomial();
	TreeStatExport virtual ~CPolynomial();

	TreeStatExport CPolynomial& operator = (const CPolynomial& from);

	TreeStatExport void Destroy();

	TreeStatExport void CreateConstant(real constant);
	TreeStatExport bool BestFit(
		size_t degree, 
		const real* pTs, 
		const real* pValues, 
		const real* pWeights, 
		size_t samples,
		real angle = (real)DEFAULT_TANGENT_ANGLE,
		int monotonicity = 0 );

	TreeStatExport real Evaluate(real x) const;
	TreeStatExport real EvaluatePolynomial(real x) const;
	TreeStatExport real EvaluateDerivative(real x) const;

	TreeStatExport size_t GetCoefficientsCount();
	TreeStatExport real* GetCoefficients();
	TreeStatExport const real* GetCoefficients() const;

	TreeStatExport real GetLeftBoundaryDerivative() const;
	TreeStatExport real GetRightBoundaryDerivative() const;
	TreeStatExport real GetLeftBoundaryValue() const;
	TreeStatExport real GetRightBoundaryValue() const;

private:
	TreeStatExport void CleanMembers();

private:
	//CPolynomial(const CPolynomial& from);

private:
	GSLMathUtilPtr m_pMathUtil;
	real m_leftBoundaryDerivative;
	real m_rightBoundaryDerivative;
	real m_leftBoundaryValue;
	real m_rightBoundaryValue;
	vector<real> m_coefficients;
};

WING_END

#endif // #ifndef CPOLYNOMIAL_13371242007_H
// -----------------------------------------------------------------------------
// History: 
//   12/21/2007 Yuan.YUAN Created.
// -----------------------------------------------------------------------------

#ifndef CCARDINALSPLINE_131612212007_yy_H
#define CCARDINALSPLINE_131612212007_yy_H

#include "StatisticsBase.h"
#include "MathUtil/IGSLMathUtil.h"

WING_BEGIN

class CCardinalSpline
{
public:
	TreeStatExport CCardinalSpline();
	TreeStatExport virtual ~CCardinalSpline();

	TreeStatExport CCardinalSpline& operator = (const CCardinalSpline& from);

	TreeStatExport void Destroy();

	TreeStatExport bool ImportScaledSamples( const real* pTs, const real* pValues, size_t samples );

	TreeStatExport real Evaluate(real x) const;
	TreeStatExport real EvaluateSpline(real x) const;
	TreeStatExport real EvaluateDerivative(real x) const;

	TreeStatExport real GetLeftBoundaryDerivative() const;
	TreeStatExport void SetLeftBoundaryDerivative( real m );
	TreeStatExport real GetRightBoundaryDerivative() const;
	TreeStatExport void SetRightBoundaryDerivative( real m );
	TreeStatExport real GetLeftBoundaryValue() const;
	TreeStatExport real GetRightBoundaryValue() const;

private:
	TreeStatExport void CleanMembers();

private:
	//CCardinalSpline(const CCardinalSpline& from);

private:
	GSLMathUtilPtr m_pMathUtil;
	real m_leftBoundaryDerivative;
	real m_rightBoundaryDerivative;
	real m_leftBoundaryValue;
	real m_rightBoundaryValue;
	vector<real> m_scaledTs;
	vector<real> m_scaledVs;
	vector<real> m_tangents;
};

WING_END

#endif // #ifndef CSPLINE_131612212007_yy_H
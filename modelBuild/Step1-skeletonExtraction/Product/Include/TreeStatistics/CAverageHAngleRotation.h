
#ifndef CAVERAGEANGLEROTATION_124301042007_yy_H
#define CAVERAGEANGLEROTATION_124301042007_yy_H

#include "StatisticsBase.h"
#include "CDistribution1D.h"

WING_BEGIN

#define MAX_MEAN_SQUARE_DEVIATION_ROTATION 500

enum LimbRamificationType
{
	NONE,
	VERTICIL,
	OPPOSITE
};

class CAverageHAngleRotation
{
public:
	TreeStatExport CAverageHAngleRotation();
	TreeStatExport virtual ~CAverageHAngleRotation();

	TreeStatExport void Destroy();
	TreeStatExport void AddLimbData( StdSkeletonLimb& limb );
	TreeStatExport bool BuildCurve();
	TreeStatExport bool IsCurveValid() const;

public:
	TreeStatExport real	Sample();
	TreeStatExport void Sample( OUT vector<vector<real>>& lHAngles, OUT vector<real>& tHAngles );
	TreeStatExport real Sample( size_t events, size_t index );
	TreeStatExport real SampleFirstHAngle();

	TreeStatExport LimbRamificationType GetLimbRamificationType();

private:
	TreeStatExport void CleanMembers();

private:
	LimbRamificationType m_ramiType;
	CDistribution1D m_HAngleDistribution;
	CDistribution1D m_AAngleDistribution;
	map<size_t, vector<CDistribution1D>> m_RAngleDistributionMap;

	vector<real> m_hAngles;
	vector<real> m_rotAAngles;
	map<size_t, real> m_lateralRamiProbability;
	map<size_t, real> m_terminalRamiProbability;
	map<size_t, vector<vector<real>>> m_rAnglesMap;

	size_t m_ramiTypeOPPO;
	size_t m_ramiTypeVERT;
};

WING_END

#endif // #ifndef CAVERAGEANGLEROTATION_124301042007_yy_H
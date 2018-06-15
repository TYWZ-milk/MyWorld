#ifndef __STD_SKELETON_LIMB_HELPER_H_140512182007__
#define __STD_SKELETON_LIMB_HELPER_H_140512182007__

#include "AnalysisBase.h"
#include "TreeLimbDisk.h"
#include "Utility/StlDeque.h"
#include "RenderSystem/IRenderDevice.h"
#include "Geometry/Coordinate3.h"
#include "B_Spline/BSpline.h"


WING_BEGIN

class StdSkeletonLimb;
struct LimbKnotPoint;

struct LinearInterPltData
{
    real start;
    real end;
    real middle;
};

class CStdSkeletonLimbHelper
{
public:
    AnalysisExport CStdSkeletonLimbHelper();
    AnalysisExport ~CStdSkeletonLimbHelper(){};
    
    AnalysisExport BOOL GetMaxDistToParentApex(const TDynArray<StdSkeletonLimb*>& limbArr, real& distToParentApex);
    AnalysisExport BOOL GetMinDistToParentApex(const TDynArray<StdSkeletonLimb*>& limbArr, real& distToParentApex);
    AnalysisExport BOOL GetDistToParentApex(StdSkeletonLimb* pLimb, real& distToParentApex);
    AnalysisExport real GetRelatedDist(real relate, real distToParentApex);
    AnalysisExport BOOL GetVerticalAngle(StdSkeletonLimb* pLimb, real& vAngle);

    AnalysisExport BOOL IsTernimal(StdSkeletonLimb* pLimb);
    AnalysisExport BOOL SetRelateDist(real relatedDist);

    AnalysisExport real DegreeToRadian(real degree);

	AnalysisExport BOOL SetTreeDirtyAll(StdSkeletonLimb* pLimb);
	AnalysisExport BOOL GenRootLimbAddr(StdSkeletonLimb* pLimb, StdSkeletonLimb*& pRootLimb);

	AnalysisExport BOOL CalculateLimbLength(StdSkeletonLimb* pLimb, real& len);
    AnalysisExport BOOL GetEndKnotPoint(StdSkeletonLimb* pLimb, LimbKnotPoint& knotPoint);

    AnalysisExport BOOL SetTreeExistFlag(StdSkeletonLimb* pLimb, bool bExist);
    AnalysisExport BOOL GetLimbExistFlag(StdSkeletonLimb* pLimb);

    AnalysisExport Vector3 GetLimbDir(StdSkeletonLimb* pLimb);

    AnalysisExport bool   EqualFloatZero(real fValue);

    AnalysisExport bool   GetLimbLeafDir(
        StdSkeletonLimb* pLimb, 
        real angleDegree,
        Vector3& leftDir, 
        Vector3& rightdir);

    AnalysisExport Vector3 RotateVector(
        const Vector3& vDir, 
        const Vector3& axis, 
        real angleDegree);

    AnalysisExport bool ClearLimbStaticalData(StdSkeletonLimb* pLimb);
    AnalysisExport bool CopyTree(
        StdSkeletonLimb* pRootLimbSrc, 
        StdSkeletonLimb* pRootLimbDst);
    AnalysisExport bool AdjustLimbRadius(
        StdSkeletonLimb* pLimb, 
        real rootRadius, 
        real endRadius);
    AnalysisExport bool GenerateBSpline(
        StdSkeletonLimb* pLimb, 
        BSpline3Ptr& bSpline);

    AnalysisExport bool GetTPreKnotIndex(
        StdSkeletonLimb* pLimb, 
        BSpline3Ptr pBSpline,
        real tParam,
        size_t& indexPreKnot);

    AnalysisExport bool SetParent(
        StdSkeletonLimb* pLimb, 
        StdSkeletonLimb* pParentLimb);
    
    AnalysisExport bool GenNearestPointOnSplineSeg(
        StdSkeletonLimb* pLimb, 
        size_t           indexKnot,
        Vector3          vInPoint,
        Vector3&         vOutPoint);

    AnalysisExport bool GetLimbNodeLen(
        StdSkeletonLimb* pLimb, 
        size_t startIndex,
        size_t endIndex,
        real&  len);

    AnalysisExport real LinearInterpolate(
        const LinearInterPltData& src,
        LinearInterPltData& dst);

private:
    

private:
    real m_relatedDist;
    
};

WING_END

#endif //__STD_SKELETON_LIMB_HELPER_H_140512182007__
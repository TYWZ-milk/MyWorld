// -----------------------------------------------------------------------------
// History: 
//   11/27/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef LIMBREBUILDER_212811272007_H
#define LIMBREBUILDER_212811272007_H

#include "SkeletonAnalysis/StdSkeletonLimb.h"
#include "RenderSystem/IRenderDevice.h"

WING_BEGIN

class ILimbRebuilder;
typedef InterfacePtr<ILimbRebuilder> LimbRebuilderPtr;

class ILimbRebuilder : public IEntity
{
public:
	static inline InterfaceID IID() { return InterfaceID(0x2ce19a9, 0x7241216d); };

	virtual void SetOrigin(const Vector3& vOrigin) = 0;

	virtual void Clear() = 0;

	virtual bool Create(const StdSkeletonLimbPtr& pLimbRoot, real growth_rate) = 0;

	virtual bool GetStop() = 0;

	virtual void SetStop(bool stop) = 0;

	virtual void ResetTime() = 0;

	virtual void OnTimer(real timeValue) = 0;
    
    virtual void SetDrawSkeletionFlag(bool bDrawSkeleton) = 0;

    virtual void BuildSkeleton() = 0;

	virtual void Draw() = 0;

	virtual void Draw(const RenderSystemPtr& pRenderSystem) = 0;

    virtual size_t GetLateralClusterCount() const = 0;

    virtual size_t GetLateralClusterChildCount(size_t cluster) const = 0;

    virtual LimbRebuilderPtr GetLateralClusterChild(size_t cluster, size_t childIndex) const = 0;

    virtual size_t GetTerminalChildCount() const = 0;

    virtual LimbRebuilderPtr GetTerminalChild(size_t childIndex) const = 0;

    virtual const StdSkeletonLimb& GetSkeletonLimb()const = 0;
};

WING_END

#endif // #ifndef LIMBREBUILDER_212811272007_H
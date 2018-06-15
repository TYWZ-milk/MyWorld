#ifndef __REMESH_H_dsd__
#define __REMESH_H_dsd__

#include "SkeletonAnalysis/StdSkeletonLimb.h"
#include "TreeStatistics/ILimbRebuilder.h"

WING_BEGIN  //namespace

struct Point 
{
    Vector3 position;
	uint32 color;
    Vector3 normal;
    float tU,tV;
};

class IRemesh: public Interface
{

public:
    static inline InterfaceID IID() { return InterfaceID(0xb63383fc, 0xb633cc99); };

public:
    //load a skeleton from a file
    virtual void LoadSkeleton(StdSkeletonLimb* skeletonLimb)=0;
    virtual void LoadSkeleton(LimbRebuilderPtr pSkeletonLimb)=0;

    virtual void SetConfigPureFileName(wstring fileName)=0;

    // generate the triangle mesh
    virtual void GenerateMesh()=0;
    virtual void SetState(bool bWireFrame, bool bLeaf, bool bTexture)=0;
    virtual bool Draw(bool bWireFrame)=0;
    virtual bool DrawShadowMap(
        const Matrix44* pMatWorld,
        const Matrix44* pMatView,
        const Matrix44* pMatProject) = 0;

    //save mesh to file
    virtual void SaveMesh() = 0;

    //get mesh
	virtual size_t GetSubCount() const = 0;
	virtual size_t GetVertexCount(size_t subIndex) const = 0;
	virtual const Point* GetVertexAddress(size_t subIndex) const = 0;

	virtual size_t GetIndexCount(size_t subIndex) const =0;
	virtual const UINT32* GetIndexAddress(size_t subIndex) const = 0;

	virtual TDynArray<TDynArray<Point>*>  GetVertex() = 0;
	virtual TDynArray<TDynArray<UINT32>*> GetIndex() = 0;

};

typedef InterfacePtr<IRemesh> RemeshPtr;

WING_END 
//----------------------------
#endif //__REMESH_H_dsd__

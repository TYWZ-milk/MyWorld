// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   01/04/2008 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef IRANDOMWEIGHTCURVE_1448142008_H
#define IRANDOMWEIGHTCURVE_1448142008_H

#include "StatisticsBase.h"

WING_BEGIN

class IRandomWeightCurve;
typedef InterfacePtr<IRandomWeightCurve> RandomWeightCurvePtr;

class IRandomWeightCurve : public Interface
{
public:
	static inline InterfaceID IID() { return InterfaceID(0x5ecc1e1e, 0x1f5b5f7f); }; 

	virtual void GenerateRandomWeight() = 0;

	virtual void GenerateRandomWeights(
		OUT vector<RandomWeightCurvePtr>& weights, 
		IN size_t needWeightCount) = 0;

	virtual void CopyFrom(const RandomWeightCurvePtr& pWeight) = 0;

	virtual void InvWeight() = 0;

	virtual void Add(const RandomWeightCurvePtr& pWeight) = 0;

	virtual void Multiply(const RandomWeightCurvePtr& pWeight) = 0;

	virtual void Multiply(real weight) = 0;

	virtual void MultiplyInvWeight(const RandomWeightCurvePtr& pWeight) = 0;

	virtual size_t GetWeightCount() const = 0;

	virtual real GetWeight(size_t index) const = 0;

	virtual real Evaluate(real t) const = 0;

	virtual void BuildDebugVertices(uint32 color) = 0;

	virtual void RenderDebugVertices(bool samplePoints) const = 0;
};

WING_END

#endif // #ifndef IRANDOMWEIGHTCURVE_1448142008_H
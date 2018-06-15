// -----------------------------------------------------------------------------
// History: 
//   11/26/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef IGROWTHFUNCTION_145211262007_H
#define IGROWTHFUNCTION_145211262007_H

#include "Utility/InterfacePtr.h"

WING_BEGIN

class IGrowthFunction : public Interface
{
public:
	static inline InterfaceID IID() { return InterfaceID(0x32cc73e5, 0x67ee6a40); };

	virtual void Create(real minimalValue, real maximalValue, real maximalTime) = 0;

	virtual real Evaluate(real timeValue) = 0;
};

typedef InterfacePtr<IGrowthFunction> GrowthFunctionPtr;

WING_END

#endif // #ifndef IGROWTHFUNCTION_145211262007_H
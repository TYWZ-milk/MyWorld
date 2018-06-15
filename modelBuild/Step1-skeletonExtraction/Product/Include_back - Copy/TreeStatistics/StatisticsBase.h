// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/16/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef STATISTICSBASE_160512162007_H
#define STATISTICSBASE_160512162007_H

#include "Utility/Types.h"

#include "Geometry/Vector3.h"
#include "Geometry/Matrix44.h"
#include "Geometry/Coordinate3.h"

#include "Kernel/IEntitySystem.h"

#include "RenderSystem/IRenderDevice.h"

#include "SkeletonAnalysis/StdSkeletonLimb.h"
#include "MathUtil/IGSLMathUtil.h"

#ifndef TREESTATISTICS_EXPORTS
#	define TreeStatExport __declspec(dllimport)
#else
#	define TreeStatExport __declspec(dllexport)
#endif

#endif // #ifndef STATISTICSBASE_160512162007_H
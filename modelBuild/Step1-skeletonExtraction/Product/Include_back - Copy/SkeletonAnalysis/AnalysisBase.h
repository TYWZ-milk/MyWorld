// -----------------------------------------------------------------------------
// Copyright (c) 2007 Power studio. All rights reserved.

// Permission is granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software") 
// for non-commercial use only, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// For commercial use of this software, please concat author.

// History: 
//   12/30/2007 Qilin.Ren Created.
// -----------------------------------------------------------------------------

#ifndef ANALYSISBASE_211612302007_H
#define ANALYSISBASE_211612302007_H

#include "Utility/Bitfields.h"
#include "Utility/TDynArray.h"
#include "Utility/TPointerArray.h"
#include "Utility/IBinaryBuffer.h"
#include "Utility/CBinaryStream.h"
#include "Utility/StlVector.h"
#include "Utility/StlString.h"

#include "Geometry/Vector3.h"
#include "Geometry/AxisAlignedBox.h"
#include "Geometry/TriangleI.h"

#include "Mesh/Meshbase.h"
#include "Mesh/TriFace.h"
#include "Mesh/TriMapChannel.h"
#include "Mesh/TriMesh.h"

#ifndef SKELETONANALYSIS_EXPORTS
#	define AnalysisExport __declspec(dllimport)
#else
#	define AnalysisExport __declspec(dllexport)
#endif

#endif // #ifndef ANALYSISBASE_211612302007_H
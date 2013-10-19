/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_METASL_RUNTIME_MI_TYPES_H
#define MI_METASL_RUNTIME_MI_TYPES_H

#include <mi/base/types.h>

#if MI_BASE_VERSION_MAJOR > 1
#error "MI_BASE_VERSION_MAJOR is greater than 1, but 1 is required for this MetaSL runtime API."
#endif

namespace MI
{
using mi::Sint8;  // 8-bit signed integer
using mi::Uint8;  // 8-bit unsigned integer
using mi::Sint16; // 16-bit signed integer
using mi::Uint16; // 16-bit unsigned integer
using mi::Sint32; // 32-bit signed integer
using mi::Uint32; // 32-bit unsigned integer
using mi::Sint64; // 64-bit signed integer
using mi::Uint64; // 64-bit unsigned integer

using mi::Float32;          // 32-bit IEEE-754 single precision float
using mi::Float64;          // 64-bit IEEE-754 double precision float

typedef Float32 Scalar;     // single precision
typedef Float64 Dscalar;    // double precision

typedef mi::Uint32  Uint;   // unsigned integer

using mi::Size;             // Architecture dependent unsigned word size.
using mi::Difference;       // Architecture dependent signed word size.


} // namespace MI


#endif // MI_METASL_RUNTIME_MI_TYPES_H


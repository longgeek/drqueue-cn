//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/metasl_runtime/function.h
///
//*****************************************************************************

#ifndef MI_METASL_RUNTIME_FUNCTION_H
#define MI_METASL_RUNTIME_FUNCTION_H

#include <mi/math/function.h>

#if MI_MATH_VERSION_MAJOR > 1
#error "MI_MATH_VERSION_MAJOR is greater than 1, but 1 is required for this MetaSL runtime API."
#endif

namespace MI {
namespace MATH {

using mi::math::abs;
using mi::math::isfinite;
using mi::math::isinfinite;
using mi::math::isnan;

// The following definitions are for the benefit of the CIL back-end.

// Maximum value on integers.
inline int maximum(
    int a,              // Left argument.
    int b)              // Right argument.
{
    return mi::math::max(a,b);
}

// Minimum value on integers.
inline int minimum(
    int a,              // Left argument.
    int b)              // Right argument.
{
    return mi::math::min(a,b);
}

// Maximum value on floats.
inline float maximum(
    float a,              // Left argument.
    float b)              // Right argument.
{
    return mi::math::max(a,b);
}

// Minimum value on floats.
inline float minimum(
    float a,              // Left argument.
    float b)              // Right argument.
{
    return mi::math::min(a,b);
}

} // namespace MATH
} // namespace MI

#endif // MI_METASL_RUNTIME_FUNCTION_H

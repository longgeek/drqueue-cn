//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/metasl_runtime/color.h
///
//*****************************************************************************

#ifndef MI_METASL_RUNTIME_COLOR_H
#define MI_METASL_RUNTIME_COLOR_H

#include <mi/math/color.h>
#include <mi/metasl_runtime/function.h>
#include <mi/metasl_runtime/vector.h>

namespace MI {
namespace COLOR {

using mi::math::Color_struct;
using mi::math::Color;

} // namespace COLOR

namespace MSLCOLOR {

// Is finite.
inline MATH::Vector4b isfinite(
    const COLOR::Color &c)            // The Color to test.
{
    return MATH::Vector4b(
            mi::math::isfinite(c.r),
            mi::math::isfinite(c.g),
            mi::math::isfinite(c.b),
            mi::math::isfinite(c.a));
}

// Is NAN.
inline MATH::Vector4b isnan(
    const COLOR::Color &c)            // The Color to test.
{
    return MATH::Vector4b(
            mi::math::isnan(c.r),
            mi::math::isnan(c.g),
            mi::math::isnan(c.b),
            mi::math::isnan(c.a));
}

// Componentwise maximum of Color.
inline COLOR::Color max(
    const COLOR::Color &a,             // The first color.
    const COLOR::Color &b)             // The second color.
{
    return mi::math::elementwise_max(a,b);
}


// Componentwise minimum of Color.
inline COLOR::Color min(
    const COLOR::Color &a,             // The first color.
    const COLOR::Color &b)             // The second color.
{
    return mi::math::elementwise_min(a,b);
}

/// Normalizes color \p c to unit length, iff \p c != 0.
/// Otherwise the parameter is returned unmodified.
inline COLOR::Color normalize(
    const COLOR::Color& c)   // color
{
    COLOR::Color result_col(c);
    Float32 n = length(result_col);
    bool not_null = ( n != 0 );
    if (not_null)
        result_col /= n;
    return result_col;
}


} // namespace MSLCOLOR
} // namespace MI


#endif // MI_METASL_RUNTIME_COLOR_H

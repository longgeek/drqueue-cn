/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_METASL_STDLIB_H
#define MI_METASL_STDLIB_H 1

#include "math.h"

// almost all MetaSL stdlib functions come from mi::math, only a few additions
// are necessary to be made here.

namespace MI {
namespace SHADER {

using MATH::operator==;
using MATH::operator!=;
using MATH::operator<;
using MATH::operator>;
using MATH::operator<=;
using MATH::operator>=;

using MATH::normalize;
using MATH::min;
using MATH::max;

// MetaSL stdlib Math functions

using mi::math::abs;
using mi::math::acos;
using mi::math::all;
using mi::math::any;
using mi::math::asin;
using mi::math::atan;
using mi::math::atan2;
using mi::math::ceil;
using mi::math::clamp;
using mi::math::cos;
using mi::math::degrees;
using mi::math::exp;
using mi::math::exp2;
using mi::math::floor;
using mi::math::fmod;
using mi::math::frac;
using mi::math::lerp;
using mi::math::log;
using mi::math::log2;
using mi::math::log10;
//using mi::math::max; // missing elementwise max on Vector/Color
//using mi::math::min; // missing elementwise min on Vector/Color
using mi::math::modf;
using mi::math::pow;
using mi::math::radians;
using mi::math::round;
using mi::math::rsqrt;
using mi::math::saturate;
using mi::math::sign;
using mi::math::sin;
using mi::math::sincos;
using mi::math::smoothstep;
using mi::math::sqrt;
using mi::math::step;
using mi::math::tan;
using mi::math::transpose;

// MetaSL stdlib Geometric functions

using mi::math::cross;
// using mi::math::distance; // named euclidean_distance in mi::math
using mi::math::dot;
// using mi::math::faceforward; // too specific for mi::math, defined here
using mi::math::length;
// using mi::math::reflect; // too specific for mi::math, defined here
// using mi::math::refract; // too specific for mi::math, defined here

// Missing definitions

// Returns the Euclidean distance of the scalar \p a from \p b.
inline Float32 distance( Float32 a, Float32 b) { return abs(a-b); }
// Returns the Euclidean distance of the scalar \p a from \p b.
inline Float64 distance( Float64 a, Float64 b) { return abs(a-b); }

// Returns the Euclidean distance of the vector \p a from \p b.
template <typename T, Size DIM>
inline T distance( const mi::math::Vector<T,DIM>& a, const mi::math::Vector<T,DIM>& b)
{
    return length(a - b);
}

// Returns the Euclidean distance of the color \p a from \p b.
inline Float32 distance( const mi::math::Color& a, const mi::math::Color& b)
{
    return length(a - b);
}

// Compute faceforward function.
template <typename T, typename V>
inline T faceforward( const T& n, const V& i, const V& ng)
{
    return (dot(i,ng) < typename V::value_type(0)) ? n : -n;
}

// Compute reflected direction.
template <typename T>
inline mi::math::Vector<T,3> reflect(
    const mi::math::Vector<T,3>& i,         // Incoming direction.
    const mi::math::Vector<T,3>& n)         // Surface normal.
{
    return i - T(2) * dot(i,n) * n;
}

// Compute refracted direction.
template <typename T>
inline mi::math::Vector<T,3> refract(
    const mi::math::Vector<T,3>& i,         // Incoming direction.
    const mi::math::Vector<T,3>& n,         // Surface normal.
    T eta)                                  // The index of refraction.
{
    const T in = dot(i,n);
    const T discr = T(1) - eta * eta * (T(1) - in * in);
    if (discr < T(0)) // return zero vector for total internal reflection
        return mi::math::Vector<T,3>(T(0));
    const T mu = eta * in + sqrt(discr);
    return eta * i - mu * n;
}


} // namespace MI
} // namespace SHADER


#endif

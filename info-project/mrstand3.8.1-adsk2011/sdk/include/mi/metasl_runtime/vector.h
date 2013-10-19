//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/metasl_runtime/vector.h
///
//*****************************************************************************

#ifndef MI_METASL_RUNTIME_VECTOR_H
#define MI_METASL_RUNTIME_VECTOR_H

#include <mi/math/vector.h>
#include <mi/metasl_runtime/mi_types.h>
#include <mi/metasl_runtime/function.h>

namespace MI {
namespace MATH {

using mi::math::Vector;


// Equality comparison.
template <typename T, mi::Size DIM>
inline Vector<bool, DIM> operator==(
    const Vector<T, DIM>        &lhs,   // left vector
    const Vector<T, DIM>        &rhs)   // right vector
{
    Vector<bool,DIM> result;
    mi::math::general::transform(lhs,rhs,result,mi::math::functor::Operator_equal_equal());
    return result;
}

// Not equal.
template <typename T1, typename T2, mi::Size DIM>
inline Vector<bool, DIM> operator!=(
    const Vector<T1, DIM>        &lhs,   // left vector
    const Vector<T2, DIM>        &rhs)   // right vector
{
    Vector<bool,DIM> result;
    mi::math::general::transform(lhs,rhs,result,mi::math::functor::Operator_not_equal());
    return result;
}

// Less than.
template <typename T1, typename T2, mi::Size DIM>
inline Vector<bool, DIM> operator<(
    const Vector<T1, DIM>        &lhs,   // left vector
    const Vector<T2, DIM>        &rhs)   // right vector
{
    Vector<bool,DIM> result;
    mi::math::general::transform(lhs,rhs,result,mi::math::functor::Operator_less());
    return result;
}

// Greater than.
template <typename T1, typename T2, mi::Size DIM>
inline Vector<bool, DIM> operator>(
    const Vector<T1, DIM>        &lhs,   // left vector
    const Vector<T2, DIM>        &rhs)   // right vector
{
    Vector<bool,DIM> result;
    mi::math::general::transform(lhs,rhs,result,mi::math::functor::Operator_greater());
    return result;
}

// Less equal.
template <typename T1, typename T2, mi::Size DIM>
inline Vector<bool, DIM> operator<=(
    const Vector<T1, DIM>        &lhs,   // left vector
    const Vector<T2, DIM>        &rhs)   // right vector
{
    Vector<bool,DIM> result;
    mi::math::general::transform(lhs,rhs,result,mi::math::functor::Operator_less_equal());
    return result;
}

// Greater equal.
template <typename T1, typename T2, mi::Size DIM>
inline Vector<bool, DIM> operator>=(
    const Vector<T1, DIM>        &lhs,   // left vector
    const Vector<T2, DIM>        &rhs)   // right vector
{
    Vector<bool,DIM> result;
    mi::math::general::transform(lhs,rhs,result,mi::math::functor::Operator_greater_equal());
    return result;
}


/// Adds \p rhs elementwise to \p lhs and returns the modified \p lhs.
template <typename T, mi::Size DIM, typename TT>
inline Vector<T,DIM> & operator+= (
    Vector<T,DIM> & lhs,  // left hand-side vector
    TT rhs)               // right hand-side scalar
{
    for (mi::Size i(0u); i < DIM; ++i)
        lhs[i] += T(rhs);
    return lhs;
}

/// Subtracts \p rhs elementwise from \p lhs and returns the modified \p lhs.
template <typename T, mi::Size DIM, typename TT>
inline Vector<T,DIM> & operator-= (
    Vector<T,DIM> & lhs,  // left hand-side vector
    TT rhs)               // right hand-side scalar
{
    for (mi::Size i(0u); i < DIM; ++i)
        lhs[i] -= T(rhs);
    return lhs;
}

/// Adds \p lhs and \p rhs elementwise and returns the new result.
template <typename T, mi::Size DIM, typename TT>
inline Vector<T,DIM> operator+ (
    const Vector<T,DIM> & lhs,  // left  hand-side vector
    TT rhs)                     // right hand-side scalar
{
    Vector<T,DIM> tmp(lhs);
    return tmp += T(rhs);
}

/// Adds \p lhs and \p rhs elementwise and returns the new result.
template <typename TT, typename T, mi::Size DIM>
inline Vector<T,DIM> operator+ (
    TT lhs,                     // left  hand-side scalar
    const Vector<T,DIM> & rhs)  // right hand-side vector
{
    Vector<T,DIM> tmp(rhs);
    return tmp += T(lhs);
}

/// Subtracts \p rhs elementwise from \p lhs and returns the new result.
template <typename T, mi::Size DIM, typename TT>
inline Vector<T,DIM> operator- (
    const Vector<T,DIM> & lhs,  // left hand-side vector
    TT rhs)                     // right hand-side scalar
{
    Vector<T,DIM> tmp(lhs);
    return tmp -= T(rhs);
}

/// Subtracts \p rhs elementwise from \p lhs and returns the new result.
template <typename TT, typename T, mi::Size DIM>
inline Vector<T,DIM> operator- (
    TT lhs,                     // left hand-side scalar
    const Vector<T,DIM> & rhs)  // right hand-side vector
{
    Vector<T,DIM> tmp((T(lhs)));
    tmp -= rhs;
    return tmp;
}

/// Multiply \p lhs and \p rhs elementwise and returns the new result.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> operator* (
    T lhs,                      // left  hand-side scalar
    const Vector<T,DIM> & rhs)  // right hand-side vector
{
    Vector<T,DIM> tmp(lhs);
    return tmp *= rhs;
}

/// Divide \p lhs and \p rhs elementwise and returns the new result.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> operator/ (
    T lhs,                      // left  hand-side scalar
    const Vector<T,DIM> & rhs)  // right hand-side vector
{
    Vector<T,DIM> tmp(lhs);
    return tmp /= rhs;
}

/// elementwise modulo
template <mi::Size DIM>
inline Vector<int,DIM> operator% (
    int lhs,                      // left  hand-side scalar
    const Vector<int,DIM> & rhs)  // right hand-side vector
{
    Vector<int,DIM> tmp(lhs);
    return tmp %= rhs;
}

/// elementwise modulo
template <mi::Size DIM>
inline Vector<int,DIM> operator% (
    Vector<int,DIM> lhs,          // left  hand-side vector
    int rhs)                      // right hand-side scalar
{
    Vector<int,DIM> tmp(rhs);
    return lhs %= tmp;
}

/// Postincrement \p arg componentwise.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> operator++ (
    Vector<T,DIM> & arg,    // argument vector
    int)                    // dumy argument to indicate postfix operator
{
    Vector<T,DIM> tmp(arg);
    for(mi::Size i = 0; i < DIM; i++)
        arg[i]++;
    return tmp;
}

/// Postdecrement \p arg componentwise.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> operator-- (
    Vector<T,DIM> & arg,    // argument vector
    int)                    // dumy argument to indicate postfix operator
{
    Vector<T,DIM> tmp(arg);
    for(mi::Size i = 0; i < DIM; i++)
        arg[i]--;
    return tmp;
}

// Convenient typedefs for bool, int, float, and double vectors.
typedef Vector<bool,    2>      Vector2b;
typedef Vector<int,     2>      Vector2i;
typedef Vector<Float32, 2>      Vector2;
typedef Vector<Float64, 2>      Dvector2;
typedef Vector<bool,    3>      Vector3b;
typedef Vector<int,     3>      Vector3i;
typedef Vector<Float32, 3>      Vector3;
typedef Vector<Float64, 3>      Dvector3;
typedef Vector<bool,    4>      Vector4b;
typedef Vector<int,     4>      Vector4i;
typedef Vector<Float32, 4>      Vector4;
typedef Vector<Float64, 4>      Dvector4;

// Geometry vector types linked to Scalar type.
typedef Vector2 Vector2;
typedef Vector3 Vector3;
typedef Vector4 Vector4;

// Is finite.
template <typename T, mi::Size DIM>
inline Vector<bool,DIM> isfinite( const Vector<T,DIM>& v)
{
    Vector<bool,DIM> result;
    for (mi::Size i = 0; i != DIM; ++i)
        result[i] = isfinite(v[i]);
    return result;
}

// Is NaN.
template <typename T, mi::Size DIM>
inline Vector<bool,DIM> isnan MI_PREVENT_MACRO_EXPAND ( const Vector<T,DIM>& v)
{
    Vector<bool,DIM> result;
    for (mi::Size i = 0; i != DIM; ++i)
        result[i] = isnan(v[i]);
    return result;
}

/// Normalizes vector \p c to unit length, iff \p c != 0.
/// Otherwise the parameter is returned unmodified.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> normalize(
    const Vector<T,DIM> & v)   // vector
{
    Vector<T,DIM> result_vec(v);
    const T rec_length = T(1) / length(result_vec);
    const bool result = isfinite(rec_length);
    if (result)
        result_vec *= rec_length;
    return result_vec;
}

/// Returns elementwise maximum of two vectors.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> max (
        const Vector<T,DIM> &   lhs,    // left hand-side vector
        const Vector<T,DIM> &   rhs)    // right hand-side vector
{
    return mi::math::elementwise_max(lhs, rhs);
}

/// Returns elementwise minimum of two vectors.
template <typename T, mi::Size DIM>
inline Vector<T,DIM> min (
        const Vector<T,DIM> &   lhs,    // left hand-side vector
        const Vector<T,DIM> &   rhs)    // right hand-side vector
{
    return mi::math::elementwise_min(lhs, rhs);
}


// mixed scalar/vector operators

#define MI_SCAL_VEC_OP(op) \
template <typename T, mi::Size DIM>     \
inline Vector<bool,DIM> operator op (   \
        const Vector<T,DIM>&     lhs,   \
        T                        rhs)   \
{                                       \
    Vector<bool,DIM> r;                 \
    for (mi::Size i=0; i<DIM; ++i)      \
        r[i] = (lhs[i] op rhs);         \
    return r;                           \
}                                       \
                                        \
template <typename T, mi::Size DIM>     \
inline Vector<bool,DIM> operator op (   \
        T                        lhs,   \
        const Vector<T,DIM>&     rhs)   \
{                                       \
    Vector<bool,DIM> r;                 \
    for (mi::Size i=0; i<DIM; ++i)      \
        r[i] = (lhs op rhs[i]);         \
    return r;                           \
}


MI_SCAL_VEC_OP(==);
MI_SCAL_VEC_OP(!=);
MI_SCAL_VEC_OP(>=);
MI_SCAL_VEC_OP(<=);
MI_SCAL_VEC_OP(>);
MI_SCAL_VEC_OP(<);


#undef MI_SCAL_VEC_OP



} // namespace MATH
} // namespace MI

#endif // MI_METASL_RUNTIME_VECTOR_H

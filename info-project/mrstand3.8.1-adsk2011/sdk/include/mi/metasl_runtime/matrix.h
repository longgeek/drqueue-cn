//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/metasl_runtime/matrix.h
///
//*****************************************************************************

#ifndef MI_METASL_RUNTIME_MATRIX_H
#define MI_METASL_RUNTIME_MATRIX_H

#include <mi/math/matrix.h>
#include <mi/metasl_runtime/function.h>
#include <mi/metasl_runtime/vector.h>

namespace MI {
namespace MATH {

// Convenient typedefs.
typedef mi::math::Matrix<Float32,2,2>  Matrix2x2f;
typedef mi::math::Matrix<Float32,3,2>  Matrix3x2f;
typedef mi::math::Matrix<Float32,4,2>  Matrix4x2f;
typedef mi::math::Matrix<Float32,2,3>  Matrix2x3f;
typedef mi::math::Matrix<Float32,3,3>  Matrix3x3f;
typedef mi::math::Matrix<Float32,4,3>  Matrix4x3f;
typedef mi::math::Matrix<Float32,2,4>  Matrix2x4f;
typedef mi::math::Matrix<Float32,3,4>  Matrix3x4f;
typedef mi::math::Matrix<Float32,4,4>  Matrix4x4f;

typedef mi::math::Matrix<Float64,2,2>  Matrix2x2d;
typedef mi::math::Matrix<Float64,3,2>  Matrix3x2d;
typedef mi::math::Matrix<Float64,4,2>  Matrix4x2d;
typedef mi::math::Matrix<Float64,2,3>  Matrix2x3d;
typedef mi::math::Matrix<Float64,3,3>  Matrix3x3d;
typedef mi::math::Matrix<Float64,4,3>  Matrix4x3d;
typedef mi::math::Matrix<Float64,2,4>  Matrix2x4d;
typedef mi::math::Matrix<Float64,3,4>  Matrix3x4d;
typedef mi::math::Matrix<Float64,4,4>  Matrix4x4d;

using mi::math::sub_matrix;

/// Returns the upper-left sub-matrix of size \c NEW_ROW times \c NEW_COL.
/// Precondition: \c NEW_ROW <= \c ROW and \c NEW_COL <= \c COL.
///
/// In addition to mi::math::sub_matrix, this function allows type conversion.
template <typename NEW_T, Size NEW_ROW, Size NEW_COL, typename T, Size ROW, Size COL>
inline mi::math::Matrix<NEW_T,NEW_ROW,NEW_COL> sub_matrix(
    const mi::math::Matrix<T,ROW,COL>& mat) // original matrix
{
    mi_static_assert( NEW_ROW<=ROW);
    mi_static_assert( NEW_COL<=COL);
    mi::math::Matrix<NEW_T,NEW_ROW,NEW_COL> result;
    for (Size i=0; i < NEW_ROW; ++i) {
        for (Size j=0; j < NEW_COL; ++j) {
            result(i,j) = NEW_T(mat(i,j));
        }
    }
    return result;
}


// Combined multiplication and assignment on vector and square matrix.
template <typename T, Size D>
inline mi::math::Vector<T,D>& operator*=(
        mi::math::Vector<T,D>& v,
        const mi::math::Matrix<T,D,D>& m)
{
    mi::math::Vector<T,D> result = v * m;
    return v = result;
}


// Overloads of +=, -=, +, and - operators
// for combined matrix/scalar arithmetic.

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> &operator+=(mi::math::Matrix<T,ROW,COL> &m,T f)
{
    for(Size i = 0; i < ROW; i++)
        for(Size k = 0; k < COL; k++)
            m[i][k] += f;
    return m;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> &operator-=(mi::math::Matrix<T,ROW,COL> &m,T f)
{
    for(Size i = 0; i < ROW; i++)
        for(Size k = 0; k < COL; k++)
            m[i][k] -= f;
    return m;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> operator+(const mi::math::Matrix<T,ROW,COL> &m,T f)
{
    mi::math::Matrix<T,ROW,COL> result = m;

    result += f;
    return result;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> operator+(T f,const mi::math::Matrix<T,ROW,COL> &m)
{
    mi::math::Matrix<T,ROW,COL> result = m;

    result += f;
    return result;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> operator-(const mi::math::Matrix<T,ROW,COL> &m,T f)
{
    mi::math::Matrix<T,ROW,COL> result = m;

    result += f;
    return result;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> operator-(T f,const mi::math::Matrix<T,ROW,COL> &m)
{
    mi::math::Matrix<T,ROW,COL> result = m;

    result += f;
    return result;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> &operator/=(mi::math::Matrix<T,ROW,COL> &m,T f)
{
    for(Size i = 0; i < ROW; i++)
        for(Size k = 0; k < COL; k++)
            m[i][k] /= f;
    return m;
}

template <typename T, Size ROW, Size COL>
inline mi::math::Matrix<T,ROW,COL> operator/(const mi::math::Matrix<T,ROW,COL> &m,T f)
{
    mi::math::Matrix<T,ROW,COL> result = m;

    result /= f;
    return result;
}


} // namespace MATH
} // namespace MI


#endif // MI_METASL_RUNTIME_MATRIX_H

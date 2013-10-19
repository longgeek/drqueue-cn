/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/


#ifndef MI_SHADER_TYPECONV_H
#define MI_SHADER_TYPECONV_H

#ifdef MI_RAY
// request MetaSL support
#define MI_METASL_HEADERS
#include <shader.h>
#endif

#include "mi_shader_types.h"
#include "math.h"
#include "tag_wrapper.h"


namespace MI {
namespace SHADER {


/* type conversion to mental ray 3.x API */

inline miTag to_ray3_type(SHADER::Tag t)
{
    return miTag(t);
}

inline miBoolean to_ray3_type(bool b)
{
    return b ? miTRUE : miFALSE;
}

inline miInteger to_ray3_type(int i)
{
    return i;
}

inline miScalar to_ray3_type(float f)
{
    return f;
}

inline miScalar to_ray3_type(double d)
{
    return miScalar(d);
}

inline miVector to_ray3_type(const MATH::Vector2& v)
{
    const miVector r = { v.x, v.y, 0.f };
    return r;
}

inline miVector to_ray3_type(const MATH::Dvector2& v)
{
    const miVector r = { float(v.x), float(v.y), 0.f };
    return r;
}

inline miVector to_ray3_type(const MATH::Vector2b& v)
{
    const miVector r = { v.x?1.f:0.f, v.y?1.f:0.f, 0.f };
    return r;
}

inline miVector to_ray3_type(const MATH::Vector2i& v)
{
    const miVector r = { v.x, v.y, 0.f };
    return r;
}

inline const miVector& to_ray3_type(const MATH::Vector3& v)
{
    return reinterpret_cast<const miVector&>(v);
}

inline miVector to_ray3_type(const MATH::Vector3b& v)
{
    const miVector r = { v.x?1.f:0.f, v.y?1.f:0.f, v.z?1.f:0.f };
    return r;
}

inline miVector to_ray3_type(const MATH::Dvector3& v)
{
    const miVector r = { float(v.x), float(v.y), float(v.z) };
    return r;
}

inline miVector to_ray3_type(const MATH::Vector3i& v)
{
    const miVector r = { v.x, v.y, v.z };
    return r;
}

inline const miColor& to_ray3_type(const MATH::Vector4& v)
{
    return reinterpret_cast<const miColor&>(v);
}

inline miColor to_ray3_type(const MATH::Dvector4& v)
{
    const miColor r = { float(v.x), float(v.y), float(v.z), float(v.w) };
    return r;
}

inline miColor to_ray3_type(const MATH::Vector4b& v)
{
    const miColor r = { v.x?1.f:0.f, v.y?1.f:0.f, v.z?1.f:0.f, v.w?1.f:0.f };
    return r;
}

inline miColor to_ray3_type(const MATH::Vector4i& v)
{
    const miColor r = { v.x, v.y, v.z, v.w };
    return r;
}

inline const miColor& to_ray3_type(const COLOR::Color_struct& c)
{
    return reinterpret_cast<const miColor&>(c);
}

inline miColor to_ray3_type(const COLOR::Spectrum_struct& s)
{
    const miColor r = { s.c[0], s.c[1], s.c[2], 1.f };
    return r;
}

template <typename RT, typename ST>
inline void to_ray3_type(RT& res, const ST& src)
{
    res = to_ray3_type(src);
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,2,2>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]= 0.f; r[ 3]= 0.f;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]= 0.f; r[ 7]= 0.f;
    r[ 8]= 0.f; r[ 9]= 0.f; r[10]= 0.f; r[11]= 0.f;
    r[12]= 0.f; r[13]= 0.f; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,3,2>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]= 0.f; r[ 3]= 0.f;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]= 0.f; r[ 7]= 0.f;
    r[ 8]=m.zx; r[ 9]=m.zy; r[10]= 0.f; r[11]= 0.f;
    r[12]= 0.f; r[13]= 0.f; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,4,2>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]= 0.f; r[ 3]= 0.f;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]= 0.f; r[ 7]= 0.f;
    r[ 8]=m.zx; r[ 9]=m.zy; r[10]= 0.f; r[11]= 0.f;
    r[12]=m.wx; r[13]=m.wy; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,2,3>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]=m.xz; r[ 3]= 0.f;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]=m.yz; r[ 7]= 0.f;
    r[ 8]= 0.f; r[ 9]= 0.f; r[10]= 0.f; r[11]= 0.f;
    r[12]= 0.f; r[13]= 0.f; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,3,3>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]=m.xz; r[ 3]= 0.f;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]=m.yz; r[ 7]= 0.f;
    r[ 8]=m.zx; r[ 9]=m.zy; r[10]=m.zz; r[11]= 0.f;
    r[12]= 0.f; r[13]= 0.f; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,4,3>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]=m.xz; r[ 3]= 0.f;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]=m.yz; r[ 7]= 0.f;
    r[ 8]=m.zx; r[ 9]=m.zy; r[10]=m.zz; r[11]= 0.f;
    r[12]=m.wx; r[13]=m.wy; r[14]=m.wz; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,2,4>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]=m.xz; r[ 3]=m.xw;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]=m.yz; r[ 7]=m.yw;
    r[ 8]= 0.f; r[ 9]= 0.f; r[10]= 0.f; r[11]= 0.f;
    r[12]= 0.f; r[13]= 0.f; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,3,4>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]=m.xz; r[ 3]=m.xw;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]=m.yz; r[ 7]=m.yw;
    r[ 8]=m.zx; r[ 9]=m.zy; r[10]=m.zz; r[11]=m.zw;
    r[12]= 0.f; r[13]= 0.f; r[14]= 0.f; r[15]= 0.f;
}

template <typename T>
inline void to_ray3_type(miMatrix& r, const mi::math::Matrix<T,4,4>& m)
{
    r[ 0]=m.xx; r[ 1]=m.xy; r[ 2]=m.xz; r[ 3]=m.xw;
    r[ 4]=m.yx; r[ 5]=m.yy; r[ 6]=m.yz; r[ 7]=m.yw;
    r[ 8]=m.zx; r[ 9]=m.zy; r[10]=m.zz; r[11]=m.zw;
    r[12]=m.wx; r[13]=m.wy; r[14]=m.wz; r[15]=m.ww;
}


/* type conversion from mental ray 3.x API */

inline void from_ray3_type(SHADER::Tag& r, const miTag t)
{
    r = SHADER::Tag(t);
}

template <typename T>
inline void from_ray3_type(Tag_wrapper<T>& r, const miTag t)
{
    r = Tag_wrapper<T>(t);
}

// enums
template <typename T>
inline void from_ray3_type(T& r, const int i)
{
    r = T(i);
}

inline void from_ray3_type(bool& r, const miBoolean b)
{
    r = (miFALSE != b);
}

inline void from_ray3_type(int& r, const miInteger i)
{
    r = i;
}

inline void from_ray3_type(float& r, const miScalar f)
{
    r = f;
}

inline void from_ray3_type(double& r, const miScalar f)
{
    r = f;
}

inline void from_ray3_type(MATH::Vector2b& r, const miVector& v)
{
    r[0] = (v.x != 0.f); r[1] = (v.y != 0.f);
}

inline void from_ray3_type(MATH::Vector3b& r, const miVector& v)
{
    r[0] = (v.x != 0.f); r[1] = (v.y != 0.f); r[2] = (v.z != 0.f);
}

inline void from_ray3_type(MATH::Vector4b& r, const miColor& v)
{
    r[0] = (v.r != 0.f); r[1] = (v.g != 0.f); r[2] = (v.b != 0.f); r[3] = (v.a != 0.f);
}

template <typename T>
inline void from_ray3_type(MATH::Vector<T,2>& r, const miVector& v)
{
    r[0] = T(v.x); r[1] = T(v.y);
}

template <typename T>
inline void from_ray3_type(MATH::Vector<T,3>& r, const miVector& v)
{
    r[0] = T(v.x); r[1] = T(v.y); r[2] = T(v.z);
}

template <typename T>
inline void from_ray3_type(MATH::Vector<T,4>& r, const miColor& v)
{
    r[0] = T(v.r); r[1] = T(v.g); r[2] = T(v.b); r[3] = T(v.a);
}

inline void from_ray3_type(COLOR::Color_struct& r, const miColor& c)
{
    r = reinterpret_cast<const COLOR::Color_struct&>(c);
}

inline void from_ray3_type(COLOR::Color& r, const miColor& c)
{
    r = reinterpret_cast<const COLOR::Color_struct&>(c);
}

inline void from_ray3_type(COLOR::Spectrum& r, const miColor& s)
{
    r[0] = s.r; r[1] = s.g; r[2] = s.b;
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,2,2>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,2,2>::Row_vector V;
    r = mi::math::Matrix<T,2,2>(
            V(m[ 0],m[ 1]),
            V(m[ 4],m[ 5]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,3,2>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,3,2>::Row_vector V;
    r = mi::math::Matrix<T,3,2>(
            V(m[ 0],m[ 1]),
            V(m[ 4],m[ 5]),
            V(m[ 8],m[ 9]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,4,2>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,4,2>::Row_vector V;
    r = mi::math::Matrix<T,4,2>(
            V(m[ 0],m[ 1]),
            V(m[ 4],m[ 5]),
            V(m[ 8],m[ 9]),
            V(m[12],m[13]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,2,3>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,2,3>::Row_vector V;
    r = mi::math::Matrix<T,2,3>(
            V(m[ 0],m[ 1],m[ 2]),
            V(m[ 4],m[ 5],m[ 6]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,3,3>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,3,3>::Row_vector V;
    r = mi::math::Matrix<T,3,3>(
            V(m[ 0],m[ 1],m[ 2]),
            V(m[ 4],m[ 5],m[ 6]),
            V(m[ 8],m[ 9],m[10]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,4,3>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,4,3>::Row_vector V;
    r = mi::math::Matrix<T,4,3>(
            V(m[ 0],m[ 1],m[ 2]),
            V(m[ 4],m[ 5],m[ 6]),
            V(m[ 8],m[ 9],m[10]),
            V(m[12],m[13],m[14]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,2,4>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,2,4>::Row_vector V;
    r = mi::math::Matrix<T,2,4>(
            V(m[ 0],m[ 1],m[ 2],m[ 3]),
            V(m[ 4],m[ 5],m[ 6],m[ 7]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,3,4>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,3,4>::Row_vector V;
    r = mi::math::Matrix<T,3,4>(
            V(m[ 0],m[ 1],m[ 2],m[ 3]),
            V(m[ 4],m[ 5],m[ 6],m[ 7]),
            V(m[ 8],m[ 9],m[10],m[11]));
}

template <typename T>
inline void from_ray3_type(mi::math::Matrix<T,4,4>& r, const miMatrix& m)
{
    typedef typename mi::math::Matrix<T,4,4>::Row_vector V;
    r = mi::math::Matrix<T,4,4>(
            V(m[ 0],m[ 1],m[ 2],m[ 3]),
            V(m[ 4],m[ 5],m[ 6],m[ 7]),
            V(m[ 8],m[ 9],m[10],m[11]),
            V(m[12],m[13],m[14],m[15]));
}

#if 0
template <typename TR, typename TS>
inline TR from_ray3_type(const TS& src)
{
    TR res;
    from_ray3_type(res,src);
    return res;
}
#endif

}}

#endif //MI_SHADER_TYPECONV_H

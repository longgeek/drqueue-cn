//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/metasl_runtime/spectrum.h
///
//*****************************************************************************

#ifndef MI_METASL_RUNTIME_SPECTRUM_H
#define MI_METASL_RUNTIME_SPECTRUM_H

#include <mi/math/spectrum.h>
#include <mi/metasl_runtime/function.h>
#include <mi/metasl_runtime/vector.h>
#include <mi/metasl_runtime/color.h>

namespace MI {
namespace COLOR {

using mi::math::Color_struct;
using mi::math::Color;
using mi::math::Spectrum_struct;
using mi::math::Spectrum;

/// Returns elementwise maximum of two spectra.
inline Spectrum max MI_PREVENT_MACRO_EXPAND ( const Spectrum& lhs, const Spectrum& rhs)
{
    mi_math_assert_msg(lhs.size() == 3, "precondition");
    mi_math_assert_msg(rhs.size() == 3, "precondition");
    return Spectrum(
            mi::math::max MI_PREVENT_MACRO_EXPAND ( lhs[0], rhs[0]),
            mi::math::max MI_PREVENT_MACRO_EXPAND ( lhs[1], rhs[1]),
            mi::math::max MI_PREVENT_MACRO_EXPAND ( lhs[2], rhs[2]));
}

/// Returns elementwise minimum of two spectra.
inline Spectrum min MI_PREVENT_MACRO_EXPAND ( const Spectrum& lhs, const Spectrum& rhs)
{
    mi_math_assert_msg(lhs.size() == 3, "precondition");
    mi_math_assert_msg(rhs.size() == 3, "precondition");
    return Spectrum(
            mi::math::min MI_PREVENT_MACRO_EXPAND ( lhs[0], rhs[0]),
            mi::math::min MI_PREVENT_MACRO_EXPAND ( lhs[1], rhs[1]),
            mi::math::min MI_PREVENT_MACRO_EXPAND ( lhs[2], rhs[2]));
}

/// Add Spectrum to Color.
inline Spectrum operator+(const Spectrum &s,const Color_struct &c)
{
    return Spectrum(s[0] + c.r,s[1] + c.g,s[2] + c.b);
}

/// Add Spectrum to Vector3.
inline Spectrum operator+(const Spectrum &s,const MATH::Vector3 &v)
{
    return Spectrum(s[0] + v[0],s[1] + v[1],s[2] + v[2]);
}

/// Add Spectrum to Vector4.
inline Spectrum operator+(const Spectrum &s,const MATH::Vector4 &v)
{
    return Spectrum(s[0] + v[0],s[1] + v[1],s[2] + v[2]);
}

/// Add Color to Spectrum.
inline Spectrum operator+(const Color_struct &c,const Spectrum &s)
{
    return Spectrum(c.r + s[0],c.g + s[1],c.b + s[2]);
}

/// Add Vector3 to Spectrum.
inline Spectrum operator+(const MATH::Vector3 &v,const Spectrum &s)
{
    return Spectrum(v[0] + s[0],v[1] + s[1],v[2] + s[2]);
}

/// Add Vector4 to Spectrum.
inline Spectrum operator+(const MATH::Vector4 &v,const Spectrum &s)
{
    return Spectrum(v[0] + s[0],v[1] + s[1],v[2] + s[2]);
}

/// Subtract Color from Spectrum.
inline Spectrum operator-(const Spectrum &s,const Color_struct &c)
{
    return Spectrum(s[0] - c.r,s[1] - c.g,s[2] - c.b);
}

/// Subtract Vector3 from Spectrum.
inline Spectrum operator-(const Spectrum &s,const MATH::Vector3 &v)
{
    return Spectrum(s[0] - v[0],s[1] - v[1],s[2] - v[2]);
}

/// Subtract Vector4 from Spectrum.
inline Spectrum operator-(const Spectrum &s,const MATH::Vector4 &v)
{
    return Spectrum(s[0] - v[0],s[1] - v[1],s[2] - v[2]);
}

/// Subtract spectrum from Color.
inline Spectrum operator-(const Color_struct &c,const Spectrum &s)
{
    return Spectrum(c.r - s[0],c.g - s[1],c.b - s[2]);
}

/// Subtract spectrum from Vector3.
inline Spectrum operator-(const MATH::Vector3 &v,const Spectrum &s)
{
    return Spectrum(v[0] - s[0],v[1] - s[1],v[2] - s[2]);
}

/// Subtract spectrum from Vector4.
inline Spectrum operator-(const MATH::Vector4 &v,const Spectrum &s)
{
    return Spectrum(v[0] - s[0],v[1] - s[1],v[2] - s[2]);
}

/// Multiply Spectrum with Color.
inline Spectrum operator*(const Spectrum &s,const Color_struct &c)
{
    return Spectrum(s[0] * c.r,s[1] * c.g,s[2] * c.b);
}

/// Multiply Spectrum with Vector3.
inline Spectrum operator*(const Spectrum &s,const MATH::Vector3 &v)
{
    return Spectrum(s[0] * v[0],s[1] * v[1],s[2] * v[2]);
}

/// Multiply Spectrum with Vector4.
inline Spectrum operator*(const Spectrum &s,const MATH::Vector4 &v)
{
    return Spectrum(s[0] * v[0],s[1] * v[1],s[2] * v[2]);
}

/// Multiply Color with Spectrum.
inline Spectrum operator*(const Color_struct &c,const Spectrum &s)
{
    return Spectrum(c.r * s[0],c.g * s[1],c.b * s[2]);
}

/// Multiply Vector3 with Spectrum.
inline Spectrum operator*(const MATH::Vector3 &v,const Spectrum &s)
{
    return Spectrum(v[0] * s[0],v[1] * s[1],v[2] * s[2]);
}

/// Multiply Vector4 with Spectrum.
inline Spectrum operator*(const MATH::Vector4 &v,const Spectrum &s)
{
    return Spectrum(v[0] * s[0],v[1] * s[1],v[2] * s[2]);
}

/// Divide Spectrum by Color.
inline Spectrum operator/(const Spectrum &s,const Color_struct &c)
{
    return Spectrum(s[0] / c.r,s[1] / c.g,s[2] / c.b);
}

/// Divide Spectrum by Vector3.
inline Spectrum operator/(const Spectrum &s,const MATH::Vector3 &v)
{
    return Spectrum(s[0] / v[0],s[1] / v[1],s[2] / v[2]);
}

/// Divide Spectrum by Vector4.
inline Spectrum operator/(const Spectrum &s,const MATH::Vector4 &v)
{
    return Spectrum(s[0] / v[0],s[1] / v[1],s[2] / v[2]);
}

/// Divide Color by Spectrum.
inline Spectrum operator/(const Color_struct &c,const Spectrum &s)
{
    return Spectrum(c.r / s[0],c.g / s[1],c.b / s[2]);
}

/// Divide Vector3 by Spectrum.
inline Spectrum operator/(const MATH::Vector3 &v,const Spectrum &s)
{
    return Spectrum(v[0] / s[0],v[1] / s[1],v[2] / s[2]);
}

/// Divide Vector4 by Spectrum.
inline Spectrum operator/(const MATH::Vector4 &v,const Spectrum &s)
{
    return Spectrum(v[0] / s[0],v[1] / s[1],v[2] / s[2]);
}

/// += on Spectrum and Color.
inline Spectrum &operator+=(Spectrum &s,const Color_struct &c)
{
    return s = s + c;
}

/// += on Spectrum and Vector3.
inline Spectrum &operator+=(Spectrum &s,const MATH::Vector3 &v)
{
    return s = s + v;
}

/// += on Spectrum and Vector4.
inline Spectrum &operator+=(Spectrum &s,const MATH::Vector4 &v)
{
    return s = s + v;
}

/// += on Color and Spectrum.
inline Color &operator+=(Color &c,const Spectrum &s)
{
    return c = Color((c + s).to_vector4());
}

/// += on Vector3 and Spectrum.
inline MATH::Vector3 &operator+=(MATH::Vector3 &v,const Spectrum &s)
{
    return v = (v + s).to_vector3();
}

/// += on Vector4 and Spectrum.
inline MATH::Vector4 &operator+=(MATH::Vector4 &v,const Spectrum &s)
{
    return v = (v + s).to_vector4();
}

/// -= on Spectrum and Color.
inline Spectrum &operator-=(Spectrum &s,const Color_struct &c)
{
    return s = s - c;
}

/// -= on Spectrum and Vector3.
inline Spectrum &operator-=(Spectrum &s,const MATH::Vector3 &v)
{
    return s = s - v;
}

/// -= on Spectrum and Vector4.
inline Spectrum &operator-=(Spectrum &s,const MATH::Vector4 &v)
{
    return s = s - v;
}

/// -= on Color and Spectrum.
inline Color &operator-=(Color &c,const Spectrum &s)
{
    return c = Color((c - s).to_vector4());
}

/// -= on Vector3 and Spectrum.
inline MATH::Vector3 &operator-=(MATH::Vector3 &v,const Spectrum &s)
{
    return v = (v - s).to_vector3();
}

/// -= on Vector4 and Spectrum.
inline MATH::Vector4 &operator-=(MATH::Vector4 &v,const Spectrum &s)
{
    return v = (v - s).to_vector4();
}

/// *= on Spectrum and Color.
inline Spectrum &operator*=(Spectrum &s,const Color_struct &c)
{
    return s = s * c;
}

/// *= on Spectrum and Vector3.
inline Spectrum &operator*=(Spectrum &s,const MATH::Vector3 &v)
{
    return s = s * v;
}

/// *= on Spectrum and Vector4.
inline Spectrum &operator*=(Spectrum &s,const MATH::Vector4 &v)
{
    return s = s * v;
}

/// *= on Color and Spectrum.
inline Color &operator*=(Color &c,const Spectrum &s)
{
    return c = Color((c * s).to_vector4());
}

/// *= on Vector3 and Spectrum.
inline MATH::Vector3 &operator*=(MATH::Vector3 &v,const Spectrum &s)
{
    return v = (v * s).to_vector3();
}

/// *= on Vector4 and Spectrum.
inline MATH::Vector4 &operator*=(MATH::Vector4 &v,const Spectrum &s)
{
    return v = (v * s).to_vector4();
}

/// /= on Spectrum and Color.
inline Spectrum &operator/=(Spectrum &s,const Color_struct &c)
{
    return s = s / c;
}

/// /= on Spectrum and Vector3.
inline Spectrum &operator/=(Spectrum &s,const MATH::Vector3 &v)
{
    return s = s / v;
}

/// /= on Spectrum and Vector4.
inline Spectrum &operator/=(Spectrum &s,const MATH::Vector4 &v)
{
    return s = s / v;
}

/// /= on Color and Spectrum.
inline Color &operator/=(Color &c,const Spectrum &s)
{
    return c = Color((c / s).to_vector4());
}

/// /= on Vector3 and Spectrum.
inline MATH::Vector3 &operator/=(MATH::Vector3 &v,const Spectrum &s)
{
    return v = (v / s).to_vector3();
}

/// /= on Vector4 and Spectrum.
inline MATH::Vector4 &operator/=(MATH::Vector4 &v,const Spectrum &s)
{
    return v = (v / s).to_vector4();
}

} // namespace COLOR
} // namespace MI


#endif // MI_METASL_RUNTIME_SPECTRUM_H

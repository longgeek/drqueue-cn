//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/math/version.h
/// \brief Major and minor version number and an optional qualifier, 
///        see \ref mi_math_version
///
//*****************************************************************************

#ifndef MI_MATH_VERSION_H
#define MI_MATH_VERSION_H

#include <mi/base/config.h>

/** \defgroup mi_math_version Versioning of the Math API
    \ingroup mi_math
    \brief The Math API has a major and minor version number and an optional qualifier.

    Version numbers and what they tell about compatibility across versions 
    is explained in \ref mi_math_intro_versioning .

    \par Include File:
    <tt> \#include <mi/math/version.h></tt>

    @{
 */

// No DLL API yet, make this API version 0 and do not document it in the manual.
//
// API version number.
//
// A change in this version number indicates that the binary compatibility
// of the interfaces offered through the shared library have changed. 
// Older versions can then explicitly asked for.
#define MI_MATH_API_VERSION  0


// The following three to four macros define the API version.
// The macros thereafter are defined in terms of the first four.

/// mental Math API major version number (see \ref mi_math_intro_versioning).
#define MI_MATH_VERSION_MAJOR  1

/// mental Math API minor version number (see \ref mi_math_intro_versioning).
#define MI_MATH_VERSION_MINOR  0

/// mental Math API version qualifier, which is a string such as \c "alpha",
/// \c "beta", or \c "beta2", or the empty string \c "" if this is a final 
/// release, in which case the macro \c MI_MATH_VERSION_QUALIFIER_EMPTY
/// is defined as well (see \ref mi_math_intro_versioning). 
#define MI_MATH_VERSION_QUALIFIER  ""

// This macro is defined if \c MI_MATH_VERSION_QUALIFIER is the empty string \c "".
#define MI_MATH_VERSION_QUALIFIER_EMPTY

/// mental Math API major and minor version number without qualifier in a
/// string representation, such as \c "1.1".
#define MI_MATH_VERSION_STRING  MI_BASE_STRINGIZE(MI_MATH_VERSION_MAJOR) "." \
                                MI_BASE_STRINGIZE(MI_MATH_VERSION_MINOR)

/// \def MI_MATH_VERSION_QUALIFIED_STRING
/// mental Math API major and minor version number and qualifier in a
/// string representation, such as \c "1.1" or \c "1.2-beta2".
#ifdef MI_MATH_VERSION_QUALIFIER_EMPTY
#define MI_MATH_VERSION_QUALIFIED_STRING  MI_MATH_VERSION_STRING
#else
#define MI_MATH_VERSION_QUALIFIED_STRING  MI_MATH_VERSION_STRING "-" MI_MATH_VERSION_QUALIFIER
#endif // MI_MATH_VERSION_QUALIFIER_EMPTY


/*@}*/ // end group mi_math_version

#endif // MI_MATH_VERSION_H

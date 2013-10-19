/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_VERSION_H
#define MI_SHADER_VERSION_H 1

namespace MI {
namespace SHADER {

// MetaSL version, runtime revision:
// 1 digit major, two digit minor, three digit rev.
// MetaSL 1.2, RT rev. 42 -> 102042
#define MI_METASL_RUNTIME_VERSION 101008

#define mi_stringify(s) # s
#define mi_make_str(s) mi_stringify(s)
#define mi_vers_str mi_make_str(MI_METASL_RUNTIME_VERSION)
static const char RUNTIME_VERSION_STRING[] = mi_vers_str;
#undef mi_vers_str
#undef mi_make_str
#undef mi_stringify


}}

#endif //MI_SHADER_VERSION_H

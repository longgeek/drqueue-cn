/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_METASL_RUNTIME_H
#define MI_METASL_RUNTIME_H

// shaders are compiled as shared object
#define MI_DLL_BUILD

#include <mi/base.h>
#include <mi/math.h>
#include <mi/metasl_runtime/mi_types.h>
#include <mi/metasl_runtime/math.h>
#include <mi/metasl_runtime/tag_wrapper.h>

#include <mi/metasl_runtime/mi_array.h>
#include <mi/metasl_runtime/mi_string.h>
#include <mi/metasl_runtime/mi_metasl_stdlib.h>
#include <mi/metasl_runtime/mi_smart_ptr.h>
#include <mi/metasl_runtime/mi_shader_version.h>
#include <mi/metasl_runtime/mi_shader_shader.h>
#include <mi/metasl_runtime/mi_shader_state.h>
#include <mi/metasl_runtime/mi_shader_utils.h>
#include <mi/metasl_runtime/mi_shader_plugin.h>
#include <mi/metasl_runtime/mi_builtin_brdfs.h>

#ifdef MI_RAY
#include <mi/metasl_runtime/mi_shader_state_mr.h>
#include <mi/metasl_runtime/mi_shader_typeconv.h>
#endif // MI_RAY

#endif // MI_METASL_RUNTIME_H

/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_SHADER_H
#define MI_SHADER_SHADER_H 1


#ifdef MI_PRODUCT_RAY
#ifdef MI_RAY
// request MetaSL support
#define MI_METASL_HEADERS
#include <shader.h>
#else
#include <mi_mem.h>
#endif
#endif

#include "mi_shader_types.h"

namespace MI {
namespace SHADER {

struct State;
class Brdf;
class Msl_brdf_adapter;


struct Shader_system
{
    /// Return a builtin Brdf instance of the requested type.
    ///
    /// The given initializer will handle input evaluation.
    virtual Brdf* get_builtin_brdf(
        Uint32 type,
        Msl_brdf_adapter* initializer) = 0;


    /// Release a builtin Brdf instance.
    virtual void release_builtin_brdf(Brdf* brdf) = 0;


    /// Register a string.
    ///
    /// Each string will be assigned an ID. Identical strings will receive
    /// identical IDs. Each registered string must be unregistered.
    virtual String_id register_string(const char* str) = 0;


    /// De-register a registered string.
    ///
    /// Only registered strings may be de-registered.
    virtual void deregister_string(const char* str) = 0;
};


struct Data_block
{
    // get access to a field, should return NULL for unknown field name
    virtual void* get_field(
        const char* name) = 0;

    // get access to a field, should return NULL for unknown field name
    virtual const void* get_field(
        const char* name) const = 0;

    // set name of the main result
    virtual void set_result(
        const char* name) = 0;
};

class Shader
{
public:

    // Note: no virtual dtor, COM-style deallocation through release

    // Main entry point of the shader.
    //
    // This function is called concurrently from multiple threads.
    virtual void main(State* state, Data_block* result) = 0;

    // destructor function
    virtual void release() const = 0;

    // Constant constructor.
    //
    // This function is called from a single thread.
    virtual void initialize_constant(State* state) = 0;

    // Constant destructor.
    //
    // This function is called from a single thread.
    virtual void finalize_constant(State* state) = 0;

    // Uniform constructor.
    //
    // This function is called from a single thread.
    virtual void initialize_uniform(State* state) = 0;

    // Uniform destructor.
    //
    // This function is called from a single thread.
    virtual void finalize_uniform(State* state) = 0;

};

}}      // namespace MI::SHADER

#endif // MI_SHADER_SHADER_H

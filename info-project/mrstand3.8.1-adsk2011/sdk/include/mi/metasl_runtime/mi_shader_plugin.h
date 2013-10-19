/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef RENDER_SHADER_PLUGIN_H
#define RENDER_SHADER_PLUGIN_H 1

#include <mi/base/config.h>
#include <mi/base/plugin.h>

#ifdef MI_PRODUCT_RAY
#ifdef MI_RAY
// request MetaSL support
#define MI_METASL_HEADERS
#include <shader.h>
#else
#include <mi_mem.h>
#endif
#endif

namespace MI {
namespace SHADER {
    class Shader;
    struct Data_block;
    struct Shader_system;
    class Brdf;
} // SHADER
} // MI

namespace MI {

namespace SHADER {

//-----------------------------------------------------------------------------
//                              shader plugin
//-----------------------------------------------------------------------------
//
//

class Software_shader_plugin: public mi::base::Plugin
{
  public:
    // Note: no virtual dtor, COM-style deallocation through release
    // (inherited from Plugin)

    // get the type of the plugin which is "shader"
    virtual const char* get_type() const = 0;

    virtual int get_version() const = 0;

    virtual const char* get_name() const = 0;

    virtual const char* get_compiler() const = 0;

    virtual Shader* new_instance(Shader_system* system, Data_block* arg) const = 0;

    virtual Brdf* new_brdf_instance(Shader_system* system, Data_block* arg) const = 0;

    // Note: libraries rely on this function being in this position, do not move!
    virtual const char* get_runtime_version() const = 0;

    virtual void delete_brdf_instance(Shader_system* system, Brdf* brdf) const = 0;

    virtual void register_strings(Shader_system* system) = 0;

    virtual void deregister_strings(Shader_system* system) = 0;
};

} } // SHADER::MI

#endif  // RENDER_SHADER_PLUGIN_H

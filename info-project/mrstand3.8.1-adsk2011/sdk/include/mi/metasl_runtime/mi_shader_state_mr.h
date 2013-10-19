/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_STATE_MR_H
#define MI_SHADER_STATE_MR_H

#include "mi_shader_shader.h"
#include "mi_shader_state.h"
#include "mi_shader_utils.h"

#ifdef MI_RAY
// request MetaSL support
#define MI_METASL_HEADERS
#include <shader.h>
#endif

// Shadow color for mi_shaderstate_* functions.
// These are #defined to avoid static constants.
#define MI_LIGHTSHADER_RESULT_KEY "msl:shadow"


namespace MI {
namespace SHADER {


// Output struct for MetaSL light shaders.
struct Light_shader_output
{
    COLOR::Spectrum_struct m_raw_contrib;  // raw, unshadowed contribution
    COLOR::Spectrum_struct m_shadow;       // shadow factor (e.g. black)
    miTag                  m_instance;     // associated light instance
};


//
// Structure for collection shader output arguments. For efficiency reason,
// number of outputs and 3 arrays pointers are collected together.
//

class Mr_gather_output : public Gather_result_struct
{
  public:
    // constructor
    Mr_gather_output(const Gather_result_struct&);

    bool                m_gathered;             // the values have been gathered
};


// Collect those shader results stored in \c result which are requested
// by the calling shader into the outputs supplied by \c state.
template <class T>
void gather(
        State*                  state,
        const T*                result);


// Returns a convex combination of \p result and the result of a transparency ray.
MATH::Vector4 transp_blend(
        miState*                state,
        const MATH::Vector4&    result,
        const MATH::Vector4&    transp);


// Stores and restores a value.
template <typename T>
class Store
{
public:
    // Copy the original value.
    Store(T& t)
    : m_addr(t), m_val(t)
    {}

    // Restore the original value.
    void restore()
    { m_addr = m_val; }

    // Restore the original value.
    ~Store()
    { restore(); }

private:
    T&  m_addr;
    T   m_val;

    Store(const Store&);
    Store& operator=(const Store&);
};

}}

#include "mi_shader_state_mr_inline.h"

#endif

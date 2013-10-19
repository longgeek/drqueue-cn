/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_STATE_MR_INLINE_H
#define MI_SHADER_STATE_MR_INLINE_H

namespace MI {
namespace SHADER {

// Constructor
inline Mr_gather_output::Mr_gather_output(const Gather_result_struct& gather)
: Gather_result_struct(gather)
, m_gathered(false)
{
}


template <class T>
void gather(
        State*                  state,
        const T*                result)
{
    Mr_gather_output* outputs = state->get_gather_output();
    if (0==outputs)
        return;
    static const char nullblock[sizeof(Vector4)] = { 0 };
    for (Uint32 i=0; i<outputs->m_count; ++i) {
        Variable_out_struct& var = outputs->m_outputs[i];
        // shader outputs
        if (var.m_def.m_type == Variable_def::SHADER_VAR) {
            const void* field = result->get_field(var.m_def.m_var.m_shader);
            if (0==field) {     // shader does not have an output with that name
                field = &nullblock;
            }
            switch (var.m_type) {
#define ASSIGN(ID,T) case Type_code::ID: \
    *static_cast<T*>(var.m_value) =      \
    *static_cast<const T*>(field);       \
                break;
            ASSIGN(BOOL,bool);
            ASSIGN(INT,Sint32);
            ASSIGN(ENUM,Sint32);
            ASSIGN(SCALAR,Float32);
            ASSIGN(DSCALAR,Float64);
            ASSIGN(VECTOR2,MATH::Vector2);
            ASSIGN(DVECTOR2,MATH::Dvector2);
            ASSIGN(VECTOR2I,MATH::Vector2i);
            ASSIGN(VECTOR2B,MATH::Vector2b);
            ASSIGN(VECTOR3,MATH::Vector3);
            ASSIGN(DVECTOR3,MATH::Dvector3);
            ASSIGN(VECTOR3I,MATH::Vector3i);
            ASSIGN(VECTOR3B,MATH::Vector3b);
            ASSIGN(VECTOR4,MATH::Vector4);
            ASSIGN(DVECTOR4,MATH::Dvector4);
            ASSIGN(VECTOR4I,MATH::Vector4i);
            ASSIGN(VECTOR4B,MATH::Vector4b);
            ASSIGN(COLOR,COLOR::Color_struct);
            ASSIGN(SPECTRUM,COLOR::Spectrum_struct);
            ASSIGN(MATRIX2x2,MATH::Matrix2x2f);
            ASSIGN(MATRIX2x3,MATH::Matrix2x3f);
            ASSIGN(MATRIX2x4,MATH::Matrix2x4f);
            ASSIGN(MATRIX3x2,MATH::Matrix3x2f);
            ASSIGN(MATRIX3x3,MATH::Matrix3x3f);
            ASSIGN(MATRIX3x4,MATH::Matrix3x4f);
            ASSIGN(MATRIX4x2,MATH::Matrix4x2f);
            ASSIGN(MATRIX4x3,MATH::Matrix4x3f);
            ASSIGN(MATRIX4x4,MATH::Matrix4x4f);
            ASSIGN(SHADER,Tag);
            ASSIGN(BSDF,Tag);
            ASSIGN(LIGHTPROFILE,Tag);
            default:
                break;
#undef ASSIGN
            }
        }
        else {
            // state variables
            switch (var.m_type) {
            case Type_code::SCALAR:
                *static_cast<Scalar*>(var.m_value) =
                    state->get_scalar(var.m_def.m_var.m_state);
                break;
            case Type_code::VECTOR2:
                *static_cast<Vector2*>(var.m_value) =
                    state->get_vector2(var.m_def.m_var.m_state);
                break;
            case Type_code::VECTOR3:
                *static_cast<Vector3*>(var.m_value) =
                    state->get_vector3(var.m_def.m_var.m_state);
                break;
            case Type_code::VECTOR4:
                *static_cast<Vector4*>(var.m_value) =
                    state->get_vector4(var.m_def.m_var.m_state);
                break;
            default:
                break;
            }
        }
    }

    outputs->m_gathered = true;
}


inline MATH::Vector4 transp_blend(
        miState*                state,
        const MATH::Vector4&    op_res,
        const MATH::Vector4&    transp)
{
    miColor tr_res;
    mi_trace_transparent(&tr_res,state);
    return op_res * (MATH::Vector4(1.f) - transp)
         + MATH::Vector4(tr_res.r,tr_res.g,tr_res.b,tr_res.a) * transp;
}


}}

#endif

/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_BUILTIN_BRDFS_H
#define MI_BUILTIN_BRDFS_H 1


#include "mi_shader_types.h"
#include "math.h"


namespace MI {
namespace SHADER {
#ifndef MI_INTERNAL
struct Brdf_state {};
#endif
class Brdf;
struct State;


// MetaSL shader graph to Brdf adapter
class Msl_brdf_adapter
{
public:

    // Initializes the result.
    // This function assigns the shader's inputs to the members of the
    // corresponding \c Msl_xxx_state class.
    // The incoming state cannot be const, because the assignment may involve
    // evaluation of an incoming shader graph. The MetaSL spec allows shaders
    // to modify the state.
    virtual void main(
            SHADER::State*              state,
            SHADER::Brdf_state*         result) = 0;

    // deletes this object
    virtual void release() const = 0;
};


}

namespace SOFTSHAD {


// builtin brdf types
enum Brdf_type
{
    Msl_phong = 1,
    Msl_ashikhmin,
    Msl_oren_nayar,
    Msl_carpaint,
    Msl_glass,
    Msl_thinglass,
    Msl_architectural,
    Msl_archcomp,
    Msl_lambert,
    Msl_carpaint_h,
    Msl_carpaint_x,
    Msl_legacy_phong,           // Illumination_phong legacy
    Msl_legacy_ashikhmin,       // Illumination_ashikhmin_shirley legacy
    Msl_legacy_cook_torrance,   // Illumination_cook_torrance legacy
    Msl_legacy_oren_nayar       // Illumination_oren_nayar legacy
};

// Map a type string to a Brdf_type.
inline Uint32 lookup_brdf_type(const char *type)
{
    static const struct
    {
        const char *name;
        Uint32 value;
    } values[] = {
        // builtin brdf types
        { "Msl_phong",         Msl_phong },
        { "Msl_ashikhmin",     Msl_ashikhmin },
        { "Msl_oren_nayar",    Msl_oren_nayar },
        { "Msl_carpaint",      Msl_carpaint },
        { "Msl_glass",         Msl_glass },
        { "Msl_thinglass",     Msl_thinglass },
        { "Msl_architectural", Msl_architectural },
        { "Msl_archcomp",      Msl_archcomp },
        { "Msl_lambert",       Msl_lambert },
        { "Msl_carpaint_h",    Msl_carpaint_h },
        { "Msl_carpaint_x",    Msl_carpaint_x },
        { "Msl_legacy_phong",           Msl_legacy_phong },
        { "Msl_legacy_ashikhmin",       Msl_legacy_ashikhmin },
        { "Msl_legacy_cook_torrance",   Msl_legacy_cook_torrance },
        { "Msl_legacy_oren_nayar",      Msl_legacy_oren_nayar },
    };

    if (type)
    {
        for (int i = sizeof(values) / sizeof(values[0]) - 1; i >= 0; --i)
        {
            if (!strcmp(type, values[i].name))
                return values[i].value;
        }
    }

    // default to Phong
    return static_cast<Uint32>(Msl_phong);
}


/** Full name of a builtin BSDF input of name \c n.

 This macro is used to easily adapt these fields to changes in the compiler
 core and C++ backend.
 */
#define BSDF_IN_NAME(n) bsdf_##n


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_phong_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    COLOR::Color BSDF_IN_NAME(glossy_color);
    Scalar       BSDF_IN_NAME(glossy_shininess);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(glossy_scalar);
};
struct Msl_legacy_phong_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    COLOR::Color BSDF_IN_NAME(specular_color);
    Scalar       BSDF_IN_NAME(specular_shininess);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(specular_scalar);
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_ashikhmin_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    COLOR::Color BSDF_IN_NAME(glossy_color);
    Scalar       BSDF_IN_NAME(glossy_shininess_u);
    Scalar       BSDF_IN_NAME(glossy_shininess_v);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(glossy_scalar);
};
struct Msl_legacy_ashikhmin_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    COLOR::Color BSDF_IN_NAME(specular_color);
    Scalar       BSDF_IN_NAME(shininess_u);
    Scalar       BSDF_IN_NAME(shininess_v);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(specular_scalar);
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_legacy_cook_torrance_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    COLOR::Color BSDF_IN_NAME(specular_color);
    COLOR::Color BSDF_IN_NAME(ior);
    Scalar       BSDF_IN_NAME(roughness);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(specular_scalar);
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_oren_nayar_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    Scalar       BSDF_IN_NAME(diffuse_deviation);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(glossy_scalar);
    COLOR::Color BSDF_IN_NAME(glossy_color);
    Scalar       BSDF_IN_NAME(glossy_shininess);
};
struct Msl_legacy_oren_nayar_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    Scalar       BSDF_IN_NAME(diffuse_deviation);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
    Scalar       BSDF_IN_NAME(specular_scalar);
    COLOR::Color BSDF_IN_NAME(specular_color);
    Scalar       BSDF_IN_NAME(specular_shininess);
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_carpaint_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(base_color);
    COLOR::Color BSDF_IN_NAME(reflectivity0);
    COLOR::Color BSDF_IN_NAME(reflectivity90);
    Scalar       BSDF_IN_NAME(fresnel_falloff);
    Scalar       BSDF_IN_NAME(metallic);
    COLOR::Color BSDF_IN_NAME(metallic_color);
    Scalar       BSDF_IN_NAME(metallic_falloff);
    COLOR::Color BSDF_IN_NAME(edge_color);
    Scalar       BSDF_IN_NAME(edge_falloff);
    Scalar       BSDF_IN_NAME(unit_scale);
    Scalar       BSDF_IN_NAME(sparkle_weight);
    Scalar       BSDF_IN_NAME(sparkle_falloff);
    SHADER::Tag  BSDF_IN_NAME(noise_perm_texture); // dummy, not used
    SHADER::Tag  BSDF_IN_NAME(noise_grad_texture); // dummy, not used
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_glass_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(color);
    Scalar       BSDF_IN_NAME(ior); // ignored by Brdf, but needed to fill the state
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_thinglass_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(color);
    COLOR::Color BSDF_IN_NAME(reflectivity0);
    COLOR::Color BSDF_IN_NAME(reflectivity90);
    Scalar       BSDF_IN_NAME(fresnel_falloff);
};


// State that stores the outputs of the shader graph driving the Brdf
struct Msl_architectural_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_refl);
    Scalar       BSDF_IN_NAME(diffuse_refl_scalar);
    Scalar       BSDF_IN_NAME(diffuse_dev);
    COLOR::Color BSDF_IN_NAME(specular_refl);
    Scalar       BSDF_IN_NAME(specular_refl_scalar);
    Scalar       BSDF_IN_NAME(refl_gloss);
    bool         BSDF_IN_NAME(metal_material);
    COLOR::Color BSDF_IN_NAME(specular_trans);
    Scalar       BSDF_IN_NAME(specular_trans_scalar);
    Scalar       BSDF_IN_NAME(trans_gloss);
    COLOR::Color BSDF_IN_NAME(diffuse_trans);
    Scalar       BSDF_IN_NAME(diffuse_trans_scalar);
    Scalar       BSDF_IN_NAME(anisotropy);
    Scalar       BSDF_IN_NAME(anisotropy_rotation);
    Scalar       BSDF_IN_NAME(material_ior);
};


// State that stores the outputs of the shader graph driving the Brdf.
// NOTE this is a version of \c Msl_architectural_state with renamed parameters.
// The layout of the two structs (excluding additions at the end) must be
// identical!
struct Msl_archcomp_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse);
    Scalar       BSDF_IN_NAME(diffuse_weight);
    Scalar       BSDF_IN_NAME(diffuse_roughness);
    COLOR::Color BSDF_IN_NAME(refl_color);
    Scalar       BSDF_IN_NAME(reflectivity);
    Scalar       BSDF_IN_NAME(refl_gloss);
    bool         BSDF_IN_NAME(refl_is_metal);
    COLOR::Color BSDF_IN_NAME(refr_color);
    Scalar       BSDF_IN_NAME(transparency);
    Scalar       BSDF_IN_NAME(refr_gloss);
    COLOR::Color BSDF_IN_NAME(refr_trans_color);
    Scalar       BSDF_IN_NAME(refr_trans_weight);
    Scalar       BSDF_IN_NAME(anisotropy);
    Scalar       BSDF_IN_NAME(anisotropy_rotation);
    Scalar       BSDF_IN_NAME(refr_ior);

    // deprecated
    bool         BSDF_IN_NAME(brdf_fresnel);
    Scalar       BSDF_IN_NAME(brdf_0_degree_refl);
    bool         BSDF_IN_NAME(refr_translucency);
};


// State that stores the outputs of the shader graph driving the Brdf.
struct Msl_lambert_state : public SHADER::Brdf_state
{
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    Scalar       BSDF_IN_NAME(diffuse_scalar);
};


// State that stores the outputs of the shader graph driving the Brdf.
struct Msl_carpaint_h_state : public SHADER::Brdf_state
{
    // diffuse
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    Scalar       BSDF_IN_NAME(diffuse_scalar);

    // three Cook-Torrance parameters
    COLOR::Color BSDF_IN_NAME(specular_color1);
    Scalar       BSDF_IN_NAME(specular_scalar1);
    Scalar       BSDF_IN_NAME(roughness1);
    COLOR::Color BSDF_IN_NAME(specular_color2);
    Scalar       BSDF_IN_NAME(specular_scalar2);
    Scalar       BSDF_IN_NAME(roughness2);
    COLOR::Color BSDF_IN_NAME(specular_color3);
    Scalar       BSDF_IN_NAME(specular_scalar3);
    Scalar       BSDF_IN_NAME(roughness3);
    COLOR::Color BSDF_IN_NAME(ior1);
    COLOR::Color BSDF_IN_NAME(ior2);
    COLOR::Color BSDF_IN_NAME(ior3);

    Scalar       BSDF_IN_NAME(refractive_index);
    Scalar       BSDF_IN_NAME(brdf_scaling);
    Scalar       BSDF_IN_NAME(scaling_factor);
    COLOR::Color BSDF_IN_NAME(laser_color);
    MATH::Vector3 BSDF_IN_NAME(coat_normal);
    bool         BSDF_IN_NAME(flake);
};

// State that stores the outputs of the shader graph driving the Brdf.
struct Msl_carpaint_x_state : public SHADER::Brdf_state
{
    // inputs from the shader graph
    COLOR::Color BSDF_IN_NAME(diffuse_color);
    COLOR::Color BSDF_IN_NAME(glossy_color);
    COLOR::Color BSDF_IN_NAME(reflection_color);
    COLOR::Color BSDF_IN_NAME(glossiness);
};


}}

#endif //MI_BUILTIN_BRDFS_H

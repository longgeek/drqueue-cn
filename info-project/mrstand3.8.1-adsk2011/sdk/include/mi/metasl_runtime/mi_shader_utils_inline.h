/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_UTILS_INLINE_H
#define MI_SHADER_UTILS_INLINE_H 1


namespace MI {
namespace SHADER {

// get ray type
Ray_type get_ray_type(
    const Ray_flags ray_flags)
{
    const Ray_flags all_flags =
        RAY_EYE |
        RAY_TRANSPARENT |
        RAY_REFRACT |
        RAY_REFLECT |
        RAY_SHADOW |
        RAY_ENVIRONMENT |
        RAY_OCCLUSION |
        RAY_ABSORB;

    return ray_flags & all_flags;
}

// get ray shader
Ray_flags get_ray_shader(
    const Ray_flags ray_flags)
{
    const Ray_flags all_flags =
        RAY_SHADER_SURFACE |
        RAY_SHADER_VOLUME |
        RAY_SHADER_PHOTON |
        RAY_SHADER_LIGHT |
        RAY_SHADER_DISPLACE |
        RAY_SHADER_ENVIRONMENT |
        RAY_SHADER_LENS;

    return ray_flags & all_flags;
}

// is in ray dispersal group
bool is_ray_dispersal_group(
    const Ray_flags ray_flags,
    const Ray_flags group)
{
    return (ray_flags & group) != 0;
}

// is in ray history group
bool is_ray_history_group(
    const Ray_flags ray_flags,
    const Ray_flags group)
{
    return (ray_flags & group) != 0;
}

// get ray type as a string
const char* get_ray_type_string(
    const Ray_flags ray_flags)
{
    switch (get_ray_type(ray_flags))
    {
      case RAY_EYE: return RAY_EYE_STRING;
      case RAY_TRANSPARENT: return RAY_TRANSPARENT_STRING;
      case RAY_REFRACT: return RAY_REFRACT_STRING;
      case RAY_REFLECT: return RAY_REFLECT_STRING;
      case RAY_SHADOW: return RAY_SHADOW_STRING;
      case RAY_OCCLUSION: return RAY_OCCLUSION_STRING;
      case RAY_ENVIRONMENT: return RAY_ENVIRONMENT_STRING;
      default: break;
    }
    return 0;
}

// get ray shader as a string
const char* get_ray_shader_string(
    const Ray_flags ray_flags)
{
    switch (get_ray_shader(ray_flags))
    {
      case RAY_SHADER_SURFACE: return RAY_SHADER_SURFACE_STRING;
      case RAY_SHADER_VOLUME: return RAY_SHADER_VOLUME_STRING;
      case RAY_SHADER_PHOTON: return RAY_SHADER_PHOTON_STRING;
      case RAY_SHADER_LIGHT: return RAY_SHADER_LIGHT_STRING;
      case RAY_SHADER_DISPLACE: return RAY_SHADER_DISPLACE_STRING;
      case RAY_SHADER_ENVIRONMENT: return RAY_SHADER_ENVIRONMENT_STRING;
      case RAY_SHADER_LENS: return RAY_SHADER_LENS_STRING;
      default: break;
    }
    return 0;
}

// get ray dispersal group as a string
const char* get_ray_dispersal_group_string(
    const Ray_flags ray_flags)
{
    switch (ray_flags)
    {
      case RAY_SPECULAR: return RAY_SPECULAR_STRING;
      case RAY_GLOSSY: return RAY_GLOSSY_STRING;
      case RAY_DIFFUSE: return RAY_DIFFUSE_STRING;
      default: break;
    }
    return 0;
}

// get ray history group as a string
const char* get_ray_history_group_string(
    const Ray_flags ray_flags)
{
    switch (ray_flags)
    {
      case RAY_LIGHTMAP: return RAY_LIGHTMAP_STRING;
      case RAY_FINALGATHER: return RAY_FINALGATHER_STRING;
      case RAY_HULL: return RAY_HULL_STRING;
      case RAY_VOLUME: return RAY_VOLUME_STRING;
      default: break;
    }
    return 0;
}

// get light type as a string
const char* get_light_type_string(
    const Light_type type)
{
    switch (type)
    {
      case LIGHT_POINT: return LIGHT_POINT_STRING;
      case LIGHT_SPOT: return LIGHT_SPOT_STRING;
      case LIGHT_INFINITE: return LIGHT_INFINITE_STRING;
      case LIGHT_PLANAR: return LIGHT_PLANAR_STRING;
      default: break;
    }
    return 0;
}



template <typename T>
inline T scene_data(
        const State*                    state,
        const State::Data_source        source,
        const State::Data_type          data_type,
        const Uint32                    acc_count,
        const Data_member_struct*       accessors,
        const Type_code::Id             type,
        const T&                        deflt)
{
    T result(deflt);
    get_scene_data(state,source,data_type,acc_count,accessors,type,result);
    return result;
}


template <typename T>
inline bool get_scene_data(
        const State*                    state,
        const State::Data_source        source,
        const State::Data_type          data_type,
        const Uint32                    acc_count,
        const Data_member_struct*       accessors,
        const Type_code::Id             type,
        T&                              result)
{
    return state->get_scene_data(
            source,data_type,
            acc_count,accessors,
            type,sizeof(T),
            &result);
}



// constructor
inline Sample_iterator::Sample_iterator(
    Sampling_context*   context,        // context
    const Uint32        n)              // count
  : m_context   ( context )
{
    m_context->begin(n);
}

// destructor
inline Sample_iterator::~Sample_iterator()
{
    m_context->stop();
}

// is at end
inline bool Sample_iterator::end()
{
    return m_context->end();
}

// advance to next
inline void Sample_iterator::next()
{
    m_context->next();
}

// single dimensional sample. If multiple dimensional sample is
// required, this function should be called several times.
inline Scalar Sample_iterator::sample()
{
    return m_context->sample();
}
inline Vector2 Sample_iterator::sample2()
{
    return m_context->sample2();
}
inline Vector3 Sample_iterator::sample3()
{
    return m_context->sample3();
}
inline Vector4 Sample_iterator::sample4()
{
    return m_context->sample4();
}

inline Lazy_factory::Lazy_factory(State* state)
: m_state(state), m_access(0)
{
}

inline Lazy_factory::operator Factory_access&()
{
    if (!m_access)
        m_access = Factory_access(m_state->get_factory());
    return m_access;
}

inline Factory* Lazy_factory::operator->()
{
    Factory_access& fa = *this;
    return fa.operator->();
}

// constructor
template<typename TR,           // result type: Scalar, Vector[234], Color
         typename TC>           // coordinate type: Scalar, Vector2, Vector3
inline Texture_sampler_access<TR,TC>::Texture_sampler_access(
    Interface* pointer) :                       // pointer
  Base_class( pointer )
{
}


}}      // namespace MI::SHADER

#endif // MI_SHADER_UTILS_INLINE_H

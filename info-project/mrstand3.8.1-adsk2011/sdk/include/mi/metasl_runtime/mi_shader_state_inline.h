/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_STATE_INLINE_H
#define MI_SHADER_STATE_INLINE_H 1

#include <mi/base/assert.h>

namespace MI {
namespace SHADER {

// constructor
inline Variable_def::Variable_def()
{
    m_type = UNDEFINED;
}

// state var def constructor
inline Variable_def::Variable_def(
    State_sym::Id s)                    // state var
{
    m_type = STATE_VAR;
    m_var.m_state = s;
}

// shader var def constructor
inline Variable_def::Variable_def(
    const char* s)                              // shader var

{
    m_type = SHADER_VAR;
    m_var.m_shader = s;
}

// shader var ctor
template <typename Result_type>
inline Variable<Result_type>::Variable(
    const Variable_def_struct&  d,
    Type_code::Id               tp,
    Result_type                 val)
{
    this->m_def = d;
    this->m_type = tp;
    this->m_value = val;
}


inline void Trace_options::set_defaults()
{
    m_near               = 0.0;
    m_far                = 1e36f; // huge
    m_importance         = 1.0f;
    m_enable_environment = true;
    m_ray_type           = RAY_REFLECT;
    m_ray_flags          = RAY_SPECULAR;
    m_ray_data           = 0;
}

// constructor
inline Trace_options::Trace_options()
: m_data_access(0)
{
    set_defaults();
}

// constructor
inline Trace_options::Trace_options(const Factory* f)
: m_data_access(f->create_ray_data())
{
    set_defaults();
    m_ray_data           = m_data_access.get();
}

// Copy constructor.
inline Trace_options::Trace_options(
const Trace_options &other)                 // The Trace_options to copy.
: m_data_access(other.m_data_access)
{
    m_near               = other.m_near;
    m_far                = other.m_far;
    m_importance         = other.m_importance;
    m_enable_environment = other.m_enable_environment;
    m_ray_type           = other.m_ray_type;
    m_ray_flags          = other.m_ray_flags;
    m_ray_data           = other.m_ray_data;
}

// Copy constructor.
inline Trace_options &Trace_options::operator=(
const Trace_options &other)                 // The Trace_options to copy.
{
    if(this != &other) {
        m_data_access        = other.m_data_access;
        m_near               = other.m_near;
        m_far                = other.m_far;
        m_importance         = other.m_importance;
        m_enable_environment = other.m_enable_environment;
        m_ray_type           = other.m_ray_type;
        m_ray_flags          = other.m_ray_flags;
        m_ray_data           = other.m_ray_data;
    }
    return *this;
}

// set near distance
inline void Trace_options::set_near(
    double v)                           // near distance
{
    m_near = v;
}

// set far distance
inline void Trace_options::set_far(
    double v)                           // near distance
{
    m_far = v;
}

// set ray type
inline void Trace_options::set_ray_type(
    Ray_type v)                         // ray type
{
    m_ray_type = v;
}

// set ray group
inline void Trace_options::set_ray_dispersal_group(
    Ray_type v)                         // ray group
{
    m_ray_flags = v;
}

// set importance
inline void Trace_options::set_importance(
    float v)                            // importance
{
    m_importance = v;
}

// set importance
inline void Trace_options::set_importance(
    const COLOR::Color_struct& c)           // importance
{
    set_importance(COLOR::Color(c).linear_intensity());
}

// set importance
inline void Trace_options::set_importance(
    const COLOR::Spectrum_struct& s)        // importance
{
    set_importance(COLOR::Spectrum(s).linear_intensity());
}

// toggle usage of the environment shader
inline void Trace_options::enable_environment(
    bool enable_environment)                // enable environment shader if true
{
    m_enable_environment = enable_environment;
}

// set ray data
inline void Trace_options::set_data(
    const char                      *name,      // name
    const Type_code::Id             type,       // type
    Uint32                          size,       // size
    void                            *value)     // value
{
    m_ray_data->set(name,type,size,value);
}


// constructor
inline Occlusion_options::Occlusion_options()   // supply no-op defaults
{
    m_near       = 0.0;
    m_far        = 1e36f; // huge
    m_importance = 1.0f;
    m_axis       = Vector3( 0, 0, 0 );
    m_angle      = 90.0f;
    m_angle_exp  = 1.0f;
}

// Copy constructor.
inline Occlusion_options::Occlusion_options(
const Occlusion_options &other)     // The Occlusion_options to copy.
{
    m_near                  = other.m_near;
    m_far                   = other.m_far;
    m_importance            = other.m_importance;
    m_axis                  = other.m_axis;
    m_angle                 = other.m_angle;
    m_angle_exp             = other.m_angle_exp;
}

// Copy constructor.
inline Occlusion_options &Occlusion_options::operator=(
const Occlusion_options &other)     // The Occlusion_options to copy.
{
    if(this != &other) {
        m_near              = other.m_near;
        m_far               = other.m_far;
        m_importance        = other.m_importance;
        m_axis              = other.m_axis;
        m_angle             = other.m_angle;
        m_angle_exp         = other.m_angle_exp;
    }
    return *this;
}

// set near distance
inline void Occlusion_options::set_near(
    double v)                           // near distance
{
    m_near = v;
}

// set far distance
inline void Occlusion_options::set_far(
    double v)                           // near distance
{
    m_far = v;
}

// set importance
inline void Occlusion_options::set_importance(
    float v)                            // importance
{
    m_importance = v;
}

// set importance
inline void Occlusion_options::set_importance(
    const COLOR::Color_struct& c)           // importance
{
    set_importance(COLOR::Color(c).linear_intensity());
}

// set importance
inline void Occlusion_options::set_importance(
    const COLOR::Spectrum_struct& s)        // importance
{
    set_importance(COLOR::Spectrum(s).linear_intensity());
}

// set cone
inline void Occlusion_options::set_cone(
    const Vector3& axis,                // cone axis
    const float angle,                  // cone angle
    const float angle_exp)              // phong exponent
{
    m_axis  = axis;
    m_angle = angle;
    m_angle_exp = angle_exp;
}


// constructor
inline Irradiance_options::Irradiance_options() // supply no-op defaults
{
    m_near       = 0.0;
    m_far        = 1e36f; // huge
    m_importance = 1.0f;
    m_axis       = Vector3( 0, 0, 0 );
    m_angle      = 90.0f;
    m_angle_exp  = 1.0f;
}

// Copy constructor.
inline Irradiance_options::Irradiance_options(
const Irradiance_options &other)    // The Irradiance_options to copy.
{
    m_near                  = other.m_near;
    m_far                   = other.m_far;
    m_importance            = other.m_importance;
    m_axis                  = other.m_axis;
    m_angle                 = other.m_angle;
    m_angle_exp             = other.m_angle_exp;
}

// Copy constructor.
inline Irradiance_options &Irradiance_options::operator=(
const Irradiance_options &other)    // The Irradiance_options to copy.
{
    if(this != &other) {
        m_near              = other.m_near;
        m_far               = other.m_far;
        m_importance        = other.m_importance;
        m_axis              = other.m_axis;
        m_angle             = other.m_angle;
        m_angle_exp         = other.m_angle_exp;
    }
    return *this;
}

// set near distance
inline void Irradiance_options::set_near(
    double v)                           // near distance
{
    m_near = v;
}

// set far distance
inline void Irradiance_options::set_far(
    double v)                           // near distance
{
    m_far = v;
}

// set importance
inline void Irradiance_options::set_importance(
    float v)                            // importance
{
    m_importance = v;
}

// set importance
inline void Irradiance_options::set_importance(
    const COLOR::Color_struct& c)           // importance
{
    set_importance(COLOR::Color(c).linear_intensity());
}

// set importance
inline void Irradiance_options::set_importance(
    const COLOR::Spectrum_struct& s)        // importance
{
    set_importance(COLOR::Spectrum(s).linear_intensity());
}

// set cone
inline void Irradiance_options::set_cone(
    const Vector3& axis,                // cone axis
    const float angle,                  // cone angle
    const float angle_exp)              // phong exponent
{
    m_axis  = axis;
    m_angle = angle;
    m_angle_exp = angle_exp;
}

Light_iterator_options::Light_iterator_options()
{
    m_categories_set = false;
    m_n_categories = 0;
    m_categories = 0;
    m_shadows_set = false;
    m_shadows = true;
    m_cone_set = false;
    m_cone_axis = 0;
    m_cone_angle = 90.0f;
}

// set categories
void Light_iterator_options::set_categories(
    const Uint32 n_categories,     // The number of categories.
    const char *categories[])   // The array of categories.
{
    m_categories_set = true;
    m_n_categories = n_categories;
    m_categories = categories;
}

// set shadows
void Light_iterator_options::set_shadows(
    const bool on_off)          // Compute shadows if true.
{
    m_shadows_set = true;
    m_shadows = on_off;
}

// set cone
void Light_iterator_options::set_cone(
    const Vector3& axis,        // The axis of the cone.
    const Scalar angle)         // The angle of the cone.
{
    m_cone_set = true;
    m_cone_axis = axis;
    m_cone_angle = angle;
}

// propagate the options to a light sampler
void Light_iterator_options::apply(
    Light_sampler& sampler) const
{
    if (m_categories_set)
        sampler.set_categories(m_n_categories, m_categories);
    if (m_shadows_set)
        sampler.set_shadows(m_shadows);
    if (m_cone_set)
        sampler.set_cone(m_cone_axis, m_cone_angle);
}

Light_iterator::Light_iterator(
    const Factory* const factory,
    const Light_iterator_options& options)
{
    init(&options, factory->create_light_sampler());
}

Light_iterator::Light_iterator(const Factory* const factory)
{
    init(NULL, factory->create_light_sampler());
}

Light_iterator::Light_iterator(
    Light_sampler* const sampler,
    const Light_iterator_options& options)
{
    init(&options, sampler);
}

Light_iterator::Light_iterator(Light_sampler* const sampler)
{
    init(NULL, sampler);
}

// constructor.
Light_iterator::Light_iterator(const Factory* const factory, const Light_iterator& source)
{
    init(NULL, NULL);
    *this = source;
}

Light_iterator::Light_iterator(const Light_iterator& source)
{
    init(NULL, NULL);
    *this = source;
}

Light_iterator& Light_iterator::operator=(const Light_iterator& source)
{
    if (this == &source) // handle self-assignment
        return *this;

    Light_iterator_struct::operator=(source);

    if (m_sampler)
        m_sampler->release();

    m_sampler = source.m_sampler->clone();
    m_sampler->add_ref();

    return *this;
}

Light_iterator::~Light_iterator() {
    mi_base_assert(m_sampler);
    m_sampler->release();
}

void Light_iterator::init(
    const Light_iterator_options* const options,
    Light_sampler* sampler)
{
    m_valid = false;
    m_sampler = sampler;

    if (m_sampler)
    {
        m_sampler->add_ref();

        if (options)
            options->apply(*m_sampler);

        m_sampler->get_next( this );
    }
}

// advance to next sample
Light_iterator &Light_iterator::operator++()
{
    m_sampler->get_next( this );
    return *this;
}

// advance to next sample
Light_iterator Light_iterator::operator++(
    int)                                // dummy int
{
    Light_iterator it = *this;
    m_sampler->get_next( this );
    return it;
}

// equal
bool Light_iterator::operator==(
    const Light_iterator& it) const             // compare to this
{
    return
        m_count   == it.m_count &&
        m_sampler == it.m_sampler &&
        m_valid   == it.m_valid;
}

// not equal
bool Light_iterator::operator!=(
    const Light_iterator& it) const             // compare to this
{
    return !(*this == it);
}

// true if valid, false otherwise
Light_iterator::operator bool() const   // compare to this
{
    return m_valid;
}

// sample point on the light
const Vector3 &Light_iterator::get_point() const
{
    return m_point;
}

// normalized direction to light sample
const Vector3 &Light_iterator::get_direction() const
{
    return m_dir;
}

// distance illuminated point -> m_point
Scalar Light_iterator::get_distance() const
{
    return m_dist;
}

// state->normal * m_dir
Scalar Light_iterator::get_dot_nl() const
{
    return m_dot_nl;
}

// return the contribution from the light. The result of the
// get_contribution function is equal to raw_contribution * shadow
// (where shadows include volume atten.)

// light contribution incl. shadow & volume
const COLOR::Spectrum_struct Light_iterator::get_contribution() const
{
    return SHADER::get_contribution(*this);
}

// light contribution w/o shadow & volume
const COLOR::Spectrum_struct Light_iterator::get_raw_contribution() const
{
    return SHADER::get_raw_contribution(*this);
}

// shadow atten, 1 1 1=none, 0 0 0=full
const COLOR::Spectrum_struct Light_iterator::get_shadow() const
{
    return m_shadow;
}

// get light parameter
bool Light_iterator::get_light_parameter(
    const char*         name,           // parameter name
    Type_code::Id       type,           // parameter type
    void*               value) const    // parameter value
{
    return m_sampler->get_light_parameter(
        name,
        type,
        value );
}

// return the number of samples taken so far
Uint Light_iterator::get_count() const
{
    return m_count;
}

// true if valid, false otherwise
bool Light_iterator::is_valid() const
{
    return m_valid;
}

// get a pointer to Light_iterator_struct
inline const Light_iterator_struct* Light_iterator::operator&() const
{
    return (const Light_iterator_struct*)this;
}

// get a pointer to Light_iterator_struct
inline Light_iterator_struct* Light_iterator::operator&()
{
    return (Light_iterator_struct*)this;
}

// get the contribution of a light iterator
inline COLOR::Spectrum_struct get_contribution(
    const Light_iterator_struct& light_iterator)
{
    return light_iterator.m_weight * 
           light_iterator.m_raw_contrib *
           light_iterator.m_shadow;
}

// get the raw contribution of a light iterator
inline COLOR::Spectrum_struct get_raw_contribution(
    const Light_iterator_struct& light_iterator)
{
    return light_iterator.m_weight *
           light_iterator.m_raw_contrib;
}

}}      // namespace MI::SHADER

#endif

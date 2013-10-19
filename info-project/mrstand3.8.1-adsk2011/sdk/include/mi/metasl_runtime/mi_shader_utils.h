/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_UTILS_H
#define MI_SHADER_UTILS_H 1

#include "mi_smart_ptr.h"
#include "mi_shader_state.h"

namespace MI {
namespace SHADER {

static const char* RAY_EYE_STRING                = "eye";
static const char* RAY_TRANSPARENT_STRING        = "transparent";
static const char* RAY_REFRACT_STRING            = "refract";
static const char* RAY_REFLECT_STRING            = "reflect";
static const char* RAY_SHADOW_STRING             = "shadow";
static const char* RAY_OCCLUSION_STRING          = "occlusion";
static const char* RAY_ENVIRONMENT_STRING        = "environment";

static const char* RAY_DIFFUSE_STRING            = "diffuse";
static const char* RAY_GLOSSY_STRING             = "glossy";
static const char* RAY_SPECULAR_STRING           = "specular";

static const char* RAY_SHADER_SURFACE_STRING     = "surface";
static const char* RAY_SHADER_VOLUME_STRING      = "volume";
static const char* RAY_SHADER_PHOTON_STRING      = "photon";
static const char* RAY_SHADER_LIGHT_STRING       = "light";
static const char* RAY_SHADER_DISPLACE_STRING    = "displace";
static const char* RAY_SHADER_ENVIRONMENT_STRING = "environment";
static const char* RAY_SHADER_LENS_STRING        = "lens";

static const char* RAY_LIGHTMAP_STRING           = "lightmap";
static const char* RAY_FINALGATHER_STRING        = "finalgather";
static const char* RAY_HULL_STRING               = "hull";
static const char* RAY_VOLUME_STRING             = "volume";

static const char* LIGHT_POINT_STRING            = "light_point";
static const char* LIGHT_SPOT_STRING             = "light_spot";
static const char* LIGHT_INFINITE_STRING         = "light_infinite";
static const char* LIGHT_PLANAR_STRING           = "light_planar";

enum Light_type
{
    LIGHT_POINT         = 0,
    LIGHT_SPOT          = 1,
    LIGHT_INFINITE      = 2,
    LIGHT_PLANAR        = 3
};

// get ray type
inline Ray_type get_ray_type(
    const Ray_flags ray_flags);

// get ray shader
inline Ray_flags get_ray_shader(
    const Ray_flags ray_flags);

// is in ray dispersal group
inline bool is_ray_dispersal_group(
    const Ray_flags ray_flags,
    const Ray_flags group);

// is in ray history group
inline bool is_ray_history_group(
    const Ray_flags ray_flags,
    const Ray_flags group);

// get ray type as a string
inline const char* get_ray_type_string(
    const Ray_flags ray_flags);

// get ray shader as a string
inline const char* get_ray_shader_string(
    const Ray_flags ray_flags);

// get ray dispersal group as a string
inline const char* get_ray_dispersal_group_string(
    const Ray_flags ray_flags);

// get ray history group as a string
inline const char* get_ray_history_group_string(
    const Ray_flags ray_flags);

// get light type as a string
inline const char* get_light_type_string(
    const Light_type type);


// get scene data
template <typename T>
inline T scene_data(
    const State*                    state,
    const State::Data_source        source,
    const State::Data_type          data_type,
    const Uint32                    acc_count,
    const Data_member_struct*       accessors,
    const Type_code::Id             type,
    const T&                        deflt);


// get scene data
template <typename T>
inline bool get_scene_data(
    const State*                    state,
    const State::Data_source        source,
    const State::Data_type          data_type,
    const Uint32                    acc_count,
    const Data_member_struct*       accessors,
    const Type_code::Id             type,
    T&                              res);



typedef Smart_ptr<State> State_access;
typedef Smart_ptr<Frame> Frame_access;
typedef Smart_ptr<Camera> Camera_access;
typedef Smart_ptr<Factory> Factory_access;
typedef Smart_ptr<Log> Log_access;
typedef Smart_ptr<Light_sampler> Light_sampler_access;
typedef Smart_ptr<Texture_info> Texture_info_access;

class Lazy_factory
{
public:
    Lazy_factory(State*);
    operator Factory_access&();
    Factory* operator->();

private:
    State*         m_state;
    Factory_access m_access;
};

template<typename TR,           // result type: Scalar, Vector[234], Color
         typename TC>           // coordinate type: Scalar, Vector2, Vector3
struct Texture_sampler_access : public Smart_ptr< Texture_sampler<TR,TC> >
{
    typedef Texture_sampler<TR,TC>      Interface;
    typedef Smart_ptr<Interface>        Base_class;

    // constructor
    Texture_sampler_access(
        Interface* pointer=0);                    // pointer
};

// 1D
typedef Texture_sampler_access<Scalar,                 Scalar>  
Texture1D_sampler_float_access;
typedef Texture_sampler_access<Vector2,                Scalar>  
Texture1D_sampler_float2_access;
typedef Texture_sampler_access<Vector3,                Scalar>  
Texture1D_sampler_float3_access;
typedef Texture_sampler_access<Vector4,                Scalar>  
Texture1D_sampler_float4_access;
typedef Texture_sampler_access<Dscalar,                Scalar>  
Texture1D_sampler_double_access;
typedef Texture_sampler_access<Dvector2,               Scalar>  
Texture1D_sampler_double2_access;
typedef Texture_sampler_access<Dvector3,               Scalar>  
Texture1D_sampler_double3_access;
typedef Texture_sampler_access<Dvector4,               Scalar>  
Texture1D_sampler_double4_access;
typedef Texture_sampler_access<COLOR::Color_struct,    Scalar>  
Texture1D_sampler_color_access;
typedef Texture_sampler_access<COLOR::Spectrum_struct, Scalar>  
Texture1D_sampler_spectrum_access;
// 2D
typedef Texture_sampler_access<Scalar,                 Vector2> 
Texture2D_sampler_float_access;
typedef Texture_sampler_access<Vector2,                Vector2> 
Texture2D_sampler_float2_access;
typedef Texture_sampler_access<Vector3,                Vector2> 
Texture2D_sampler_float3_access;
typedef Texture_sampler_access<Vector4,                Vector2> 
Texture2D_sampler_float4_access;
typedef Texture_sampler_access<Dscalar,                Vector2> 
Texture2D_sampler_double_access;
typedef Texture_sampler_access<Dvector2,               Vector2> 
Texture2D_sampler_double2_access;
typedef Texture_sampler_access<Dvector3,               Vector2> 
Texture2D_sampler_double3_access;
typedef Texture_sampler_access<Dvector4,               Vector2> 
Texture2D_sampler_double4_access;
typedef Texture_sampler_access<COLOR::Color_struct,    Vector2> 
Texture2D_sampler_color_access;
typedef Texture_sampler_access<COLOR::Spectrum_struct, Vector2> 
Texture2D_sampler_spectrum_access;
// 3D
typedef Texture_sampler_access<Scalar,                 Vector3> 
Texture3D_sampler_float_access;
typedef Texture_sampler_access<Vector2,                Vector3> 
Texture3D_sampler_float2_access;
typedef Texture_sampler_access<Vector3,                Vector3> 
Texture3D_sampler_float3_access;
typedef Texture_sampler_access<Vector4,                Vector3> 
Texture3D_sampler_float4_access;
typedef Texture_sampler_access<Dscalar,                Vector3> 
Texture3D_sampler_double_access;
typedef Texture_sampler_access<Dvector2,               Vector3> 
Texture3D_sampler_double2_access;
typedef Texture_sampler_access<Dvector3,               Vector3> 
Texture3D_sampler_double3_access;
typedef Texture_sampler_access<Dvector4,               Vector3> 
Texture3D_sampler_double4_access;
typedef Texture_sampler_access<COLOR::Color_struct,    Vector3> 
Texture3D_sampler_color_access;
typedef Texture_sampler_access<COLOR::Spectrum_struct, Vector3> 
Texture3D_sampler_spectrum_access;
// CUBE
typedef Texture_sampler_access<Scalar,                 Vector3> 
TextureCUBE_sampler_float_access;
typedef Texture_sampler_access<Vector2,                Vector3> 
TextureCUBE_sampler_float2_access;
typedef Texture_sampler_access<Vector3,                Vector3> 
TextureCUBE_sampler_float3_access;
typedef Texture_sampler_access<Vector4,                Vector3> 
TextureCUBE_sampler_float4_access;
typedef Texture_sampler_access<Dscalar,                Vector3> 
TextureCUBE_sampler_double_access;
typedef Texture_sampler_access<Dvector2,               Vector3> 
TextureCUBE_sampler_double2_access;
typedef Texture_sampler_access<Dvector3,               Vector3> 
TextureCUBE_sampler_double3_access;
typedef Texture_sampler_access<Dvector4,               Vector3> 
TextureCUBE_sampler_double4_access;
typedef Texture_sampler_access<COLOR::Color_struct,    Vector3> 
TextureCUBE_sampler_color_access;
typedef Texture_sampler_access<COLOR::Spectrum_struct, Vector3> 
TextureCUBE_sampler_spectrum_access;

struct Sample_iterator
{
    // constructor
    inline Sample_iterator(
        Sampling_context*       context,        // context
        const Uint32            n = 0);         // count

    // destructor
    inline ~Sample_iterator();

    // is at end
    inline bool end();

    // advance to next
    inline void next();

    // single dimensional sample. If multiple dimensional sample is
    // required, this function should be called several times.
    inline Scalar  sample();
    inline Vector2 sample2();
    inline Vector3 sample3();
    inline Vector4 sample4();

    Smart_ptr<Sampling_context> m_context;      // context
};

// equal operator for Smart_ptr
template<class T> inline bool operator==(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// not-equal operator for Smart_ptr
template<class T> inline bool operator!=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// less-than operator for Smart_ptr
template<class T> inline bool operator<(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// less-equal operator for Smart_ptr
template<class T> inline bool operator<=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// greater-than operator for Smart_ptr
template<class T> inline bool operator>(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// greater-equal operator for Smart_ptr
template<class T> inline bool operator>=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// equal operator for Smart_ptr
template<class T> inline bool operator==(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs);   // right hand-side instance

// not-equal operator for Smart_ptr
template<class T> inline bool operator!=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs);   // right hand-side instance

// less-than operator for Smart_ptr
template<class T> inline bool operator<(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs);   // right hand-side instance

// less-equal operator for Smart_ptr
template<class T> inline bool operator<=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs);   // right hand-side instance

// greater-than operator for Smart_ptr
template<class T> inline bool operator>(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs);   // right hand-side instance

// greater-equal operator for Smart_ptr
template<class T> inline bool operator>=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs);   // right hand-side instance

// equal operator for Smart_ptr
template<class T> inline bool operator==(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// not-equal operator for Smart_ptr
template<class T> inline bool operator!=(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// less-than operator for Smart_ptr
template<class T> inline bool operator<(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// less-equal operator for Smart_ptr
template<class T> inline bool operator<=(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// greater-than operator for Smart_ptr
template<class T> inline bool operator>(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// greater-equal operator for Smart_ptr
template<class T> inline bool operator>=(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs);   // right hand-side instance

// Scoped memory allocation using a class that
// provides alloc and free methods.
template <typename Allocator>
class Scoped_alloc
{
  public:
    Scoped_alloc(
        Allocator& allocator,
        const size_t num_bytes) :
        m_allocator(allocator),
        m_ptr(allocator.alloc(num_bytes))
    { }

    ~Scoped_alloc()
    {
        m_allocator.free(m_ptr);
    }

    void* get() const
    {
        return m_ptr;
    }

  private:
    // non-copyable
    Scoped_alloc(const Scoped_alloc&);
    Scoped_alloc& operator=(const Scoped_alloc&);

    Allocator& m_allocator;
    void* m_ptr;
};

}}      // namespace MI::SHADER

#include "mi_shader_utils_inline.h"

#endif // MI_SHADER_UTILS_H

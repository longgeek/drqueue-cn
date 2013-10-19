/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_STATE_H
#define MI_SHADER_STATE_H 1

#include "mi_shader_types.h"
#include "math.h"
#include "color.h"
#include "mi_rdiff.h"
#include "mi_smart_ptr.h"


#ifdef MI_PRODUCT_RAY
struct miState;
#endif

namespace MI {
namespace SHADER {

using MATH::Vector2;
using MATH::Vector3;
using MATH::Vector4;
using MATH::Dvector2;
using MATH::Dvector3;
using MATH::Dvector4;
using MATH::Matrix4x4d;

class Brdf;
struct Material_def;
struct State;
struct Factory;
struct Log;
struct Frame;
struct Light_sampler;
class Light_iterator_options;
struct Light_iterator_struct;
struct Light_iterator;
struct Trace_options_struct;
struct Trace_options;
struct Occlusion_options_struct;
struct Occlusion_options;
struct Irradiance_options_struct;
struct Irradiance_options;
struct Sampling_context;
struct Data_block;


//-----------------------------------------------------------------------------
//
// builtin filters. Sinc filters (with negative coefficients) are clipped;
// result cannot be outside the range of all the samples under the filter.
struct Texture_filter
{
    enum Id {
        BOX             = 0,            // box filter
        TRIANGLE,                       // triangle filter
        GAUSS,                          // Gaussian filter
        CMITCHELL,                      // clipped Mitchell filter
        CLANCZOS,                       // clipped Lanczos filter
        FAST,                           // could be GPU anti-aliasing, or any
        NONE,                           // no filtering
        DATA,                           // data texture, no clamp / trafo / filtering

        NUM,                            // number of filters
        ALIGN           = 0xFFFFFFFF    // force to be 32bits
    };
};


//-----------------------------------------------------------------------------
//
// Base type ids
//
struct Type_code
{
    enum Id
    {
        BOOL            = 0,            // Bool type
        INT,                            // Int type
        SCALAR,                         // Scalar type (float)
        DSCALAR,                        // Dscalar type (double)
        VECTOR2,                        // Vector2 type (float)
        VECTOR3,                        // Vector3 type (float)
        VECTOR4,                        // Vector4 type (float)
        DVECTOR2,                       // Vector2 type (double)
        DVECTOR3,                       // Vector3 type (double)
        DVECTOR4,                       // Vector4 type (double)
        VECTOR2I,                       // Vector2i type
        VECTOR3I,                       // Vector3i type
        VECTOR4I,                       // Vector4i type
        VECTOR2B,                       // Vector2b type
        VECTOR3B,                       // Vector3b type
        VECTOR4B,                       // Vector4b type
        COLOR,                          // Color type
        SPECTRUM,                       // Spectrum type
        MATRIX2x2,                      // Matrix2x2 type
        MATRIX2x3,                      // Matrix2x3 type
        MATRIX2x4,                      // Matrix2x4 type
        MATRIX3x2,                      // Matrix3x2 type
        MATRIX3x3,                      // Matrix3x3 type
        MATRIX3x4,                      // Matrix3x4 type
        MATRIX4x2,                      // Matrix4x2 type
        MATRIX4x3,                      // Matrix4x3 type
        MATRIX4x4,                      // Matrix4x4 type
        TEXTURE1D,                      // Texture1d type
        TEXTURE2D,                      // Texture2d type
        TEXTURE3D,                      // Texture3d type
        TEXTURE_CUBE,                   // Texture_cube type
        SHADER,                         // Shader type
        BSDF,                           // Bsdf type
        STRING,                         // String type
        ENUM,                           // Enum type
        STRUCT,                         // Struct type
        LIGHTPROFILE,                   // Lightprofile type

        NUM_TYPES,                      // Number of types
        ALIGN           = 0xFFFFFFFF    // force to be 32bits
    };
};


//-----------------------------------------------------------------------------
///
/// State symbols a shader can ask the state for. Many offer derivatives too.
/// (c) means camera space. Numbers not listed here are available for arbitrary
/// named custom vertex attribute data; use the name2getvector function.
///
struct State_sym
{
    enum Id {
        ORG                             = 0,    // ray origin (c)
        ORG_DX                          = 1,    // ray origin (c)
        ORG_DY                          = 2,    // ray origin (c)
        DIR                             = 3,    // ray direction (c)
        DIR_DX                          = 4,    // ray direction (c)
        DIR_DY                          = 5,    // ray direction (c)
        POINT                           = 6,    // intersection point (c)
        POINT_DX                        = 7,    // intersection point (c)
        POINT_DY                        = 8,    // intersection point (c)
        NORMAL                          = 9,    // interpolated normal (c)
        NORMAL_DX                       = 10,   // interpolated normal (c)
        NORMAL_DY                       = 11,   // interpolated normal (c)
        NORMAL_GEOM                     = 12,   // geometric normal (c)
        NORMAL_GEOM_DX                  = 13,   // geometric normal (c)
        NORMAL_GEOM_DY                  = 14,   // geometric normal (c)
        MOTION                          = 15,   // tangential motion vector (c)
        MOTION_DX                       = 16,   // tangential motion vector (c)
        MOTION_DY                       = 17,   // tangential motion vector (c)
        UV                              = 18,   // parametric uv coord
        UV_DX                           = 19,   // parametric uv coord
        UV_DY                           = 20,   // parametric uv coord
        RASTER                          = 21,   // raster coordinates
        RASTER_DX                       = 22,   // raster coordinates
        RASTER_DY                       = 23,   // raster coordinates
        RAY_LENGTH                      = 24,   // ray length
        RAY_LENGTH_DX                   = 25,   // ray length dx
        RAY_LENGTH_DY                   = 26,   // ray length dy
        RAY_LENGTH_DIFF                 = 27,   // ray length diff
        DOT_ND                          = 28,   // normal.dir
        DOT_ND_DX                       = 29,   // normal.dir dx
        DOT_ND_DY                       = 30,   // normal.dir dy
        DOT_ND_DIFF                     = 31,   // normal.dir diff
        BACKSIDE                        = 32,   // backside
        REFRACTED_IOR                   = 33,   // refracted ior
        INCIDENT_IOR                    = 34,   // incident ior
        TIME                            = 35,   // time
        IMPORTANCE                      = 36,   // importance
        TRACE_DEPTH                     = 37,   // trace depth
        VOLUME_INPUT                    = 38,   // volume input
        VOLUME_INPUT_DX                 = 39,   // volume input
        VOLUME_INPUT_DY                 = 40,   // volume input
        INSIDE                          = 41,   // inside
        TEXTURE                         = 1000, // texture coords
        TEXTURE_DX                      = 2000, // texture coords
        TEXTURE_DY                      = 3000, // texture coords
        TEXTURE_TANGENT                 = 4000, // texture tangent
        TEXTURE_TANGENT_DX              = 5000, // texture tangent
        TEXTURE_TANGENT_DY              = 6000, // texture tangent
        TEXTURE_BINORMAL                = 7000, // texture binormal
        TEXTURE_BINORMAL_DX             = 8000, // texture binormal
        TEXTURE_BINORMAL_DY             = 9000, // texture binormal
        TEXTURE_DU                      = 10000,// texture coords
        TEXTURE_DU_DX                   = 11000,// texture coords
        TEXTURE_DU_DY                   = 12000,// texture coords
        TEXTURE_DV                      = 13000,// texture coords
        TEXTURE_DV_DX                   = 14000,// texture coords
        TEXTURE_DV_DY                   = 15000,// texture coords
        TEXTURE_NUM                     = 256,  // maximum texture index
        LIGHT_POINT                     = 50000,// light point
        LIGHT_POINT_DX                  = 50001,// light point dx
        LIGHT_POINT_DY                  = 50002,// light point dy
        LIGHT_DIRECTION                 = 50003,// light direction
        LIGHT_DIRECTION_DX              = 50004,// light direction dx
        LIGHT_DIRECTION_DY              = 50005,// light direction dy
        LIGHT_NORMAL                    = 50006,// light normal
        LIGHT_NORMAL_DX                 = 50007,// light normal dx
        LIGHT_NORMAL_DY                 = 50008,// light normal dy
        LIGHT_UV                        = 50009,// light uv
        LIGHT_UV_DX                     = 50010,// light uv dx
        LIGHT_UV_DY                     = 50011,// light uv dy
        LIGHT_SPREAD                    = 50012,// light spread
        LIGHT_TYPE                      = 50013,// light type
        LIGHT_DOT_NL                    = 50015,// light dot nl
        LIGHT_DOT_NL_DX                 = 50016,// light dot nl dx
        LIGHT_DOT_NL_DY                 = 50017,// light dot nl dy
        LIGHT_DISTANCE                  = 50018,// light distance
        LIGHT_DISTANCE_DX               = 50019,// light distance dx
        LIGHT_DISTANCE_DY               = 50020,// light distance dy
        LIGHT_TO_SURFACE                = 50021,// light to surface
        LIGHT_TO_SURFACE_DX             = 50022,// light to surface dx
        LIGHT_TO_SURFACE_DY             = 50023,// light to surface dy
        LIGHT_SPREAD_COS                = 50024,// light spread cos
        LIGHT_DISTANCE_LIMIT            = 50025,// light distance limit
        LIGHT_AREA                      = 50026,// light area
        LIGHT_CONTRIBUTION              = 50028,// light color contribution
        LIGHT_TEXTURE                   = 51000,// light texture coords
        LIGHT_TEXTURE_DX                = 52000,// light texture dx
        LIGHT_TEXTURE_DY                = 53000,// light texture dy
        LIGHT_TEXTURE_TANGENT           = 54000,// light texture tangent
        LIGHT_TEXTURE_TANGENT_DX        = 55000,// light texture tangent dx
        LIGHT_TEXTURE_TANGENT_DY        = 56000,// light texture tangent dy
        LIGHT_TEXTURE_BINORMAL          = 57000,// light texture tangent
        LIGHT_TEXTURE_BINORMAL_DX       = 58000,// light texture tangent dx
        LIGHT_TEXTURE_BINORMAL_DY       = 59000,// light texture tangent dy
        LIGHT_TEXTURE_DU                = 60000,// light texture coords
        LIGHT_TEXTURE_DU_DX             = 61000,// light texture coords
        LIGHT_TEXTURE_DU_DY             = 62000,// light texture coords
        LIGHT_TEXTURE_DV                = 63000,// light texture coords
        LIGHT_TEXTURE_DV_DX             = 64000,// light texture coords
        LIGHT_TEXTURE_DV_DY             = 65000,// light texture coords
        LIGHT_TEXTURE_NUM               = 256,  // maximum texture index
        // The EXTENDED_STATE_SYMS allows derived classes to define
        // additional enums which may not be available in all base classes.
        // Except for the ALIGN enum no other enums should have a greater
        // value than EXTENDED_STATE_SYMS.
        EXTENDED_STATE_SYMS             = 0x80000000, // start of extensions
        ALIGN                           = 0xFFFFFFFF// force to be 32bits
    };
};


//-----------------------------------------------------------------------------
///
/// Shader input or output or state variable definition.
///
/// A variable can be either a state variable or a shader input or output.
/// In the first case we can use an enum to refer to it, while
/// in the second we have to use a string, since names are not
/// defined in advance.
///
struct Variable_def_struct
{
    enum Type {
        STATE_VAR,
        SHADER_VAR,
        UNDEFINED       = 0xFFFFFFFF
    };

    Type                m_type;                 // type of variable
    union
    {
        State_sym::Id   m_state;                // state var
        const char*     m_shader;               // shader var
    }                   m_var;                  // variable name
};


/// Constructor for easy \c Variable_def_struct creation.
struct Variable_def : public Variable_def_struct
{
    // constructor
    inline Variable_def();

    // state var constructor
    inline Variable_def(
        State_sym::Id s);                       // state var

    // shader var constructor
    inline Variable_def(
        const char* s);                         // shader var
};


/// Shader input or output or state variable.
template <typename Result_type>
struct Variable_struct
{
    Variable_def_struct m_def;                  ///< identifier
    Type_code::Id       m_type;                 ///< type
    Result_type         m_value;                ///< value
};


/// Constructor for easy \c Variable_struct creation.
template <typename Result_type>
struct Variable : public Variable_struct<Result_type>
{
    inline Variable(
            const Variable_def_struct&  d,
            Type_code::Id               tp,
            Result_type                 val);
};


typedef Variable_struct<const void*> Variable_in_struct; // input
typedef Variable<const void*> Variable_in;               // input
typedef Variable_struct<void*> Variable_out_struct;      // output
typedef Variable<void*> Variable_out;                    // output


/// Shader results for ray tracing.
struct Gather_result_struct
{
    Tag                  m_shader;       ///< shader or null tag for intersected shader
    Variable_out_struct* m_outputs;      ///< array of requested outputs
    Uint32               m_count;        ///< length of outputs array
};


struct Gather_result : public Gather_result_struct
{
    inline Gather_result(
            Tag                         tag,
            Uint32                      out_count,
            Variable_out_struct*        outputs)
    {
        m_shader = tag;
        m_outputs = outputs;
        m_count = out_count;
    }
};


/// Shader inputs and results for explicit shader invocation.
struct Shader_io_struct
{
    Tag                  m_shader;       ///< shader tag
    Variable_in_struct*  m_inputs;       ///< inputs to be overwritten
    Uint32               m_inputs_count; ///< length of inputs array
    Variable_out_struct* m_outputs;      ///< requested outputs
    Uint32               m_outputs_count;///< length of outputs array
};


/// Struct member/array element access representation
struct Data_member_struct
{
    enum Type {
        TYPE_ARRAY_ELEMENT,
        TYPE_STRUCT_MEMBER,
        UNDEFINED       = 0xFFFFFFFF
    };

    Type m_type;
    union {
        Uint32          m_index;
        const char*     m_field;
    };
};


struct Data_member : public Data_member_struct
{
    Data_member(const char* name)
    {
        m_type = TYPE_STRUCT_MEMBER;
        m_field = name;
    }

    Data_member(Uint32 idx)
    {
        m_type = TYPE_ARRAY_ELEMENT;
        m_index = idx;
    }
};


//-----------------------------------------------------------------------------
///
/// the state passed to shaders. This is the main gateway into the renderer for
/// shaders. Note that users do not see this state, it is designed for the
/// convenience of the MetaSL compiler back-end.
///
struct State
{
    // sources of user scene data
    enum Data_source {
        INSTANCE_DATA,
        OBJECT_DATA,
        OPTIONS_DATA,
        PRIMITIVE_DATA,
        DATA_ALIGN                      = 0xFFFFFFFF// force to be 32bits
    };

    // types of scene data
    enum Data_type {
        SCENE_DATA,
        SCENE_ATTR_BBOX_MIN,
        SCENE_ATTR_BBOX_MAX,
        SCENE_ALIGN                     = 0xFFFFFFFF// force to be 32bits
    };


    //--------------------------------- state variable access -----------------
    // read access methods for the intersection state. (c) = camera space

    virtual Sint32      get_int(                // get integer value
        State_sym::Id v) const = 0;             // return this value

    virtual Scalar      get_scalar(             // get scalar value
        State_sym::Id v) const = 0;             // return this vector

    virtual Vector2     get_vector2(            // get vector value
        State_sym::Id v) const = 0;             // return this vector

    virtual Vector3     get_vector3(            // get vector value
        State_sym::Id v) const = 0;             // return this vector

    virtual Vector4     get_vector4(            // get vector value
        State_sym::Id v) const = 0;             // return this vector

    virtual Uint        get_dim(                // numb. of dimensions, 0=undef
        State_sym::Id v) const = 0;             // of this vector

    // texture tangent space
    virtual Matrix4x4d     get_tangent_space(
                        Uint index) const = 0;  // texture index

    // return ray flags, the union of ray_type, ray_history and ray_dispersal
    // groups. Each of these can then be retrieved by calling the appropriate
    // utility functions in shader_utils.h: get_ray_type( ray_flags ),
    // is_ray_history_group( ray_flags, group ), etc.
    virtual Ray_flags   get_ray_flags() const = 0;

    // get ray differential
    virtual void get_ray_diff(
        RDIFF::Ray_diff_struct* ray) const = 0; // ray diff

    // get trace depth
    virtual Uint32 get_trace_depth(
        Ray_type) const = 0;                    // ray flags

    // write access methods for the intersection state.

    virtual void        set_int(                // set integer value
        State_sym::Id   v,                      // state var
        Sint32          val) = 0;               // value

    virtual void        set_scalar(             // set scalar value
        State_sym::Id   v,                      // state var
        Scalar          val) = 0;               // value

    virtual void        set_vector2(            // set vector value
        State_sym::Id   v,                      // state var
        const Vector2&  val) = 0;               // value

    virtual void        set_vector3(            // set vector value
        State_sym::Id   v,                      // state var
        const Vector3&  val) = 0;               // value

    virtual void        set_vector4(            // set vector value
        State_sym::Id   v,                      // state var
        const Vector4&  val) = 0;               // value

    //--------------------------------- lighting evaluators -------------------

    // Use the local BRDF to evaluate the direct light contribution to the surface
    // color. This function loops over some or all lights, and evaluates the
    // BRDF for each light sample and returns the total result.
    // The first three boolean parameters determine which components to
    // evaluate. If the corresponding result pointers are non-NULL, the
    // individual results are stored there. If the \c sum pointer is
    // non-NULL, the sum of all computed components is stored there.
    // Note that the computed results overwrite the previous content of
    // the corresponding result variables, i.e. the contribution is
    // _not_ added to the previous value.
    virtual void direct_light(
        bool compute_diffuse,                   // compute diffuse component if true
        bool compute_glossy,                    // compute glossy component if true
        bool compute_specular,                  // compute specular component if true
        COLOR::Spectrum_struct* diffuse,        // diffuse lighting if !NULL
        COLOR::Spectrum_struct* glossy,         // glossy lighting if !NULL
        COLOR::Spectrum_struct* specular,       // specular lighting if !NULL
        COLOR::Spectrum_struct* sum)            // sum of computed components if !NULL
        const = 0;

    // Use the local BRDF to evaluate the direct light contribution to the surface
    // color. This function only considers a single light sample using the given
    // light iterator.
    // The first three boolean parameters determine which components to
    // evaluate. If the corresponding result pointers are non-NULL, the
    // individual results are stored there. If the \c sum pointer is
    // non-NULL, the sum of all computed components is stored there.
    // Note that the computed results overwrite the previous content of
    // the corresponding result variables, i.e. the contribution is
    // _not_ added to the previous value.
    virtual void direct_light(
        const Light_iterator_struct& light_iterator,
        bool compute_diffuse,             // compute diffuse component if true
        bool compute_glossy,              // compute glossy component if true
        bool compute_specular,            // compute specular component if true
        COLOR::Spectrum_struct* diffuse,  // diffuse lighting if !NULL
        COLOR::Spectrum_struct* glossy,   // glossy lighting if !NULL
        COLOR::Spectrum_struct* specular, // specular lighting if !NULL
        COLOR::Spectrum_struct* sum)      // sum of computed components if !NULL
        const = 0;

    // Use the local BRDF to evaluate the indirect light contribution to the surface
    // color. The first three boolean parameters determine which components to
    // evaluate. If the corresponding result pointers are non-NULL, the
    // individual results are stored there. If the \c sum pointer is
    // non-NULL, the sum of all computed components is stored there.
    // Note that the computed results overwrite the previous content of
    // the corresponding result variables, i.e. the contribution is
    // _not_ added to the previous value.
    virtual void indirect_light(
        bool compute_diffuse,             // compute diffuse component if true
        bool compute_glossy,              // compute glossy component if true
        bool compute_specular,            // compute specular component if true
        COLOR::Spectrum_struct* diffuse,  // diffuse lighting if !NULL
        COLOR::Spectrum_struct* glossy,   // glossy lighting if !NULL
        COLOR::Spectrum_struct* specular, // specular lighting if !NULL
        COLOR::Spectrum_struct* sum)      // sum of computed components if !NULL
        const = 0;

    //--------------------------------- raytracing methods --------------------

    // trace a ray immediately, and return intersection info (unless false is
    // returned, in case the ray hit nothing, not even an environment, or some
    // trace depth was exhausted).
    virtual bool trace(
        const RDIFF::Ray_diff_struct&   ray,           // ray differential
        const Trace_options_struct&     opt,           // tracing options
        Uint32                          n_requests,    // number of outputs
        const Gather_result_struct*     requests)      // outputs
        const = 0;

#ifdef METASL_EXP
    // trace a deferred ray. If the ray hits something later, the result will
    // be multiplied by the passed weight, and added to the frame buffer.
    virtual void trace_deferred(
        const RDIFF::Ray_diff_struct    &ray,           // ray differential
        const Trace_options_struct      &opt,           // tracing options
        const COLOR::Color_struct       weight)         // mult. factor
        const = 0;

    // trace a deferred shadow ray for the given light sample. If the ray hits
    // something later, the result will be multiplied by the passed weight,
    // and subtracted from the frame buffer.
    virtual void shadow_deferred(
        const Light_iterator            &it,            // current light
        const COLOR::Color_struct       weight)         // mult. factor
        const = 0;
#endif

    // get ambient occlusion of the current point. 0=not occluded, 1=fully
    // occluded.
    virtual Scalar occlusion(
        const Occlusion_options_struct  &opt)   // tracing options
        const = 0;

    // get irradiance of the current point.
    virtual COLOR::Spectrum_struct irradiance(
        const Irradiance_options_struct &opt)   // tracing options
        const = 0;

    // get shadowing factor
    virtual COLOR::Spectrum_struct shadowing() const = 0;

    // get a parameter of the invoking shader, i.e. the shader
    // which created this state.
    // For example, one can call this function within a light
    // shader to query an input parameter of the shader which
    // caused the invocation of the light shader itself.
    virtual bool get_shader_parameter(
        const char*     name,                   // parameter name
        Type_code::Id   type,                   // parameter type
        void*           value) const = 0;       // parameter value

    // invoke the given shader.
    // This function calls the shader identified by \c args->m_shader.
    // If \c args->m_inputs is non-null and not empty, the given inputs will
    // overwrite the shader's instance parameters. Implementations do not need
    // to verify that the overridden inputs are nonuniform.
    // The shader's outputs are stored in the corresponding \c args->m_outputs
    // array. Outputs which are requested by \c args->m_outputs but do not match
    // any of the shader's outputs will not be modified.
    // This function returns true if the shader was found and executed successfully.
    virtual bool call_shader(
        Shader_io_struct*       args            // shader inputs and result slots
        ) const = 0;

    //--------------------------------- space transforms ----------------------
    // point transformations use the full matrix including translation.
    virtual const Matrix4x4d &get_internal_to_world() const = 0;
    virtual const Matrix4x4d &get_internal_to_object() const = 0;
    virtual const Matrix4x4d &get_internal_to_camera() const = 0;
    virtual const Matrix4x4d &get_internal_to_raster() const = 0;
    virtual const Matrix4x4d &get_world_to_internal() const = 0;
    virtual const Matrix4x4d &get_world_to_object() const = 0;
    virtual const Matrix4x4d &get_world_to_camera() const = 0;
    virtual const Matrix4x4d &get_world_to_raster() const = 0;
    virtual const Matrix4x4d &get_object_to_internal() const = 0;
    virtual const Matrix4x4d &get_object_to_world() const = 0;
    virtual const Matrix4x4d &get_object_to_camera() const = 0;
    virtual const Matrix4x4d &get_object_to_raster() const = 0;
    virtual const Matrix4x4d &get_camera_to_internal() const = 0;
    virtual const Matrix4x4d &get_camera_to_world() const = 0;
    virtual const Matrix4x4d &get_camera_to_object() const = 0;
    virtual const Matrix4x4d &get_camera_to_raster() const = 0;
    virtual const Matrix4x4d &get_raster_to_internal() const = 0;
    virtual const Matrix4x4d &get_raster_to_world() const = 0;
    virtual const Matrix4x4d &get_raster_to_object() const = 0;
    virtual const Matrix4x4d &get_raster_to_camera() const = 0;
    virtual const Matrix4x4d &get_internal_to_light() const = 0;
    virtual const Matrix4x4d &get_light_to_internal() const = 0;

    // standard coordinate systems
    typedef Uint Coordsystem;
    static const Coordsystem COORD_WORLD     = 0;
    static const Coordsystem COORD_OBJECT    = 1;
    static const Coordsystem COORD_CAMERA    = 2;
    static const Coordsystem COORD_RASTER    = 3;
    static const Coordsystem COORD_LIGHT     = 4;
    static const Coordsystem COORD_UNDEFINED = (Coordsystem)-1;

    // transform point
    virtual Vector3 transform_point(
        Coordsystem from,                       // from space
        Coordsystem to,                         // to space
        const Vector3 &point) const = 0;        // the point to transform

    // transform vector
    virtual Vector3 transform_vector(
        Coordsystem from,                       // from space
        Coordsystem to,                         // to space
        const Vector3 &vec) const = 0;          // the vector to transform

    // transform normal
    virtual Vector3 transform_normal(
        Coordsystem from,                       // from space
        Coordsystem to,                         // to space
        const Vector3 &normal) const = 0;       // the normal to transform

    // for user-defined coordinate systems
    virtual const Matrix4x4d get_transform(
        Coordsystem     from,           // from the space defined by this key
        Coordsystem     to) const = 0;  // to the space defined by this key

    // map a coordinate system name to a coordinate key
    virtual Coordsystem get_coordsystem(
        const char      *name) const = 0;// name of custom coordinate system

    // get internal space
    virtual Coordsystem get_internal_coordsystem() const = 0;

    //--------------------------------- texture utilities --------------------

    // Lookup 1D texture.
    virtual COLOR::Color_struct tex1D(
        Tag tex,                            // the texture to lookup.
        const Scalar &coord) const = 0;    // the coordinate to lookup.

    // Lookup 1D texture.
    virtual COLOR::Color_struct tex1D(
        Tag tex,                            // the texture to lookup.
        const Scalar &coord,               // the coordinate to lookup.
        const Scalar &coord_dx,            // the x derivative.
        const Scalar &coord_dy) const = 0; // the y derivative.

    // Lookup 2D texture.
    virtual COLOR::Color_struct tex2D(
        Tag tex,                            // the texture to lookup.
        const Vector2 &coord) const = 0;   // the coordinate to lookup.

    // Lookup 2D texture.
    virtual COLOR::Color_struct tex2D(
        Tag tex,                            // the texture to lookup.
        const Vector2 &coord,              // the coordinate to lookup.
        const Vector2 &coord_dx,           // the x derivative.
        const Vector2 &coord_dy) const = 0;// the y derivative.

    // Lookup 3D texture.
    virtual COLOR::Color_struct tex3D(
        Tag tex,                            // the texture to lookup.
        const Vector3 &coord) const = 0;   // the coordinate to lookup.

    // Lookup 3D texture.
    virtual COLOR::Color_struct tex3D(
        Tag tex,                            // the texture to lookup.
        const Vector3 &coord,              // the coordinate to lookup.
        const Vector3 &coord_dx,           // the x derivative.
        const Vector3 &coord_dy) const = 0;// the y derivative.

    // Lookup CUBE texture.
    virtual COLOR::Color_struct texCUBE(
        Tag tex,                            // the texture to lookup.
        const Vector3 &coord) const = 0;   // the coordinate to lookup.

    // Lookup CUBE texture.
    virtual COLOR::Color_struct texCUBE(
        Tag tex,                            // the texture to lookup.
        const Vector3 &coord,              // the coordinate to lookup.
        const Vector3 &coord_dx,           // the x derivative.
        const Vector3 &coord_dy) const = 0;// the y derivative.

    //----------------------------------- misc --------------------------------
    // get a frame context
    virtual Frame* get_frame() const = 0;

    // get a sampling context
    virtual Sampling_context *get_sampler() const = 0;

    // get a shading context
    virtual Factory* get_factory() const = 0;

    // get a logger
    virtual Log* get_log() const = 0;

    // add a reference to this object
    virtual void add_ref() = 0;

    // delete this
    virtual void release() = 0;

    //----------------------------------- light profile ------------------------
    // Lookup a light profile using phi and theta in horizontal and vertical direction
    virtual COLOR::Spectrum_struct lookup_light_profile(
        Tag             light_profile,                  // The light profile to lookup
        const Vector2& angles,                         // Angles in horizontal and vertical dir
        bool            normalized = true) const = 0;   // Return candela or normalized values
    // Lookup a light profile using the light-to-surface
    // direction to derive phi and theta
    virtual COLOR::Spectrum_struct lookup_light_profile(
        Tag             light_profile,                // The light profile to lookup
        bool            normalized = true) const = 0; // Return candela or normalized values

    //----------------------------------- data ---------------------------------

    // get ray data
    virtual bool get_ray_data(
        const char              *name,              // name
        const Type_code::Id     type,               // type
        Uint32                  size,               // size
        void                    *value) const = 0;  // value

    // clear ray data; if a null pointer is given all the data is cleared.
    virtual void clear_ray_data(
        const char              *name = 0) = 0;     // name

    // check if scene data exists
    virtual bool exists_scene_data(const Data_source source) const = 0;

    // accesses scene data
    //
    // This function returns \c true if the requested data element was found
    // and its type matches. Otherwise, it returns \c false. In that case, the
    // memory pointed to by \p value will not be modified.
    //
    // Also see the free functions \c get_scene_data and \c scene_data.
    virtual bool get_scene_data(
            const Data_source   source,
            const Data_type     data_type,
            Uint32              acc_count,
            const Data_member_struct* accessors,
            const Type_code::Id type,
            const Uint32        size,
            void* const         value) const = 0;


    //------------------------------ material definitions ----------------------

    // Get the material definition at the current position.
    //
    // If the current sample is a light sample, return the material def
    // of the calling shader, if present.
    virtual const Material_def* get_material_def() const = 0;

    // Get the light definition for the current sample.
    virtual const Material_def* get_light_def() const = 0;


#ifdef MI_PRODUCT_RAY
    // access the mental ray shader state
    virtual miState* get_miState() = 0;

    // get storage for multiple shader outputs
    virtual class Mr_gather_output* get_gather_output() = 0;

    // set volume input
    virtual void set_volume_input(const COLOR::Color_struct& vi) = 0;
#endif


};


//-----------------------------------------------------------------------------
///
/// Camera interface symbols
///
struct Camera_sym
{
    enum Id
    {
        ORTHOGRAPHIC            = 0,            // orthographic
        FOCAL_LENGTH            = 1,            // focal length (distance to viewing plane)
        APERTURE                = 2,            // aperture
        ASPECT_RATIO            = 3,            // aspect ratio
        CAMERA_OFFSET           = 4,            // camera offset
        DOF_FOCUS               = 5,            // distance to focus plane
        DOF_RADIUS              = 6,            // dof radius
        NEAR_CLIP               = 7,            // near clip
        FAR_CLIP                = 8,            // far clip
        ALIGN                   = 0xFFFFFFFF    // force to be 32bits
    };
};


///
/// Camera interface
///
struct Camera
{
    // get integer value
    virtual Sint32      get_int(
        Camera_sym::Id v) const = 0;            // return this value

    // get vector value
    virtual Scalar      get_scalar(
        Camera_sym::Id v) const = 0;            // return this vector

    // get vector value
    virtual Vector2     get_vector2(
        Camera_sym::Id v) const = 0;            // return this vector

    // get vector value
    virtual Vector3     get_vector3(
        Camera_sym::Id v) const = 0;            // return this vector

    // get vector value
    virtual Vector4     get_vector4(
        Camera_sym::Id v) const = 0;            // return this vector

    // get transformations
    virtual const Matrix4x4d &get_world_to_camera() const = 0;
    virtual const Matrix4x4d &get_camera_to_world() const = 0;

    // add a reference to this object
    virtual void add_ref() = 0;

    // delete this
    virtual void release() = 0;
};


//-----------------------------------------------------------------------------
///
/// Frame interface symbols
///
/// Available at FRAME_INIT/EXIT time and from the shader state.
///
struct Frame_sym
{
    enum Id
    {
        IMAGE_RESOLUTION_X      = 8,            // image width
        IMAGE_RESOLUTION_Y      = 9,            // image height
        WINDOW_LEFT             = 10,           // window left
        WINDOW_RIGHT            = 11,           // window right
        WINDOW_TOP              = 12,           // window top
        WINDOW_BOTTOM           = 13,           // window bottom
        ANIMATION_FRAME         = 0,            // animation frame
        ANIMATION_TIME          = 1,            // animation time
        SHUTTER_TIME            = 2,            // shutter time
        SHUTTER_DURATION        = 3,            // shutter duration
        SHUTTER_POSITION        = 4,            // shutter position
        SHUTTER_OPEN            = 5,            // shutter open
        SHUTTER_CLOSE           = 6,            // shutter close
        ALIGN                   = 0xFFFFFFFF    // force to be 32bits
    };
};


///
/// Frame interface
///
/// Available at FRAME_INIT/EXIT time and from the shader state.
///
struct Frame
{
    // get integer value
    virtual Sint32      get_int(
        Frame_sym::Id v) const = 0;             // return this value

    // get vector value
    virtual Scalar      get_scalar(
        Frame_sym::Id v) const = 0;             // return this vector

    // get vector value
    virtual Vector2     get_vector2(
        Frame_sym::Id v) const = 0;             // return this vector

    // get vector value
    virtual Vector3     get_vector3(
        Frame_sym::Id v) const = 0;             // return this vector

    // get vector value
    virtual Vector4     get_vector4(
        Frame_sym::Id v) const = 0;             // return this vector

    virtual const Matrix4x4d &get_world_to_raster() const = 0;
    virtual const Matrix4x4d &get_camera_to_raster() const = 0;
    virtual const Matrix4x4d &get_raster_to_world() const = 0;
    virtual const Matrix4x4d &get_raster_to_camera() const = 0;

    // get camera interface
    virtual Camera* get_camera() const = 0;

    // add a reference to this object
    virtual void add_ref() = 0;

    // delete this
    virtual void release() = 0;
};



//-----------------------------------------------------------------------------
//
// ray types. Multiple flags can be OR-ed: pick at most one from groups marked
// ONE, and zero or more from groups that are marked MULT. Transparency is a
// special case of specular refraction where the ray direction cannot change.
// Shadow ray directions cannot change either. Some of these (light, displace)
// do not actually describe rays but tell the shader in what context it is
// called.
// This enum tells a shader what has happened to the ray since it was emitted,
// and controls the volume stack and extinction at the trace depth limit.
//
// Combination constraints:
// RAY_TRANSPARENT: always specular, never glossy or diffuse.
// RAY_OCCLUSION: always diffuse, never specular or glossy; always RAY_SHADER_SURFACE
//
                                                //----- ONE: ray type group
const Ray_flags RAY_EYE                 = 0x000001;     // first-gen ray or photon
const Ray_flags RAY_TRANSPARENT         = 0x000002;     // transparency ray into object
const Ray_flags RAY_REFRACT             = 0x000004;     // refraction into object
const Ray_flags RAY_REFLECT             = 0x000008;     // reflection away from object
const Ray_flags RAY_SHADOW              = 0x000010;     // shadow ray to illum. point
const Ray_flags RAY_OCCLUSION           = 0x000020;     // ambient occlusion
const Ray_flags RAY_ENVIRONMENT         = 0x000040;     // ray to environment
const Ray_flags RAY_ABSORB              = 0x000080;     // photon is absorbed (RIP)
                                                //----- MULT: dispersal group
const Ray_flags RAY_SPECULAR            = 0x000100;     // specular transp/refl/refr
const Ray_flags RAY_GLOSSY              = 0x000200;     // glossy   transp/refl/refr
const Ray_flags RAY_DIFFUSE             = 0x000400;     // diffuse  transp/refl/refr
                                                //----- ONE: shader type group
const Ray_flags RAY_SHADER_SURFACE      = 0x000800;     // surface shader
const Ray_flags RAY_SHADER_VOLUME       = 0x001000;     // volume shader
const Ray_flags RAY_SHADER_PHOTON       = 0x002000;     // globillum or caustic photon
const Ray_flags RAY_SHADER_LIGHT        = 0x004000;     // light shader call
const Ray_flags RAY_SHADER_DISPLACE     = 0x008000;     // displacement shader call
const Ray_flags RAY_SHADER_ENVIRONMENT  = 0x010000;     // ray to environment
const Ray_flags RAY_SHADER_LENS         = 0x020000;     // lens shader
                                                //----- MULT: ray history group
const Ray_flags RAY_LIGHTMAP            = 0x040000;     // displacement shader call
const Ray_flags RAY_FINALGATHER         = 0x080000;     // final gather ray
const Ray_flags RAY_HULL                = 0x100000;     // passed through hull surface
const Ray_flags RAY_VOLUME              = 0x200000;     // starts in empty space


//-----------------------------------------------------------------------------
/// Container for ray data
struct Ray_data
{
    // set data
    virtual void set(
        const char                      *name,      // name
        const Type_code::Id             type,       // type
        Uint32                          size,       // size
        void                            *value) = 0;// value

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;
};


///
/// the trace functions may carry additional information. Pass an instance of
/// this class; this is more flexible than loads of method arguments.
///
struct Trace_options_struct
{
    double              m_near;                 // start intersect at this dist
    double              m_far;                  // stop intersect at this dist
    float               m_importance;           // importance factor
    bool                m_enable_environment;   // enable environment shader if true
    Ray_type            m_ray_type;             // ray type
    Ray_flags           m_ray_flags;            // ray flags
    Ray_data*           m_ray_data;             // ray data
};


///
/// the trace functions may carry additional information. Pass an instance of
/// this class; this is more flexible than loads of method arguments.
/// TBD: should this be a "Tracer" class containing a trace method? In that
/// case we need to decide here how deferred tracing results are specified.
///
struct Trace_options : public Trace_options_struct
{
    // Ctor without ray data.
    // Note that instances which were created through this ctor cannot
    // use \c set_data.
    inline Trace_options();

    // Ctor with ray data
    inline Trace_options(const Factory* f);

    // Copy constructor.
    inline Trace_options(
        const Trace_options &other);                // The Trace_options to copy.

    // Copy constructor.
    inline Trace_options &operator=(
        const Trace_options &other);                // The Trace_options to copy.

    // set near distance
    inline void set_near(
        double v);                              // near distance

    // set far distance
    inline void set_far(
        double v);                              // far distance

    // set ray type
    inline void set_ray_type(
        Ray_flags v);                           // ray type

    // set ray group
    inline void set_ray_dispersal_group(
        Ray_flags v);                           // ray group

    // set importance
    inline void set_importance(
        float v);                               // importance

    // set importance
    inline void set_importance(
        const COLOR::Color_struct& c);          // importance

    // set importance
    inline void set_importance(
        const COLOR::Spectrum_struct& s);       // importance

    // toggle usage of the environment shader
    inline void enable_environment(
        bool enable_environment);               // enable environment shader if true

    // set ray data
    inline void set_data(
        const char                      *name,      // name
        const Type_code::Id             type,       // type
        Uint32                          size,       // size
        void                            *value);    // value

private:

    void set_defaults();

    Smart_ptr<Ray_data> m_data_access;
};


///
/// the occlusion functions may carry additional information. Pass an instance
/// of this class; this is more flexible than loads of method arguments.
///
struct Occlusion_options_struct
{
    double              m_near;                 // start intersect at this dist
    double              m_far;                  // stop intersect at this dist
    float               m_importance;           // importance factor
    Vector3             m_axis;                 // cone axis
    float               m_angle;                // cone angle
    float               m_angle_exp;            // phong exponent
};


///
/// the occlusion functions may carry additional information. Pass an instance
/// of this class; this is more flexible than loads of method arguments.
///
struct Occlusion_options : public Occlusion_options_struct
{
    inline Occlusion_options();                 // supply no-op defaults

    // Copy constructor.
    inline Occlusion_options(
        const Occlusion_options &other);    // The Occlusion_options to copy.

    // Copy constructor.
    inline Occlusion_options &operator=(
        const Occlusion_options &other);    // The Occlusion_options to copy.

    // set near distance
    inline void set_near(
        double v);                              // near distance

    // set far distance
    inline void set_far(
        double v);                              // near distance

    // set importance
    inline void set_importance(
        float v);                               // importance

    // set importance
    inline void set_importance(
        const COLOR::Color_struct& c);          // importance

    // set importance
    inline void set_importance(
        const COLOR::Spectrum_struct& s);       // importance

    // set cone
    inline void set_cone(
        const Vector3& axis = Vector3(0,0,0),   // cone axis
        const float angle = 90.0f,              // cone angle
        const float angle_exp = 1.0f);          // phong exponent
};


///
/// the irradiance function may carry additional information. Pass an instance
/// of this class; this is more flexible than loads of method arguments.
///
struct Irradiance_options_struct
{
    double              m_near;                 // start intersect at this dist
    double              m_far;                  // stop intersect at this dist
    float               m_importance;           // importance factor
    Vector3             m_axis;                 // cone axis
    float               m_angle;                // cone angle
    float               m_angle_exp;            // phong exponent
};


///
/// the irradiance function may carry additional information. Pass an instance
/// of this class; this is more flexible than loads of method arguments.
///
struct Irradiance_options : public Irradiance_options_struct
{
    inline Irradiance_options();                // supply no-op defaults

    // Copy constructor.
    inline Irradiance_options(
        const Irradiance_options &other);   // The Irradiance_options to copy.

    // Copy constructor.
    inline Irradiance_options &operator=(
        const Irradiance_options &other);   // The Irradiance_options to copy.

    // set near distance
    inline void set_near(
        double v);                              // near distance

    // set far distance
    inline void set_far(
        double v);                              // near distance

    // set importance
    inline void set_importance(
        float v);                               // importance

    // set importance
    inline void set_importance(
        const COLOR::Color_struct& c);          // importance

    // set importance
    inline void set_importance(
        const COLOR::Spectrum_struct& s);       // importance

    // set cone
    inline void set_cone(
        const Vector3& axis = Vector3(0,0,0),   // cone axis
        const float angle = 90.0f,              // cone angle
        const float angle_exp = 1.0f);          // phong exponent
};



//------------------------------------- texture -------------------------------

template <typename V> inline Uint dimension()
{ return V::DIMENSION; }
template <> inline Uint dimension<float>()
{ return 1; }
template <> inline Uint dimension<double>()
{ return 1; }
template <> inline Uint dimension<COLOR::Color_struct>()
{ return COLOR::Color::SIZE; }
template <> inline Uint dimension<COLOR::Spectrum_struct>()
{ return COLOR::Spectrum::SIZE; }


///
/// a texture sampler knows a texture in the scene database and how to sample
/// it, and provides a lookup function for sampling. Note that textures carry
/// remapping information, so that the coordinate is usually just a texture
/// space coordinate from get_vector.Note that get_components and get_dimension
/// can return values that differ from TR and TC, respectively, this leads to
/// automatic conversions. Conversions allow a shader to function if the scene
/// supplies a wrong image; this is not under the control of the shader writer.
///
template<typename TR,           // result type: Scalar, Vector[234], Color
         typename TC>           // coordinate type: Scalar, Vector2, Vector3
struct Texture_sampler
{
    // number of components of a texture: 1 for Scalar .. 4 for Color/Vector4
    static Uint get_components() { return dimension<TR>(); }

    // number of dimensions of a texture. 2 for 2D (UV) and 3 for 3D (XYZ).
    static Uint get_dimension() { return dimension<TC>(); }

    // non-antialiased sample function.
    virtual TR lookup(
        const TC        &coord) const = 0;      // texture coordinate

    // sample function.
    virtual TR lookup(
        const TC        &coord,                 // texture coordinate
        const TC        &deriv_x,               // d(coord)dx
        const TC        &deriv_y) const = 0;    // d(coord)dy

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;
};

// 1D
typedef Texture_sampler<Scalar,                 Scalar>  Texture1D_sampler_float;
typedef Texture_sampler<Vector2,                Scalar>  Texture1D_sampler_float2;
typedef Texture_sampler<Vector3,                Scalar>  Texture1D_sampler_float3;
typedef Texture_sampler<Vector4,                Scalar>  Texture1D_sampler_float4;
typedef Texture_sampler<Dscalar,                Scalar>  Texture1D_sampler_double;
typedef Texture_sampler<Dvector2,               Scalar>  Texture1D_sampler_double2;
typedef Texture_sampler<Dvector3,               Scalar>  Texture1D_sampler_double3;
typedef Texture_sampler<Dvector4,               Scalar>  Texture1D_sampler_double4;
typedef Texture_sampler<COLOR::Color_struct,    Scalar>  Texture1D_sampler_color;
typedef Texture_sampler<COLOR::Spectrum_struct, Scalar>  Texture1D_sampler_spectrum;
// 2D
typedef Texture_sampler<Scalar,                 Vector2> Texture2D_sampler_float;
typedef Texture_sampler<Vector2,                Vector2> Texture2D_sampler_float2;
typedef Texture_sampler<Vector3,                Vector2> Texture2D_sampler_float3;
typedef Texture_sampler<Vector4,                Vector2> Texture2D_sampler_float4;
typedef Texture_sampler<Dscalar,                Vector2> Texture2D_sampler_double;
typedef Texture_sampler<Dvector2,               Vector2> Texture2D_sampler_double2;
typedef Texture_sampler<Dvector3,               Vector2> Texture2D_sampler_double3;
typedef Texture_sampler<Dvector4,               Vector2> Texture2D_sampler_double4;
typedef Texture_sampler<COLOR::Color_struct,    Vector2> Texture2D_sampler_color;
typedef Texture_sampler<COLOR::Spectrum_struct, Vector2> Texture2D_sampler_spectrum;
// 3D
typedef Texture_sampler<Scalar,                 Vector3> Texture3D_sampler_float;
typedef Texture_sampler<Vector2,                Vector3> Texture3D_sampler_float2;
typedef Texture_sampler<Vector3,                Vector3> Texture3D_sampler_float3;
typedef Texture_sampler<Vector4,                Vector3> Texture3D_sampler_float4;
typedef Texture_sampler<Dscalar,                Vector3> Texture3D_sampler_double;
typedef Texture_sampler<Dvector2,               Vector3> Texture3D_sampler_double2;
typedef Texture_sampler<Dvector3,               Vector3> Texture3D_sampler_double3;
typedef Texture_sampler<Dvector4,               Vector3> Texture3D_sampler_double4;
typedef Texture_sampler<COLOR::Color_struct,    Vector3> Texture3D_sampler_color;
typedef Texture_sampler<COLOR::Spectrum_struct, Vector3> Texture3D_sampler_spectrum;
// CUBE
typedef Texture_sampler<Scalar,                 Vector3> TextureCUBE_sampler_float;
typedef Texture_sampler<Vector2,                Vector3> TextureCUBE_sampler_float2;
typedef Texture_sampler<Vector3,                Vector3> TextureCUBE_sampler_float3;
typedef Texture_sampler<Vector4,                Vector3> TextureCUBE_sampler_float4;
typedef Texture_sampler<Dscalar,                Vector3> TextureCUBE_sampler_double;
typedef Texture_sampler<Dvector2,               Vector3> TextureCUBE_sampler_double2;
typedef Texture_sampler<Dvector3,               Vector3> TextureCUBE_sampler_double3;
typedef Texture_sampler<Dvector4,               Vector3> TextureCUBE_sampler_double4;
typedef Texture_sampler<COLOR::Color_struct,    Vector3> TextureCUBE_sampler_color;
typedef Texture_sampler<COLOR::Spectrum_struct, Vector3> TextureCUBE_sampler_spectrum;


//------------------------------------- light ---------------------------------
//
// Light_sampler is used by shaders to apply a BRDF to every light. The
// Light_iterator is just a container for holding information relative
// to a light sample, while the actual iteration, involving sample
// selection and shader evaluation is performed by the underlying light
// sampler.
//

///
/// Light_iterator_options
///
struct Light_iterator_options_struct
{
    bool         m_categories_set;
    Uint32       m_n_categories;
    const char** m_categories;

    bool         m_shadows_set;
    bool         m_shadows;

    bool         m_cone_set;
    Vector3      m_cone_axis;
    Scalar       m_cone_angle;
};


class Light_iterator_options : protected Light_iterator_options_struct {
public:
    inline Light_iterator_options();

    inline void set_categories(
        const Uint32 n_categories,  // The number of categories.
        const char  *categories[]); // The array of categories.

    inline void set_shadows(
        const bool on_off);         // Compute shadows if true.

    inline void set_cone(
        const Vector3& axis,        // The axis of the cone.
        const Scalar angle);        // The angle of the come.

    // propagate the options to a light sampler
    inline void apply(
        Light_sampler& sampler) const;
};


///
/// Light_iterator_struct
///
struct Light_iterator_struct
{
    Uint                   m_count;        // # of samples taken so far
    Vector3                m_point;        // sample point on the light
    Vector3                m_dir;          // normalized light direction
    Scalar                 m_dist;         // distance
    Scalar                 m_dot_nl;       // state->normal . light dir
    COLOR::Spectrum_struct m_raw_contrib;  // radiance returned by light
    COLOR::Spectrum_struct m_shadow;       // shadow attenuation
    Scalar                 m_weight;       // sample weight
    bool                   m_valid;        // validity flag
};


///
/// Light_iterator
///
/// Light_sampler is used by shaders to apply a BRDF to every light. The
/// Light_iterator is just a container for holding information relative
/// to a light sample, while the actual iteration, involving sample
/// selection and shader evaluation is performed by the underlying light
/// sampler.
///
///
struct Light_iterator : protected Light_iterator_struct
{
    inline Light_iterator(
        const Factory* const factory,
        const Light_iterator_options& options);
    inline Light_iterator(const Factory* const factory);

    inline Light_iterator(
        Light_sampler* const sampler,
        const Light_iterator_options& options);

    inline Light_iterator(Light_sampler* const sampler);

    // this constructor is not stricly required but avoids special case handling
    // in the C++ backend which is non trivial with the current implementation
    inline Light_iterator(
        const Factory* const factory,
        const Light_iterator& source);

    inline Light_iterator(const Light_iterator& source);

    inline Light_iterator& operator=(const Light_iterator& source);

    inline ~Light_iterator();

    // advance to next sample
    inline Light_iterator &operator++();
    inline Light_iterator  operator++(int);

    // equal
    inline bool operator==(
        const Light_iterator& it) const;        // compare to this

    // not equal
    inline bool operator!=(
        const Light_iterator& it) const;        // compare to this

    // true if valid, false otherwise
    inline operator bool() const;

    //---------------------------------- getters ------------------------------

    // sample point on the light
    inline const Vector3 &get_point() const;

    // normalized direction to light sample
    inline const Vector3 &get_direction() const;

    // distance illuminated point -> m_point
    inline Scalar get_distance() const;

    // state->normal * m_dir
    inline Scalar get_dot_nl() const;

    // return the contribution from the light. The result of the
    // get_contribution function is equal to raw_contribution * shadow
    // (where shadows include volume atten.)

    // light contribution incl. shadow & volume
    inline const COLOR::Spectrum_struct get_contribution() const;

    // light contribution w/o shadow & volume
    inline const COLOR::Spectrum_struct get_raw_contribution() const;

    // shadow atten, 1 1 1=none, 0 0 0=full
    inline const COLOR::Spectrum_struct get_shadow() const;

    // get light parameter
    inline bool get_light_parameter(
        const char*     name,           // parameter name
        Type_code::Id   type,           // parameter type
        void*           value) const;   // parameter value

    // return the number of samples taken so far
    inline Uint get_count() const;

    // true if valid, false otherwise
    inline bool is_valid() const;

    // get a pointer to Light_iterator_struct
    inline const Light_iterator_struct* operator&() const;

    // get a pointer to Light_iterator_struct
    inline Light_iterator_struct* operator&();

  private:
    inline void init(
        const Light_iterator_options* const options,
        Light_sampler* sampler);

    Light_sampler *m_sampler; // the light sampler
};


//
// Helper functions
//

// get the contribution of a light iterator
COLOR::Spectrum_struct get_contribution(
    const Light_iterator_struct& light_iterator);

// get the raw contribution of a light iterator
COLOR::Spectrum_struct get_raw_contribution(
    const Light_iterator_struct& light_iterator);


//-----------------------------------------------------------------------------
///
/// A light sampler is the class which selects samples on light sources
/// and fills in light iterators.
///
struct Light_sampler
{
    // start iteration over sampled lights
    virtual void begin() = 0;

    // is at end
    virtual bool end() const = 0;

    // get current sample
    virtual Light_iterator_struct operator* () const = 0;

    // advance one step
    virtual void get_next (
        Light_iterator_struct*) = 0;    // put results here

    // is current sample valid
    virtual operator bool() const = 0;

    // get light parameter
    virtual bool get_light_parameter(
        const char*     name,           // parameter name
        Type_code::Id   type,           // parameter type
        void*           value)          // parameter value
        const = 0;

    // set light categories
    virtual void set_categories(
        Uint32 n_categories,               // The number of categories.
        const char *categories[]) = 0;  // The array of categories.

    // set shadows on/off
    virtual void set_shadows(
        bool on_off) = 0;               // on/off

    // set lighting cone
    virtual void set_cone(
        const Vector3&  axis,           // cone axis
        const Scalar    angle) = 0;     // cone angle

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;

    // create a deep copy
    virtual Light_sampler* clone() const = 0;
};


//-----------------------------------------------------------------------------
///
/// QMC sampling context
///
struct Sampling_context
{
    // start a sampling session
    virtual void begin(
        Uint n) = 0;                    // number of instances

    // stop a sampling session
    virtual void stop() = 0;

    // is at end
    virtual bool end() const = 0;

    // advance to next
    virtual void next() = 0;

    // single dimensional sample. If multiple dimensional sample is
    // required, this function should be called several times.
    virtual Scalar  sample() = 0;
    virtual Vector2 sample2() = 0;
    virtual Vector3 sample3() = 0;
    virtual Vector4 sample4() = 0;

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;
};


//-----------------------------------------------------------------------------
///
/// A Texture_info provides texture properties, such as width, height, and depth.
///
struct Texture_info
{
    // get the width
    virtual Uint32 get_width() const = 0;

    // get the height
    virtual Uint32 get_height() const = 0;

    // get the depth
    virtual Uint32 get_depth() const = 0;

    // return true if the texture is valid
    virtual bool is_valid() const = 0;

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;
};


//-----------------------------------------------------------------------------
///
/// Factory interface
///
struct Factory
{
    /// \c Texture_sampler factory functions.
    ///{
    virtual Texture1D_sampler_float* create_texture1D_sampler_float(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_float2* create_texture1D_sampler_float2(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_float3* create_texture1D_sampler_float3(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_float4* create_texture1D_sampler_float4(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_double* create_texture1D_sampler_double(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_double2* create_texture1D_sampler_double2(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_double3* create_texture1D_sampler_double3(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_double4* create_texture1D_sampler_double4(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_color* create_texture1D_sampler_color(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture1D_sampler_spectrum* create_texture1D_sampler_spectrum(
        Tag                     texture,                // texture tag
        Scalar                  blur=1,                 // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_float* create_texture2D_sampler_float(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_float2* create_texture2D_sampler_float2(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_float3* create_texture2D_sampler_float3(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_float4* create_texture2D_sampler_float4(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_double* create_texture2D_sampler_double(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_double2* create_texture2D_sampler_double2(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_double3* create_texture2D_sampler_double3(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_double4* create_texture2D_sampler_double4(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_color* create_texture2D_sampler_color(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture2D_sampler_spectrum* create_texture2D_sampler_spectrum(
        Tag                     texture,                // texture tag
        const Vector2&          blur=Vector2(1,1),      // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_float* create_texture3D_sampler_float(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_float2* create_texture3D_sampler_float2(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_float3* create_texture3D_sampler_float3(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_float4* create_texture3D_sampler_float4(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_double* create_texture3D_sampler_double(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_double2* create_texture3D_sampler_double2(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_double3* create_texture3D_sampler_double3(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_double4* create_texture3D_sampler_double4(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_color* create_texture3D_sampler_color(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual Texture3D_sampler_spectrum* create_texture3D_sampler_spectrum(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_float* create_textureCUBE_sampler_float(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_float2* create_textureCUBE_sampler_float2(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_float3* create_textureCUBE_sampler_float3(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_float4* create_textureCUBE_sampler_float4(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_double* create_textureCUBE_sampler_double(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_double2* create_textureCUBE_sampler_double2(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_double3* create_textureCUBE_sampler_double3(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_double4* create_textureCUBE_sampler_double4(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_color* create_textureCUBE_sampler_color(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;

    virtual TextureCUBE_sampler_spectrum* create_textureCUBE_sampler_spectrum(
        Tag                     texture,                // texture tag
        const Vector3&          blur=Vector3(1,1,1),    // more blurry if >1
        Texture_filter::Id      f=Texture_filter::FAST) // filter kernel
        const = 0;
    ///}

    // create a texture info
    virtual Texture_info* create_texture_info(
        Tag                     texture)                // texture tag
        const = 0;

    // get the pointer to a baked result output string
    virtual const char* get_result_string() const = 0;

    // get the pointer to a baked transparency output string
    virtual const char* get_transparency_string() const = 0;

    // Create a light sampler
    virtual Light_sampler* create_light_sampler() const = 0;

    // Create a ray data container
    virtual Ray_data* create_ray_data() const = 0;

    // Allocate memory, returns null on failure.
    // The memory must be freed using free.
    virtual void* alloc(size_t num_bytes) = 0;

    // Free memory allocated by alloc.
    virtual void free(void* ptr) = 0;

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;
};


//-----------------------------------------------------------------------------
///
/// Log interface
///
struct Log
{
    // log an error message
    virtual void error(
        const char *message) const = 0;  // The log message.

    // log a warning message
    virtual void warning(
        const char *message) const = 0;  // The log message.

    // log an info message
    virtual void info(
        const char *message) const = 0;  // The log message.

    // log a progress message
    virtual void progress(
        const char *message) const = 0;  // The log message.

    // add a reference to this object
    virtual void add_ref() = 0;

    // release this
    virtual void release() = 0;
};


///
/// Representation of a MetaSL shader graph.
///
struct Graph
{
    // add a reference
    virtual void add_ref() = 0;

    // release, destroy after last reference is released
    virtual void release() = 0;

    // retrieve the node with the given name.
    //
    // If the name does not exist, or the node with the given name
    // is a BSDF, return an invalid tag.
    virtual Tag get_shader(String_id name) const = 0;

    // retrieve the node with the given name.
    //
    // If the name does not exist, or the node with the given name
    // is a Shader, return an invalid tag.
    virtual Tag get_bsdf(String_id name) const = 0;
};


///
/// Representation of a MetaSL material or light definition.
///
/// Material and light definitions are shader graphs with a specified
/// set of nodes.
///
struct Material_def : public Graph
{
    enum Shader_id {
        DISPLACEMENT_SHADER,
        SURFACE_SHADER,
        TRANSPARENCY_SHADER,
        IOR_SHADER,
        VOLUME_SHADER,
        VOLUME_ABSORPTION_SHADER,
        VOLUME_SCATTERING_SHADER,
        LIGHT_SHADER,
        RADIANT_EXITANCE_SHADER,
        SHADER_COUNT,
        SHADER_ALIGN                    = 0xFFFFFFFF    // force to be 32bits
    };

    enum Bsdf_id {
        SURFACE_BSDF,
        VOLUME_BSDF,
        LIGHT_BSDF,
        BSDF_COUNT,
        BSDF_ALIGN                      = 0xFFFFFFFF    // force to be 32bits
    };

    // retrieve the given node.
    //
    // If the node does not exist, or the requested node
    // is a BSDF, return an invalid tag.
    virtual Tag get_std_shader(Shader_id id) const = 0;

    // retrieve the given node.
    //
    // If the node does not exist, or the requested node
    // is a Shader, return an invalid tag.
    virtual Tag get_std_bsdf(Bsdf_id id) const = 0;
};


//-------------------- particle map -------------------------------------------

struct Particle_map_options_struct
{
};


class Particle_map_options : public Particle_map_options_struct
{
public:
    // Specifies the furthest distance from the position argument in which values
    // will be considered. If left unspecified, all points will be considered.
    void set_maximum_distance(float max_distance) {}

    // Specifies the furthest angular distance from the direction argument in
    // which values will be considered. If left unspecified, all directions will
    // be considered.
    void set_maximum_angle(float max_angle) {}

    // Specifies the maximum number of points that will be considered.
    // If more points are found than specified by the max points argument,
    // the points closest in distance will be selected. If left unspecified,
    // all points will be considered.
    void set_maximum_points(int max_points) {}

    // Specifies a region in three dimensional space around the position
    // argument in which values will be considered. These values are specified
    // relative to the given position. If left unspecified, all points will be
    // considered.
    void set_search_volume(
            const Vector3& min,
            const Vector3& max) {}

    // Specifies a region in four dimensional space around the position
    // argument in which values will be considered. These values are specified
    // relative to the given position. If left unspecified, all points will be
    // considered.
    void set_search_volume(
            const Vector4& min,
            const Vector4& max) {}
};


struct Particle_map
{
};


}}      // namespace MI::SHADER

#include "mi_shader_state_inline.h"

#endif // MI_SHADER_STATE_H

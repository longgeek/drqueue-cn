//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file
///
//*****************************************************************************

#ifndef MI_METASL_RUNTIME_TAG_WRAPPER_H
#define MI_METASL_RUNTIME_TAG_WRAPPER_H

#include "mi_shader_types.h"

namespace MI {

//
// Dummy structs for the tag wrapper below
//

namespace TEXTURE {
struct Texture1D_dummy { };
struct Texture2D_dummy { };
struct Texture3D_dummy { };
struct TextureCUBE_dummy { };
} // namespace TEXTURE

namespace PARTICLE_MAP {
struct Particle_map_dummy { };
} // namespace PARTICLE_MAP

namespace LIGHT_PROFILE {
struct Light_profile_dummy { };
} // namespace LIGHT_PROFILE

namespace SHADER {
struct Shader_dummy { };
struct Bsdf_dummy { };
} // namespace SHADER

//
// Wrapper classes for tags, useful for overloading functions
// where the underlying type refers to a tag.
//
template <typename T>
class Tag_wrapper
{
  private:
    SHADER::Tag m_tag;

  public:
    Tag_wrapper() :
        m_tag(0)
    { }

    Tag_wrapper(const SHADER::Tag tag) :
        m_tag(tag)
    { }

    void set(const SHADER::Tag tag)
    {
        m_tag = tag;
    }

    operator SHADER::Tag() const
    {
        return m_tag;
    }

    bool is_valid() const
    {
        return bool(m_tag);
    }
};


typedef Tag_wrapper<TEXTURE::Texture1D_dummy> Texture1D_tag;
typedef Tag_wrapper<TEXTURE::Texture2D_dummy> Texture2D_tag;
typedef Tag_wrapper<TEXTURE::Texture3D_dummy> Texture3D_tag;
typedef Tag_wrapper<TEXTURE::TextureCUBE_dummy> TextureCUBE_tag;
typedef Tag_wrapper<PARTICLE_MAP::Particle_map_dummy> Particle_map_tag;
typedef Tag_wrapper<LIGHT_PROFILE::Light_profile_dummy> Light_profile_tag;
typedef Tag_wrapper<SHADER::Shader_dummy> Shader_tag;
typedef Tag_wrapper<SHADER::Bsdf_dummy> Bsdf_tag;

} // namespace MI


#endif // MI_METASL_RUNTIME_TAG_WRAPPER_H

///////////////////////////////////////////////////////////////////////////////
// Copyright 1986, 2013 NVIDIA Corporation. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Created:	26.1.09
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file shader_mipremap.h
/// mental ray C++ shader interface extensions.
///
/// This file provides interfaces to advanced texture filtering.
///
/// shader_mipremap.h is included by mi_shader_if.h, which in turn is
/// included from shader.h if the shader is compiled as C++ code.
/// A shader does not need to include this file directly.

#ifndef SHADER_MIPREMAP_H
#define SHADER_MIPREMAP_H

namespace mi {
namespace shader_v3 {

/// \brief Texture re-mapping interface.
///
/// This class provides texture coordinate transformation for use in
/// texture filtering. The shader function Interface::lookup_filter_color_texture
/// expects an implementation of this class as a parameter.

class Mip_remap {
  public:
    /// \brief Transformation of texture coordinates.
    ///
    /// This can be used to apply affine transformations to the
    /// coordinates, including texture repeat/scaling.
    //
    /// \param[in,out]	tex_coord	uv coordinate to transform
    virtual void coord_transform(
	miVector2d &	    tex_coord) const = 0;

    /// \brief Remapping of texture coordinates.
    ///
    /// This can be used to implement texture wrapping modes like
    /// torus, alternating, clamping), and cropping.
    ///
    /// \param[in]	image		texture image
    /// \param[in,out]	image_coord	texture coordinate in image space,
    /// with <tt>
    /// image_coord[0]: [0..mi_img_get_width(image)-1],
    /// image_coord[1]: [0..mi_img_get_height(image)-1]</tt>
    virtual void coord_remap(
	const miImg_image * image,
	int		    image_coord[2]) const = 0;
};


}}

#endif

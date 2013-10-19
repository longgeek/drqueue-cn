///////////////////////////////////////////////////////////////////////////////
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Created:	26.1.09
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

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
	miVector2d &	tex_coord) const = 0;

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
	miImg_image *	image,
	int		image_coord[2]) const = 0;
};


}}

#endif

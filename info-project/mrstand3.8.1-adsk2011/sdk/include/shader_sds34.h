///////////////////////////////////////////////////////////////////////////////
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Created:	9.10.08
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file shader_sds34.h
/// mental ray C++ shader interface extensions.
///
/// This file provides interfaces that allow interaction with sds34
/// subdivision surfaces.
///
/// shader_sds34.h is included by mi_shader_if.h, which in turn is 
/// included from shader.h if the shader is compiled as C++ code.
/// A shader does not need to include this file directly.


#ifndef SHADER_SDS34_H
#define SHADER_SDS34_H

namespace mi {
namespace shader_v3 {

/// \brief Subdivision34 class
///
/// \brief This class provides access to the mixed triangle-quad
/// subdivision class in mental ray, which has the ccmesh front-end
/// in the mental ray API. ccmesh creates a database element containing
/// only triangles and quads, either directly from the source geometry
/// or with a single Catmull-Clark subdivision step in case of polygons
/// other than triangles or quads.
///

class Subdivision34 {
  public:

    /// \brief space type. A vector space contains 3d positions, arbitrary
    /// dimension scalar textures or multiple 3d motion vectors.
    enum Space_type {POS, TEXTURE, MOTION};

    /// \brief return the number of vector spaces
    virtual miUint get_no_spaces() const = 0;

    /// \brief return the dimension of a given space
    /// \param space is the space index
    virtual miUint get_dimension(miUint space) const = 0;

    /// \brief return the type of a given space
    /// \param space is the space index
    virtual Space_type get_space_type(miUint space) const = 0;

    /// \brief return the number of vectors of a given space
    /// \param space is the space index
    virtual miUint get_no_vectors(miUint space) const = 0;

    /// \brief vector access
    /// \param space is the space index
    /// \param which is the vector index within the space
    /// \return the address of the first scalar of the n-dimensional
    /// vector is returned. the length is equal to the dimension as
    /// returned by get_dimension.
    virtual const miScalar * get_vector(
	    miUint	space,
	    miUint	which) const = 0;	// vector

    /// \brief return the number of triangles for the subdiv surface
    virtual miUint get_no_triangles() const = 0;

    /// \brief return the number of quads for the subdiv surface
    virtual miUint get_no_quads() const = 0;

    /// \brief face data structure for triangles and quads
    /// m_vertices contains either 3 or 4 indices into the vector
    /// spaces. use get_vector to access the positions, textures etc
    /// using the vertex indices.
    /// m_material is the material tag for the given face.
    struct Face {
	    const miUint *	m_vertices;	// ret 3 or 4 indices
	    miTag		m_material;	// face material
    };

    /// \brief triangle access
    /// \param space is the space index
    /// \param which is the triangle index
    /// \return the triangle data is returned
    virtual const Face get_triangle(
	    miUint	space,
	    miUint	which) const = 0;	// triangle

    /// \brief quad access
    /// \param space is the space index
    /// \param which is the quad index
    /// \return the quad data is returned
    virtual const Face get_quad(
	    miUint	space,
	    miUint	which) const = 0;	// quad

    /// \brief triangle derivatives
    /// \param face is the triangle index
    /// \param which is the vertex index, 0-2
    /// \retval derivs The du/dv result vectors
    /// \return du, dv are returned in derivs
    virtual bool get_triangle_derivatives(
	    miUint	face,			// triangle
	    miUint	which,			// vertex 0-2
	    miVector	derivs[2]) = 0;		// result du dv vectors

    /// \brief quad derivatives
    /// \param face is the quad index
    /// \param which is the vertex index, 0-3
    /// \retval derivs The du/dv result vectors
    /// \return du, dv are returned in derivs
    virtual bool get_quad_derivatives(
	    miUint	face,			// quad
	    miUint	which,			// vertex 0-3
	    miVector	derivs[2]) = 0;		// result du dv vectors
};

/// \brief Subdivision34 access class. Provides access to
/// Subdivision34 as defined above.
class Access_subdivision34 {
  public:
    Access_subdivision34(
	miTag tag);

    ~Access_subdivision34();

    Subdivision34 * operator->() const;

  private:
    Access_subdivision34(const Access_subdivision34&);
    Access_subdivision34 & operator=(const Access_subdivision34&);
    mi::shader_v3::Interface *	m_iface;
    Subdivision34 *		m_sds34;
    const miTag	  	 	m_tag;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Access_subdivision34.
typedef Access_subdivision34 Subdivision34_access;

/// \brief constructor
inline Access_subdivision34::Access_subdivision34(
    miTag	tag)
  : m_iface(mi_get_shader_interface()),
    m_sds34(m_iface->accessSubdivision34(tag)),
    m_tag(tag)
{
}

/// \brief destructor
inline Access_subdivision34::~Access_subdivision34()
{
    if (m_sds34 != 0)
	m_iface->releaseSubdivision34(m_sds34);
    m_iface->release();
}

/// \brief class access
inline Subdivision34 * Access_subdivision34::operator->() const
{
    return m_sds34;
}

}}

#endif //SHADER_SDS34_H

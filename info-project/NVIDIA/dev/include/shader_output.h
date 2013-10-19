/******************************************************************************
 * Copyright 1986, 2013 NVIDIA Corporation. All rights reserved.
 ******************************************************************************
 *
 *  Created     : 08.01.2010
 *  Author      : sehera
 *  Module      : api
 *  Purpose     : mental ray C++ shader interface extensions
 *
 *  \file shader_output.h
 *  mental ray C++ shader interface extensions.
 *
 *  This file provides interfaces that allow to access an output image.
 *
 *  shader_output.h is included by mi_shader_if.h, which in turn is
 *  included from shader.h if the shader is compiled as C++ code.
 *  A shader does not need to include this file directly.
 */

#ifndef SHADER_OUTPUT_H_
#define SHADER_OUTPUT_H_
#include "mi_shader_if.h"

namespace mi {
namespace shader_v3 {

/// \brief Smart pointer to access miImg_image struct, no editing.
///
/// There resources are released automatically when Access_out_img goes out of scope.
/// For editing operations use Edit_out_img.
class Access_out_img {
    public:
    /// \brief smart pointer for the output miImg_image, read-only access.
        /// \param state for buffer access (state->ts->buffers is set)
        /// \param name name of the framebuffer
        Access_out_img(miState *state, const char* name);

        /// \param state for buffer access (state->ts->buffers is set)
        /// \param index from get_index method of a framebuffer
        /// \param compat set this to true, if index is an rc constant (miRC_IMAGE_*)
        Access_out_img(miState *state, const size_t index, const bool compat =false);

        /// \brief release resources, unpin database tag
        ~Access_out_img();

        /// \brief reference the miImg_image, read-only access
        const miImg_image * operator->() const;
        operator const miImg_image*();

    private:
        const miImg_image              *m_image;
        size_t                          m_index;
        miState                         *const m_state;
        mi::shader_v3::Interface        *m_iface;
    private:
        Access_out_img & operator=(const Access_out_img&);
};


/// \brief Smart pointer to access miImg_image struct for editing.
///
/// There resources are released automatically when Edit_out_img goes out of scope.

class Edit_out_img {
    public:
        /// \brief smart pointer for the output miImg_image, read-write access.
        /// \param state for framebuffer access
        /// \param name name of the framebuffer
        Edit_out_img(miState *state, const char* name);

        /// \param state for framebuffer access
        /// \param index from get_index method of a framebuffer
        /// \param compat set this to true, if index is an rc constant (miRC_IMAGE_*)
        Edit_out_img(miState *state, const size_t index, const bool compat=false);

        /// \brief release resources, unmap output image
        ~Edit_out_img();

        /// \brief reference the miImg_image, read-write access
        miImg_image * operator->() const;
        operator miImg_image*();

    private:
        miImg_image                     *m_image;
        size_t                          m_index;
        miState                         *const m_state;
        mi::shader_v3::Interface        *m_iface;
    private:
        Edit_out_img & operator=(const Edit_out_img&);
};

inline Access_out_img::Access_out_img(
    miState             *state,
    const char          *name)
    : m_state(state)
    , m_iface(mi_get_shader_interface())
{
    Access_fb fb(state->camera->buffertag);
    if(!fb->get_index(name, m_index))
        m_index = size_t(-1);
    miImg_image * tmp = 0;
    m_iface->open_output_image(tmp, m_state, m_index);
    m_image = tmp;
}

inline Access_out_img::Access_out_img(
    miState             *state,
    const size_t        index,
    const bool          compat)
  : m_index(index)
  , m_state(state)
  , m_iface(mi_get_shader_interface())
{
    if(compat)
    {
        Access_fb fb(state->camera->buffertag);
        int idx =-1;
        // index is a miRC_IMAGE_* constant
        if(fb->map_old_index((unsigned int)index, idx))
        {
            m_index = idx;
        }
        else
        {
            m_index = size_t(-1);
        }
    }
    miImg_image * tmp = 0;
    m_iface->open_output_image(tmp, m_state, m_index);
    m_image = tmp;
}

inline Access_out_img::~Access_out_img()
{
    if (m_image) {
        m_iface->close_output_image(m_state, m_index);
    }
    m_iface->release();
}

inline const miImg_image * Access_out_img::operator->() const
{
    return m_image;
}

inline Access_out_img::operator const miImg_image*()
{
    return m_image;
}

inline Edit_out_img::Edit_out_img(
    miState             *state,
    const char*         name)
  : m_state(state)
  , m_iface(mi_get_shader_interface())
{
    Access_fb fb(state->camera->buffertag);
    if(!fb->get_index(name, m_index))
        m_index = size_t(-1);
    m_iface->open_output_image(m_image, m_state, m_index);
}

inline Edit_out_img::Edit_out_img(
    miState             *state,
    const size_t        index,
    const bool          compat)
  : m_index(index)
  , m_state(state)
  , m_iface(mi_get_shader_interface())
{
    if(compat)
    {
        Access_fb fb(state->camera->buffertag);
        int idx = -1;
        // index is a miRC_IMAGE_* constant
        if(fb->map_old_index((unsigned int)index, idx))
        {
            m_index = idx;
        }
        else
        {
            m_index = size_t(-1);
        }
    }
    m_iface->open_output_image(m_image, m_state, m_index);
}

inline Edit_out_img::~Edit_out_img()
{
    if (m_image) {
        m_iface->close_output_image(m_state, m_index);
    }
    m_iface->release();
}

inline miImg_image * Edit_out_img::operator->() const
{
    return m_image;
}

inline Edit_out_img::operator miImg_image*()
{
    return m_image;
}

}
}

#endif /* SHADER_OUTPUT_H_ */

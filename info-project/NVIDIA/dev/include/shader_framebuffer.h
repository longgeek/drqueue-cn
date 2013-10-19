///////////////////////////////////////////////////////////////////////////////
// Copyright 1986, 2013 NVIDIA Corporation. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Created:	27.02.08
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file shader_framebuffer.h
/// mental ray C++ shader interface extensions.
///
/// This file provides interfaces that allow interaction with frame buffers.
///
/// shader_framebuffer.h is included by mi_shader_if.h, which in turn is 
/// included from shader.h if the shader is compiled as C++ code.
/// A shader does not need to include this file directly.


#ifndef SHADER_FRAMEBUFFER_H
#define SHADER_FRAMEBUFFER_H
#include "mi_shader_if.h"

namespace mi {
namespace shader_v3 {


/// \brief Framebuffer class.
///
/// The Framebuffer class is a collection of framebuffers used for a frame rendering.
/// It provide an interface to the named framebuffer attributes.
/// It also allows to retrieve the index of the buffer to use it with
/// <tt>mi_fb_put</tt> and <tt>mi_fb_get</tt> functions.
/// 
/// All strings are const char. Strings passsed in are copied, and need to
/// be freed by the user. Strings passed out should be copied by the user,
/// since they reference internal data.
///
class Framebuffer {
    public:
        /// \brief set a boolean attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const 	bool value) = 0;

        /// \brief set a float attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const float value) = 0;

        /// \brief set an integer attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const int 	value) = 0;

        /// \brief set an integer attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the new value of the attribute. A copy of the value is stored.
        virtual bool set(
            const char 	*buffer, 
            const char 	*param, 
            const char 	*value) = 0;

        /// \brief get a boolean attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            bool 	&value) const = 0;

        /// \brief get a float attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            float 	&value) const = 0;

        /// \brief get an integer attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise. 
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            int 	&value) const = 0;

        /// \brief get a string attribute for a framebuffer
        /// \param buffer is the name of the framebuffer
        /// \param param is the name of the attribute 
        /// \param value is the returned value of the attribute
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get(
            const char 	*buffer, 
            const char 	*param, 
            const char 	*&value) const = 0;

        /// \brief get an index of the framebuffer to be used in
        /// <tt>mi_fb_put</tt> and <tt>mi_fb_get</tt> functions.
        /// \param buffer is the name of the framebuffer
        /// \param index is the returned index
        /// \return true if an attribute for the given framebuffer with the given 
        /// name and type is found, false otherwise.
        virtual bool get_index(const char *buffer, size_t &index) const = 0;

        /// \brief removes all named buffers.
        /// It is not legal to call this method during the rendering process.
        /// \return true if the operation is successful, false otherwise.
        virtual bool reset() = 0;

        /// \brief echoes mi syntax for the framebuffer to the file pointer.
        virtual void echo(FILE *) const = 0;

        /// \brief get the count of buffers defined.
        /// \param buffercount is the number of buffers.
        /// \return false on failure.
        virtual bool get_buffercount(size_t &buffercount) const = 0;

        /// \brief get the name of buffer num. Note that num
        /// is not related to the index returned by <tt>get_index</tt>
        /// \param num is the number of the buffer name to return,
        /// starting with 0.
        /// \param name is the returned buffer name.
        /// \return false on failure.
        virtual bool get_buffername(size_t num, const char *&name) const = 0;

        /// \brief removes the named buffer.
        /// It is not legal to call this method during the rendering process.
        /// \return true if the operation is successful, false otherwise.
        virtual bool remove(const char *buffer) = 0;

        /// \brief get an index of the framebuffer mapped from the old
        /// miRC_IMAGE_* indices.
        /// for user framebuffers get_index has to be used.
        /// \param rc_index is the old rc index 0 to miRC_IMAGE_USER.
        /// \param index is the returned index of the framebuffer
        /// \return true if the rc buffer is available and index was set
        /// false otherwise. index is then set to -1
        virtual bool map_old_index(const unsigned int rc_index, int &index) const = 0;

        /// \brief get the data type of the given frame buffer.
        /// \param num is the number of the buffer name to return,
        /// starting with 0.
        /// \param type the data type of the \p num'th frame buffer.
        /// \return false on failure.
        virtual bool get_datatype(size_t num, miImg_type& type) const = 0;

};

/// \brief Smart pointer to access Framebuffer class, no editing.
///
/// There resources are released automatically when Access_fb goes out of scope.
/// For editing operations use Edit_fb.
class Access_fb {
    public:
        /// \brief smart pointer for the Framebuffer tag, read-only access.
        /// \param tag framebuffer database tag.
        Access_fb(
	    miTag tag);

	/// \brief release resources, unpin database tag
        ~Access_fb();

	/// \brief reference the Framebuffer class, read-only access
        const Framebuffer * operator->() const;
    private:
        Access_fb();
        Access_fb(const Access_fb &);
        const Access_fb & operator=(const Access_fb &);
	mi::shader_v3::Interface	*m_iface;
        const Framebuffer 		*const m_fb;
	const miTag	  	 	m_tag;
};


/// \brief Smart pointer to access Framebuffer class for editing.
///
/// There resources are released automatically when Edit_fb goes out of scope.

class Edit_fb {
    public:
        /// \brief smart pointer for the Framebuffer tag, read-write access.
        /// \param tag framebuffer database tag
        Edit_fb(
	    miTag tag);

	/// \brief release resources, unpin database tag
        ~Edit_fb();

	/// \brief reference the Framebuffer class, read-write access
        Framebuffer * operator->() const;
    private:
        Edit_fb();
        Edit_fb(const Edit_fb &);
        const Edit_fb & operator=(const Edit_fb &);
	mi::shader_v3::Interface	*m_iface;
	Framebuffer 			*const m_fb;
	const miTag			m_tag;
};

/// \brief Framebuffer access wrapper class.
///
inline Access_fb::Access_fb(
    miTag tag)
  : m_iface(mi_get_shader_interface())
  , m_fb(m_iface->accessFramebuffer(tag))
  , m_tag(tag)
{
}

inline Access_fb::~Access_fb()
{
    if (m_fb != 0) {
	m_iface->releaseFramebuffer(m_fb, m_tag);
    }
    m_iface->release();
}

inline const Framebuffer * Access_fb::operator->() const
{
    return m_fb;
}

/// \brief Framebuffer edit wrapper class.
///
inline Edit_fb::Edit_fb(
    miTag tag)
  : m_iface(mi_get_shader_interface())
  , m_fb(m_iface->editFramebuffer(tag))
  , m_tag(tag)
{
}

inline Edit_fb::~Edit_fb()
{
    if (m_fb != 0) {
	m_iface->releaseFramebuffer(m_fb, m_tag);
    }
    m_iface->release();
}

inline Framebuffer * Edit_fb::operator->() const
{
    return m_fb;
}


/// \brief Access for pass rendering
///
/// This only works with unified rendering.
/// The Merge_pass class should be used to access and edit render
/// passes in a pass merge shader. The merge shader is called for
/// every sample in a rendering pass that is read from the pass file.
///
/// The shader can use the set_sample methods to write the new sample
/// value to the framebuffer. The get_* methods can be used to retrieve
/// the two sample values to compare.
/// The methods with framebuffer names as parameters first map these names
/// to the framebuffer index. So they might not be as efficient.
///
/// Here is an example for a merge shader method
/// 	if(state->options->unified_sampling)
///	{
///	    mi::shader::Merge_pass merge(state);
///	    miColor tar;
///	    bool use_new = false;
///
///	    const miScalar* old_z = (const miScalar *)merge.get_cur_sample(1);
///	    const miScalar* pass_z = (const miScalar *)merge.get_pass_sample(1);
///	    if(!old_z || !pass_z)
///		return miFALSE; //should not happen
///	    if(*old_z>0.0f)
///	    {
///		if(*pass_z>0.0f && *pass_z<*old_z)
///		    use_new = true;
///	    }
///	    else if(*pass_z>0.0f)
///		use_new = true;
///
///	    if(use_new)
///	    {
///		tar = *(const miColor*)merge.get_pass_sample(size_t(0));
///
///		if ((int)state->raster_x/3%5 == (int)state->raster_y/3%5)
///		{
///
///		    switch(merge.get_cur_pass_number())
///		    {
///		      case 0:  tar.a = tar.r = 1; break;
///		      case 1:  tar.a = tar.g = 1; break;
///		      case 2:  tar.a = tar.b = 1; break;
///		      default: tar.a = tar.r = tar.g = tar.b = 1;
///		    }
///
///		}
///	    }
///	    else
///	    {
///		tar = *(const miColor*)merge.get_cur_sample(size_t(0));
///	    }
///	    merge.set_sample(size_t(0), &tar);
///
///	    return miTRUE;
///	}

class Merge_pass
{
    public:
	/// \brief Constructor
	Merge_pass(miState* state);

	/// \brief get the current sample value
	/// \param fb_name the framebuffer name
	/// \returns a pointer to the current sample value
	/// of the specified framebuffer
	const void* get_cur_sample(
	    const char* 	fb_name);

	/// brief get the current pass sample value
	/// \param fb_name the framebuffer name
	/// \returns a pointer to the current pass sample value
	/// of the specified framebuffer
	const void* get_pass_sample(
	    const char* 	fb_name);

	/// \brief set the sample value
	/// \param fb_name the framebuffer name
	/// \param sample a pointer to the sample value
	bool set_sample(
	    const char* 	fb_name,
	    void*		sample);

	/// \brief get the current sample value
	/// \param fb_index the framebuffer index (retrieved from get_index())
	/// \returns a pointer to the current sample value
	/// of the specified framebuffer
	const void* get_cur_sample(
	    size_t 		fb_index);
	/// brief get the current pass sample value
	/// \param fb_index the framebuffer index (retrieved from get_index())
	/// \returns a pointer to the current pass sample value
	/// of the specified framebuffer
	const void* get_pass_sample(
	    size_t		fb_index);

	/// \brief set the sample value
	/// \param fb_index the framebuffer index (retrieved from get_index())
	/// \param sample a pointer to the sample value
	bool set_sample(
	    size_t		fb_index,
	    void*		sample);

	/// \brief get the current pass index number
	/// \returns the current pass index number
	size_t get_cur_pass_number();

    private:
	mi::shader_v3::Interface	*m_iface;
	miState				*m_state;
};


inline Merge_pass::Merge_pass(
    miState* 	state)
  : m_iface(mi_get_shader_interface())
  , m_state(state)
{
}

inline const void* Merge_pass::get_cur_sample(
    const char* fb_name)
{
    size_t index(size_t(-1));
    Access_fb fb(m_state->camera->buffertag);
    if(!fb->get_index(fb_name, index))
        return NULL;

    return m_iface->renderpass_get_cur_sample(m_state, index);
}

inline const void* Merge_pass::get_pass_sample(
    const char* fb_name)
{
    size_t index(size_t(-1));
    Access_fb fb(m_state->camera->buffertag);
    if(!fb->get_index(fb_name, index))
        return NULL;

    return m_iface->renderpass_get_pass_sample(m_state, index);
}

inline bool Merge_pass::set_sample(
    const char* fb_name,
    void* 	sample)
{
    size_t index(size_t(-1));
    Access_fb fb(m_state->camera->buffertag);
    if(!fb->get_index(fb_name, index))
        return false;

    return m_iface->renderpass_set_sample(m_state, index, sample);
}


inline const void* Merge_pass::get_cur_sample(
    size_t	index)
{
    return m_iface->renderpass_get_cur_sample(m_state, index);
}

inline const void* Merge_pass::get_pass_sample(
    size_t	index)
{
    return m_iface->renderpass_get_pass_sample(m_state, index);
}

inline bool Merge_pass::set_sample(
    size_t	index,
    void* 	sample)
{
    return m_iface->renderpass_set_sample(m_state, index, sample);
}

inline size_t Merge_pass::get_cur_pass_number()
{
    return m_iface->renderpass_get_pass_number(m_state);
}

}}

#endif //SHADER_FRAMEBUFFER_H

/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 ******************************************************************************
 * Created:	28.01.2010
 * Purpose:	MetaSL interface for mental ray
 *
 * Note: This file is generated automatically from the mental ray sources, do
 * not edit. The interface exposed by this file exists solely for interaction
 * with compiler-generated MetaSL code and is subject to change.
 * This file is included from shader.h in C++ compilation mode and should not 
 * be included manually.
 *****************************************************************************/

#ifndef SHADER_METASL_H
#define SHADER_METASL_H

#ifndef __cplusplus
#error shader_metasl.h requires C++ compilation
#endif

#include <mi/metasl_runtime.h>


/*------------ mi_msl.h ------------*/


// forward declarations
namespace MI {
namespace SHADER {
class Brdf;
struct State;
struct Shader_system;
}}
namespace mi {
namespace shader_v3 {
struct Metasl_interface;
}}
// end forward declarations


/// \brief version number of the interface
static const int mi_ray_msl_interface_version = 1;


/// \brief Acquire an instance of the mental ray MetaSL shader interface extensions.
///
/// \param version is the version number of the requested interface class
/// and should usually be left at the default value.
/// The passed version argument is used to support multiple different interface
/// versions and should usually be the value of the variable
/// mi_ray_msl_interface_version in the defining header file. A future version of
/// mental ray may optionally return a pointer to a newer version of the
/// interface of a different type or in a different namespace, identified by a
/// different version number.
///
/// \return The returned pointer points to an object in mental ray which
/// contains the interface functions as virtual methods (hence it is possible to
/// call the interface routines from a dynamically loaded library without
/// resolving the routine in a symbol table). The caller may not attempt to
/// modify or delete the returned object but should call the
/// mi::shader::Metasl_interface::release() method when done.
///
/// \note
/// For convenience and to avoid leaks, users should use the
/// \c Access_metasl instead of this function.
extern "C" mi::shader_v3::Metasl_interface* mi_get_metasl_interface(
    int version = mi_ray_msl_interface_version);


namespace mi {
namespace shader_v3 {


/// forward declarations
class Bsdf;



/// \brief Top level MetaSL mental ray interface extensions.
///
/// This class is the top level access to the C++/MetaSL shader interface
/// extensions.
///
/// \c Metasl_interface instances should be acquired through the
/// \c Access_metasl class, although \c mi_get_metasl_interface can be used
/// as well. Note, however, that in the latter case the instance has to be
/// released manually by calling \c Metasl_interface::release.
///
/// The interface extensions are implemented as virtual functions in this
/// interface in order to avoid linking and symbol lookup problems.
struct Metasl_interface {
public:

    /// \brief acquire an instance of the interface
    ///
    /// See \c mi_get_metasl_interface for details.
    static inline Metasl_interface* get(
	int version = mi_ray_msl_interface_version)
    {
	return mi_get_metasl_interface(version);
    }


    /// \brief Release this interface instance.
    virtual void release();


    /// \brief Acquire the MetaSL shader system.
    virtual MI::SHADER::Shader_system* getSystem() const;


    /// \brief Get MetaSL state.
    ///
    /// This function returns a new MetaSL state initialized from the current
    /// miState. \c MI::SHADER::State::release() must be called when the state
    /// is not needed anymore.
    /// In order to avoid memory leaks due to missing \c State::release calls,
    /// the \c Access_state class should be used.
    /// \param state the current rendering state
    /// \return pointer to MetaSL state class
    virtual MI::SHADER::State* getState(
	    miState*		state
	    ) const;


    /// \brief Creates a \c Bsdf for the given MetaSL \c Brdf.
    ///
    /// This function generates a \c mi::shader::Bsdf that wraps around the
    /// provided \c Brdf. The returned pointer has to be released through the
    /// \c Metasl_interface::releaseBsdf function. The ownership of the
    /// provided \c Brdf pointer remains with the caller.
    virtual Bsdf* allocBsdf(
	    miState* 			state,
	    const MI::SHADER::Brdf*	msl_brdf
	    ) const;


    /// \brief Releases a \c Bsdf created by \c Metasl_interface::allocBsdf.
    ///
    /// This function is used to release \c mi::shader::Bsdf instances that
    /// were allocated through \c Metasl_interface::allocBsdf.
    virtual void releaseBsdf(
	    miState*			state,
	    const Bsdf*			bsdf
	    ) const;


    /// \brief Runs the given MetaSL \c Brdf as a traditional shader.
    ///
    /// This function can be used to implement mental ray shaders that use
    /// MetaSL \c Brdfs.
    /// The wrapper shader supports material and photon shading modes.
    virtual bool runBsdf(
	    miColor*			result,
	    miState*			state,
	    const MI::SHADER::Brdf*	msl_brdf
	    ) const;
};

/// \brief \c Metasl_interface wrapper class
class Access_metasl
{
public:
    /// \brief constructor
    Access_metasl()
    : m_ptr(mi_get_metasl_interface())
    {}

    // pointer operator
    Metasl_interface* operator->()
    {
	return m_ptr;
    }

    // release
    ~Access_metasl()
    {
	m_ptr->release();
    }

private:
    Metasl_interface* m_ptr;
};

/// \brief \c State wrapper class
class Access_state : public MI::SHADER::Smart_ptr<MI::SHADER::State>
{
    typedef MI::SHADER::Smart_ptr<MI::SHADER::State> Super;
public:
    /// \brief constructor
    Access_state(miState* state)
    : Super(Access_metasl()->getState(state))
    {}
};



}}



#endif

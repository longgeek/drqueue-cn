//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/base/plugin.h
/// \brief Base class for all plugins
///
//*****************************************************************************

#include <mi/base/types.h>

#ifndef MI_BASE_PLUGIN_H
#define MI_BASE_PLUGIN_H

namespace mi
{

namespace base
{

/// Every plugin must be derived from this class. It provides some virtual
/// functions which can be used to get information about the plugin. The
/// get_type function is used to be able to have different classes which are
/// derived from Plugin, which provide different interfaces in addition to the
/// interface defined by Plugin.

class Plugin
{
public:
    // The currently used plugin system version.
    static const Sint32 m_version = 2;

    /// Get the version of the plugin system used to compile this. This can be
    /// useful when the plugin system is extended/changed at some point to
    /// be able to still support older plugins or at least to reject them. The
    /// only thing which must not be changed is that the first virtual function
    /// is this.
    ///
    /// \return The version number of the plugin.
    virtual Sint32 get_plugin_system_version() { return 2; }

    /// Get the name of the plugin.
    ///
    /// \return A string containing the name of the plugin.
    virtual const char* get_name() const = 0;

    /// Get a type string for the plugin (e.g. "image" for image plugins).
    ///
    /// \return A string containing the plugin type.
    virtual const char* get_type() const = 0;

    /// Get the version of the plugin.
    ///
    /// \return The version number of the plugin.
    virtual Sint32 get_version() const;

    /// Get the compiler used to compile the plugin.
    ///
    /// \return A string describing the compiler used to compile the plugin.
    virtual const char* get_compiler() const;

    /// Release the plugin giving back all allocated resources.
    virtual void release();

    /// Used to return arbitrary key / value pairs. The caller can iterate over
    /// all such existing pairs by calling with indexes starting at 0 and increasing
    /// by 1 until the call returns 0. The string returned should be static.
    /// This allows a plugin to return arbitrary data.
    ///
    /// \param index The index to query.
    /// \param value A static string containing the return value.
    virtual const char* get_string_property(
        Sint32 index,                           // the index to query
        const char** value) { return 0; }       // the value or 0

  protected:
    // Destructor.
    virtual ~Plugin() {}
};

/// Get the version of the plugin.
inline Sint32 Plugin::get_version() const
{
    return 1;
}

/// Get the compiler used to compile the plugin.
inline const char* Plugin::get_compiler() const
{
    return "unknown";
}

/// Release the plugin giving back all allocated resources.
inline void Plugin::release()
{
    delete this;
}

} // namespace base

} // namespace mi

#endif // MI_BASE_PLUGIN_H

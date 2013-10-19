///////////////////////////////////////////////////////////////////////////////
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
///////////////////////////////////////////////////////////////////////////////
// Created:	27.02.08
// Module:	api
// Purpose:	mental ray C++ shader interface extensions
///////////////////////////////////////////////////////////////////////////////

/// \file shader_map.h
/// mental ray C++ shader interface extensions.
///
/// This file provides interfaces that allow interaction with map primitives.
///
/// shader_map.h is included by mi_shader_if.h, which in turn is 
/// included from shader.h if the shader is compiled as C++ code.
/// A shader does not need to include this file directly.


#ifndef SHADER_MAP_H
#define SHADER_MAP_H

#include "mi_shader_if.h"

namespace mi {
namespace shader_v3 {

/// \brief Map_status class.
///
/// \brief The Map_status is an enumerative class which is meant to list
/// all possible error conditions for the Map-related classes and methods.
///
class Map_status {
    public:
	/// \brief all the status codes.
	enum Status_code {
	    OK = 0,			///< OK

	    Insufficient_memory,	///< out of memory
	    No_such_field,		///< the specified field doesn't exist
	    Out_of_bounds,		///< map element index is out of bounds
	    No_declaration,		///< map or map element with no declaration
	    Declaration_mismatch,	///< differing declarations
	    Wrong_dimension,		///< wrong dimension for map element

	    File_could_not_be_opened = 16,  ///< I/O error
	    File_not_a_map,		    ///< the specified file is not a map
	    File_version_unsupported,	    ///< unsupported map version in map file
	    
	    Field_undefined = 32,	///< undefined map field type
	    Field_name_too_long,	///< map field name is too long
	    Field_name_empty,		///< empty map field name
	    Field_name_illegal,		///< illegal name for map field
	    Field_null_array,		///< array with zero length
	    Field_type_mismatch,	///< get/set field value of the wrong type
	    Field_illegal,		///< illegal field

	    Iterator_invalid = 48,	///< map iterator not attached to a map
	    Iterator_past_end,		///< map iterator past the end
	    Iterator_out_of_bounds,	///< map iterator is out of bounds
	    
	    Lookup_invalid = 64,	///< map lookup not attached to a map
	    Lookup_past_end,		///< map lookup past the end
	    Lookup_out_of_bounds,	///< map lookup is out of bounds
	    Lookup_dimension_mismatch	///< dist functor for search has wrong dim
	};

	/// \brief constructor, initializes to OK.
	Map_status()
	    : m_status(OK)
	{}

	/// \brief constructor from a Status_code.
	/// \param status is the assigned Status_code
	Map_status(Status_code status)
	    : m_status(status)
	{}

	/// \brief copy constructor.
	/// \param status is the Map_status to copy
	Map_status(const Map_status& status)
	    : m_status(status.m_status)
	{}

	/// \brief copy assignment operator (Status_code).
	/// \param rhs the Status_code to copy
	/// \return a reference to itself
	Map_status& operator=(const Status_code& rhs)
	{m_status=rhs;return *this;}

	/// \brief copy assignment operator (Map_status).
	/// \param rhs the Map_status to copy
	/// \return a reference to itself
	Map_status& operator=(const Map_status& rhs)
	{m_status=rhs.m_status;return *this;}

	/// \brief equality operator (Status_code).
	/// \param rhs is the Status_code to compare to
	/// \return true if equal, false if different
	bool operator==(const Status_code rhs) const
	{return m_status==rhs;}

	/// \brief equality operator (Map_status).
	/// \param rhs is the Map_status to compare to
	/// \return true if equal, false if different
	bool operator==(const Map_status& rhs) const
	{return m_status==rhs.m_status;}

	/// \brief inequality operator (Status_code).
	/// \param rhs is the Status_code to compare to
	/// \return true if different, false if equal
	bool operator!=(const Status_code rhs) const
	{return m_status!=rhs;}

	/// \brief inequality operator (Map_status).
	/// \param rhs is the Map_status to compare to
	/// \return true if different, false if equal
	bool operator!=(const Map_status& rhs) const
	{return m_status!=rhs.m_status;}
	
	/// \brief returns if the status is OK or not.
	/// \return a boolean
	bool is_ok() const
	{return m_status==OK;}

	/// \brief returns the status code as Status_code.
	/// \return the status code as Status_code
	Status_code status() const
	{return m_status;}

    private:
	/// \brief m_status is the status code.
	Status_code m_status;
};

/// \brief Map_field_type class.
///
/// \brief The Map_field_type is an enumerative class which is meant to
/// list all possible field types for maps.
///
class Map_field_type {
    public:
	/// \brief all the map field types.
	enum Type {
	    Undefined = 0,	    ///< undefined type

	    Scalar,		    ///< single-precision float
	    Integer,		    ///< integer
	    Vector,		    ///< 3-dimensional vector (XYZ)
	    Color,		    ///< 4-dimensional color (RGBA)
	    Transform,		    ///< 4x4 matrix

	    Scalar_array = 16,	    ///< array of single-precision floats
	    Integer_array,	    ///< array of integers
	    String		    ///< string
	};

	/// \brief constructor, unassigned Type.
	Map_field_type()
	    : m_type(Undefined)
	{}

	/// \brief constructor from a Type.
	/// \param type is the assigned Type
	Map_field_type(Type type)
	    : m_type(type)
	{}

	/// \brief copy constructor.
	/// \param type is the Map_field_type to copy
	Map_field_type(const Map_field_type& type)
	    : m_type(type.m_type)
	{}

	/// \brief copy assignment operator (Type).
	/// \param rhs the Type to copy
	/// \return a reference to itself
	Map_field_type& operator=(const Type& rhs)
	{m_type=rhs;return *this;}

	/// \brief copy assignment operator (Map_field_type).
	/// \param rhs the Map_field_type to copy
	/// \return a reference to itself
	Map_field_type& operator=(const Map_field_type& rhs)
	{m_type=rhs.m_type;return *this;}

	/// \brief equality operator (Type).
	/// \param rhs is the Type to compare to
	/// \return true if equal, false if different
	bool operator==(const Type rhs) const
	{return m_type==rhs;}

	/// \brief equality operator (Map_field_type).
	/// \param rhs is the Map_field_type to compare to
	/// \return true if equal, false if different
	bool operator==(const Map_field_type& rhs) const
	{return m_type==rhs.m_type;}

	/// \brief inequality operator (Type).
	/// \param rhs is the Type to compare to
	/// \return true if different, false if equal
	bool operator!=(const Type rhs) const
	{return m_type!=rhs;}

	/// \brief inequality operator (Map_field_type).
	/// \param rhs is the Map_field_type to compare to
	/// \return true if different, false if equal
	bool operator!=(const Map_field_type& rhs) const
	{return m_type!=rhs.m_type;}

	/// \brief returns the field type as Type.
	/// \return the field type as a Type
	Type type() const
	{return m_type;}

    private:
	/// \brief m_type is the field type.
	Type m_type;
};

/// \brief Map_field_id.
///
typedef miUint Map_field_id;

/// forward declarations
class Map_declaration;
class Map_element;
class Map_lookup;

/// \brief Map_base class.
///
/// \brief The Map_base class is an interface class which provides access
/// to a map, to its elements through the use of get/set methods and to its
/// declaration, and it also provides ways to read/write maps from/to files.
/// There are two wrapper classes which provide a convenient way to manage
/// this class: the Access_map class (read-only access to a map) and the
/// Edit_map class (read-write access to a map).
/// For example, a shader might access and use a map in the following way:
/// \code
/// Access_map map (tag);
///
/// if (!map->is_empty()) { ... }
/// \endcode
///
class Map_base {
    public:
	/// \brief returns the number of elements in the map.
	/// \return the number of elements in the map
	virtual miUint size() const = 0;

	/// \brief returns true if the map is empty.
	/// \return true if the map is empty, false otherwise
	virtual bool is_empty() const = 0;

	/// \brief returns true if the map has a declaration.
	/// \return true if the map has a declaration, false otherwise
	virtual bool has_declaration() const = 0;

	/// \brief gets the copy of an element.
	/// \param index is the desired element index
	/// \param map_element is the map element which will hold the copy
	/// \return a status code
	virtual Map_status get(
	    const miUint    index,
	    Map_element	    &map_element) const = 0;

	/// \brief sets the desired element in the map.
	/// \param index is the index of the element to set
	/// \param map_element is the map element
	/// \return a status code
	virtual Map_status set(
	    const miUint	index,
	    const Map_element	&map_element) = 0;

	/// \brief appends the desired element at the end.
	/// \param map_element is the map element to append
	/// \return a status code
	virtual Map_status append(
	    const Map_element	&map_element) = 0;

	/// \brief reads a map from a file.
	/// \param file_name is the name of the file to read
	/// \param notify is a flag, if true then notify messages will be printed
	/// \return a status code
	virtual Map_status read(
	    const char	*file_name,
	    const bool	notify = true) = 0;

	/// \brief appends the map to the existing file.
	/// \param file_name is the name of the file to append to
	/// \param notify is a flag, if true then notify messages will be printed
	/// \return a status code
	virtual Map_status append_to(
	    const char	*file_name,
	    const bool	notify = true) const = 0;

	/// \brief appends the contents of the file to the map.
	/// \param file_name is the name of the file to read
	/// \param notify is a flag, if true then notify messages will be printed
	/// \return a status code
	virtual Map_status append_from(
	    const char	*file_name,
	    const bool	notify = true) = 0;

	/// \brief writes the map to file.
	/// \param file_name is the name of the file to write
	/// \param notify is a flag, if true then notify messages will be printed
	/// \return a status code
	virtual Map_status write(
	    const char	*file_name,
	    const bool	notify = true) const = 0;

	/// \brief takes into account all the appended elements
	/// and rebuilds the map BVH
	/// \param bvh_quality is the quality of the BVH, between 0 and 1
	/// \return a status code
	virtual Map_status consolidate(
	    const float	bvh_quality = 0.6f) = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the float output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		&value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the integer output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			&value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the vector output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miVector		&value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the color output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miColor		&value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired global field
	/// \param value is the transform output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miMatrix		*value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the float array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		*value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the integer array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			*value) const = 0;

	/// \brief retrieves the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the string output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    char		*value) const = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the float input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const float		value) = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the integer input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const int		value) = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the vector input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miVector	&value) = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the color input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miColor	&value) = 0;

	/// \brief sets the value of the desired global field.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired global field
	/// \param value is the transform input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miMatrix	*value) = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the float array input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const float		*value) = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the integer array input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const int		*value) = 0;

	/// \brief sets the value of the desired global field.
	/// \param field_id is the id of the desired global field
	/// \param value is the string input value
	/// \param length is the amount of characters to write, if \< 0 then
	/// only the characters up to the first '\\0' will be copied
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const char		*value,
	    const int		length = -1) = 0;
};

/// \brief Access_map_dbhandle class, not to be used directly
/// (use Access_map instead).
///
class Access_map_dbhandle {
public:
    /// \brief dereference operator.
    /// \return the map object
    virtual const Map_base * operator->() = 0;

    /// \brief deletes the object and releases the map.
    virtual void release() const = 0;

    /// \brief returns the tag of the map in the DB.
    /// \return the tag of the map in the DB, or 0 if not in the DB
    virtual miTag get_tag() const = 0;

    /// \brief stores the map in the DB (if not in the DB already).
    /// \return the tag of the map in the DB
    virtual miTag store() = 0;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Access_map_dbhandle.
typedef Access_map_dbhandle Map_dbhandle_access;

/// \brief Smart pointer (access-only) to a map in the DB or to a map
/// to be read from file. It defines a dereference operator which provides
/// access to the const methods of the wrapped Map_base object.
///
class Access_map {
public:
    /// \brief smart pointer to a map in the DB.
    /// \param tag is the map database tag
    Access_map(
	const miTag tag);

    /// \brief smart pointer to a map to be read from file.
    /// \param filename file name of the map to read
    /// \param status a status code
    Access_map(
	const char *filename,
	Map_status *status = 0);

    /// \brief release resources, unpin DB tag (if in the DB).
    ~Access_map();

    /// \brief dereference operator.
    /// \return the map object
    const Map_base * operator->();

    /// \brief const dereference operator.
    /// \return the map object
    const Map_base * operator->() const;

    /// \brief returns the tag of the map in the DB.
    /// \return the tag of the map in the DB, or 0 if not in the DB
    miTag get_tag() const;

    /// \brief stores the map in the DB (if not in the DB already).
    /// \return the tag of the map in the DB
    miTag store();

private:
    Access_map();
    Access_map(const Access_map &);
    const Access_map & operator=(const Access_map &);

    Access_map_dbhandle *m_map_h;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Access_map.
typedef Access_map Map_access;

/// \brief Edit_map_dbhandle class, not to be used directly
/// (use Edit_map instead).
///
class Edit_map_dbhandle {
public:
    /// \brief dereference operator.
    /// \return the map object
    virtual Map_base * operator->() = 0;

    /// \brief deletes the object and releases the map.
    virtual void release() const = 0;

    /// \brief returns the tag of the map in the DB.
    /// \return the tag of the map in the DB, or 0 if not in the DB
    virtual miTag get_tag() const = 0;

    /// \brief stores the map in the DB (if not in the DB already).
    /// \return the tag of the map in the DB
    virtual miTag store() = 0;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Edit_map_dbhandle.
typedef Edit_map_dbhandle Map_dbhandle_edit;

/// \brief Smart pointer (read/write) to a map in the DB, to a map
/// to be read from file, or to a newly created one.
/// It defines a dereference operator which provides access to the
/// methods of the wrapped Map_base object.
///
class Edit_map {
public:
    /// \brief smart pointer to a new empty map.
    /// \param map_declaration is the declaration of the new map
    Edit_map(
	const Map_declaration &map_declaration);

    /// \brief smart pointer to a new empty map (with no declaration).
    Edit_map();

    /// \brief smart pointer to a map in the DB.
    /// \param tag is the map database tag
    Edit_map(
	const miTag tag);

    /// \brief smart pointer to a map to be read from file.
    /// \param filename file name of the map to read
    /// \param status a status code
    Edit_map(
	const char *filename,
	Map_status *status = 0);

    /// \brief release resources, unpin DB tag (if in the DB).
    ~Edit_map();

    /// \brief dereference operator.
    /// \return the map object
    Map_base * operator->();

    /// \brief const dereference operator.
    /// \return the map object
    const Map_base * operator->() const;

    /// \brief returns the tag of the map in the DB.
    /// \return the tag of the map in the DB, or 0 if not in the DB
    miTag get_tag() const;

    /// \brief stores the map in the DB (if not in the DB already).
    /// \return the tag of the map in the DB
    miTag store();

private:
    Edit_map(const Edit_map &);
    const Edit_map & operator=(const Edit_map &);

    Edit_map_dbhandle *m_map_h;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Edit_map.
typedef Edit_map Map_edit;

/// \brief Map_declaration_base class.
///
/// \brief The Map_declaration_base class is an interface class which
/// provides ways to add/query map field names and ids in a map declaration.
/// There is a wrapper class which provides a convenient way to manage
/// this class, which is the Map_declaration class.
/// For example, a shader might create and use a map declaration in the
/// following way:
/// \code
/// // declaration of a 3-dimensional map
/// Map_declaration declaration (3);
///
/// declaration->add_color ("color");
/// declaration->add_scalar ("intensity");
/// ...
///
/// // creates a map which has the declaration just built
/// Edit_map map (declaration);
/// ...
/// \endcode
///
class Map_declaration_base {
    public:
	/// \brief deletes the object.
	virtual void release() const = 0;

	/// \brief returns the total number of fields (excluding the
	/// position), global and element (non-global) fields.
	/// \return the number of total fields in the declaration
	virtual miUint get_fields() const = 0;

	/// \brief returns the number of element fields (excluding the position).
	/// \return the number of element fields in the declaration
	virtual miUint get_element_fields() const = 0;

	/// \brief returns the number of global fields.
	/// \return the number of global fields in the declaration
	virtual miUint get_global_fields() const = 0;

	/// \brief returns true if the declaration is empty,
	/// excluding the position (which is always there).
	/// \return true if it's empty, false otherwise
	virtual bool is_empty() const = 0;

	/// \brief returns the dimension of the position.
	/// \return the dimension of the position
	virtual miUint get_dimension() const = 0;

	/// \brief returns true if the declaration is equivalent to
	/// the given one, that is same field types and in the same
	/// order, though names can be different.
	/// \param other is the declaration to compare to
	/// \param status is a pointer to a status code
	/// \return true if they are equivalent, false otherwise
	virtual bool is_equivalent(
	    const Map_declaration   &other,
	    Map_status		    *status = 0) const = 0;

	/// \brief returns true if the declaration matches exactly
	/// the given one, that is same field types, in the same
	/// order and with the same names.
	/// \param other is the declaration to compare to
	/// \param status is a pointer to a status code
	/// \return true if they match, false otherwise
	virtual bool matches(
	    const Map_declaration   &other,
	    Map_status		    *status = 0) const = 0;

	/// \brief returns true if the declaration has a field with
	/// the given name (global or not).
	/// \param name is the name of the field to look for
	/// \param status is a pointer to a status code
	/// \return true if it has a field with such name, false otherwise
	virtual bool has_field(
	    const char	*name,
	    Map_status	*status = 0) const = 0;

	/// \brief returns true if the field with the given name is
	/// a global field.
	/// \param name is the name of the field
	/// \param status is a pointer to a status code
	/// \return true if it is a global field, false otherwise
	virtual bool is_global(
	    const char	*name,
	    Map_status	*status = 0) const = 0;

	/// \brief returns true if the field with the given id is
	/// a global field.
	/// \param field_id is the id of the field
	/// \param status is a pointer to a status code
	/// \return true if it is a global field, false otherwise
	virtual bool is_global(
	    const Map_field_id	field_id,
	    Map_status		*status = 0) const = 0;

	/// \brief returns the name of the desired field.
	/// \param field_id is the id of the desired field
	/// \param status is the optional returned status code
	/// \return the name of the desired field
	virtual const char* get_field_name(
	    const Map_field_id	field_id,
	    Map_status		*status = 0) const = 0;

	/// \brief returns the id of the field with the given name.
	/// \param field_name is the name of the desired field
	/// \param status is the optional returned status code
	/// \return the id of the field with the given name
	virtual Map_field_id get_field_id(
	    const char	    *field_name,
	    Map_status	    *status = 0) const = 0;

	/// \brief returns the id of the element field with the given
	/// index (between 0 and get_element_fields()-1)
	/// \param index is the index of the desired element field
	/// \param status is the optional returned status code
	/// \return the id of the field
	virtual Map_field_id get_element_field_id(
	    const miUint    index,
	    Map_status	    *status = 0) const = 0;

	/// \brief returns the id of the global field with the given
	/// index (between 0 and get_global_fields()-1)
	/// \param index is the index of the desired global field
	/// \param status is the optional returned status code
	/// \return the id of the field
	virtual Map_field_id get_global_field_id(
	    const miUint    index,
	    Map_status	    *status = 0) const = 0;

	/// \brief returns the type and the dimension of the desired field,
	/// and a flag that says if the field is global or not.
	/// \param field_id is the id of the desired field
	/// \param field_type is the returned type
	/// \param field_dimension is the returned dimension
	/// \param field_global is a flag, true if the field is global
	/// \return a status code
	virtual Map_status get_field_info(
	    const Map_field_id	field_id,
	    Map_field_type	&field_type,
	    miUint		&field_dimension,
	    bool		&field_global) const = 0;

	/// \brief returns the type and the dimension of the desired field,
	/// and a flag that says if the field is global or not.
	/// \param field_name is the name of the desired field
	/// \param field_type is the returned type
	/// \param field_dimension is the returned dimension
	/// \param field_global is a flag, true if the field is global
	/// \return a status code
	virtual Map_status get_field_info(
	    const char		*field_name,
	    Map_field_type	&field_type,
	    miUint		&field_dimension,
	    bool		&field_global) const = 0;

	/// \brief adds an element field with the given name, type and
	/// (possible) dimension (ignored in case of non-array types).
	/// \param name is the field name
	/// \param type is the field type
	/// \param dim is the dimension (ignored for non-arrays)
	/// \return a status code
	virtual Map_status add(
	    const char		    *name,
	    const Map_field_type    type,
	    const miUint	    dim = 0) = 0;

	/// \brief adds an element scalar field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_scalar(
	    const char	    *name) = 0;

	/// \brief adds an element integer field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_integer(
	    const char	    *name) = 0;

	/// \brief adds an element vector field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_vector(
	    const char	    *name) = 0;

	/// \brief adds an element color field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_color(
	    const char	    *name) = 0;

	/// \brief adds an element transform field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_transform(
	    const char	    *name) = 0;

	/// \brief adds an element scalar array field with the given name.
	/// \param name is the field name
	/// \param dim is the dimension of the array
	/// \return a status code
	virtual Map_status add_scalar_array(
	    const char	    *name,
	    const miUint    dim) = 0;

	/// \brief adds an element integer array field with the given name.
	/// \param name is the field name
	/// \param dim is the dimension of the array
	/// \return a status code
	virtual Map_status add_integer_array(
	    const char	    *name,
	    const miUint    dim) = 0;

	/// \brief adds a global field with the given name, type and
	/// (possible) dimension (meaningful only for arrays and strings).
	/// \param name is the field name
	/// \param type is the field type
	/// \param dim is the dimension (ignored for non-arrays)
	/// \return a status code
	virtual Map_status add_global(
	    const char		    *name,
	    const Map_field_type    type,
	    const miUint	    dim = 0) = 0;

	/// \brief adds a global scalar field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_global_scalar(
	    const char	    *name) = 0;

	/// \brief adds a global integer field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_global_integer(
	    const char	    *name) = 0;

	/// \brief adds a global vector field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_global_vector(
	    const char	    *name) = 0;

	/// \brief adds a global color field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_global_color(
	    const char	    *name) = 0;

	/// \brief adds a global transform field with the given name.
	/// \param name is the field name
	/// \return a status code
	virtual Map_status add_global_transform(
	    const char	    *name) = 0;

	/// \brief adds a global scalar array field with the given name.
	/// \param name is the field name
	/// \param dim is the dimension of the array
	/// \return a status code
	virtual Map_status add_global_scalar_array(
	    const char	    *name,
	    const miUint    dim) = 0;

	/// \brief adds a global integer array field with the given name.
	/// \param name is the field name
	/// \param dim is the dimension of the array
	/// \return a status code
	virtual Map_status add_global_integer_array(
	    const char	    *name,
	    const miUint    dim) = 0;

	/// \brief adds a global string field with the given name.
	/// \param name is the field name
	/// \param dim is the dimension of the array
	/// \return a status code
	virtual Map_status add_global_string(
	    const char	    *name,
	    const miUint    dim) = 0;
};

/// \brief Smart pointer to a map declaration, which allows to
/// retrieve a copy of the declaration of an existing map, or
/// to create a new map declaration.
/// It defines a dereference operator which provides access to the
/// methods of the wrapped Map_declaration_base object.
///
class Map_declaration {
public:
    /// \brief smart pointer to a new map declaration.
    /// \param dimension is the dimension of the position
    Map_declaration(
	const miUint dimension=3);

    /// \brief gets a copy of the declaration of the given map.
    /// \param map is the map to get a copy of the declaration from
    /// \param status is a status code
    Map_declaration(
	const Access_map &map,
	Map_status *status = 0);

    /// \brief gets a copy of the declaration of the given map.
    /// \param map is the map to get a copy of the declaration from
    /// \param status is a status code
    Map_declaration(
	const Edit_map &map,
	Map_status *status = 0);

    /// \brief gets a copy of the declaration of the given element.
    /// \param map_element element to get a copy of the declaration from
    /// \param status is a status code
    Map_declaration(
	const Map_element &map_element,
	Map_status *status = 0);

    /// \brief copy constructor.
    /// \param other is the declaration to copy
    /// \param status is a status code
    Map_declaration(
	const Map_declaration &other,
	Map_status *status = 0);

    /// \brief destructor, deletes the declaration.
    ~Map_declaration();

    /// \brief copy assignment operator.
    /// \param other is the declaration to copy
    Map_declaration & operator=(
	const Map_declaration &other);

    /// \brief dereference operator.
    /// \return the map declaration object
    Map_declaration_base * operator->();

    /// \brief const dereference operator.
    /// \return the map declaration object
    const Map_declaration_base * operator->() const;

private:
    Map_declaration_base *m_map_declaration;
};

/// \brief Map_element_base class.
///
/// \brief The Map_element_base class is an interface class that
/// represents a map element, which is an isolated and independent
/// piece of data, made up by a declaration and a set of values for
/// its fields. It provides ways to get/set the values of the fields.
/// There is a wrapper class which provides a convenient way to manage
/// this class, which is the Map_element class.
/// For example, a shader might create and use a map element in the
/// following way:
/// \code
/// // creates a map element which has the specified declaration
/// Map_element element (declaration);
///
/// miVector pos = ...;
/// element->set_position (pos);
///
/// miColor color = ...;
/// element->set (color_field_id, color);
/// ...
///
/// \endcode
///
class Map_element_base {
    public:
	/// \brief deletes the object.
	virtual void release() const = 0;

	/// \brief sets the declaration of the element.
	/// \param declaration is the handle of the declaration
	/// \return a status code
	virtual Map_status set_declaration(
	    const Map_declaration&  declaration) = 0;

	/// \brief retrieves the position of the element.
	/// \param position is the output array
	/// \return a status code
	virtual Map_status get_position(
	    float		*position) const = 0;

	/// \brief retrieves the position of the element, 3D case.
	/// \param position is the output vector
	/// \return a status code
	virtual Map_status get_position(
	    miVector		&position) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the float output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		&value) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the integer output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			&value) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the vector output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miVector		&value) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the color output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miColor		&value) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired field
	/// \param value is the pointer to the transform output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miMatrix		*value) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the float array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		*value) const = 0;

	/// \brief retrieves the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the integer array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			*value) const = 0;

	/// \brief sets the position of the element.
	/// \param position is the input array
	/// \return a status code
	virtual Map_status set_position(
	    const float		*position) = 0;

	/// \brief sets the position of the element, 3D case.
	/// \param position is the input vector
	/// \return a status code
	virtual Map_status set_position(
	    const miVector	&position) = 0;

	/// \brief sets the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the float input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const float		value) = 0;

	/// \brief sets the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the integer input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const int		value) = 0;

	/// \brief sets the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the vector input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miVector	&value) = 0;

	/// \brief sets the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the color input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miColor	&value) = 0;

	/// \brief sets the value of the desired field.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired field
	/// \param value is the pointer to the transform input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miMatrix	*value) = 0;

	/// \brief sets the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the float array input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const float		*value) = 0;

	/// \brief sets the value of the desired field.
	/// \param field_id is the id of the desired field
	/// \param value is the integer array input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const int		*value) = 0;
};

/// \brief Smart pointer to a map element.
/// It defines a dereference operator which provides access to the
/// methods of the wrapped Map_element_base object.
///
class Map_element {
public:
    /// \brief smart pointer to a new empty map element,
    /// without a declaration attached.
    Map_element();

    /// \brief smart pointer to a new map element which
    /// has the given declaration.
    /// \param declaration is the declaration of the new map element
    Map_element(
	const Map_declaration& declaration);

    /// \brief copy constructor.
    /// \param other is the element to copy
    Map_element(
	const Map_element &other);

    /// \brief destructor, deletes the element.
    ~Map_element();

    /// \brief copy assignment operator.
    /// \param other is the element to copy
    Map_element & operator=(
	const Map_element &other);

    /// \brief dereference operator.
    /// \return the map element object
    Map_element_base * operator->(); 

    /// \brief const dereference operator.
    /// \return the map element object
    const Map_element_base * operator->() const; 

private:
    Map_element_base *m_map_element;
};

/// \brief Map_iterator_base class.
///
/// \brief The Map_iterator_base class is an interface class which provides
/// access to the elements of the map without having to copy them first.
/// The constness of its methods refers actually to the constness
/// of the map it's attached to, not to the constness of the iterator
/// itself: for instance, the 'set' methods are non-const because
/// they change the map, even if they don't change the iterator state;
/// conversely, the 'reset' method is const even if it does change
/// the state of the iterator, but the map itself is untouched.
/// There are two wrapper classes which provide a convenient way to manage
/// this class: the Access_map_iterator class (iterator with read-only access
/// to a map) and the Edit_map_iterator class (iterator with read-write access
/// to a map).
/// For example, a shader might attach a map iterator to a map and use it
/// in the following way:
/// \code
/// // 'map' is a Access_map. 'it' is attached to the map, and it points
/// // to the first element of the map
/// Access_map_iterator it (map);
///
/// for ( ; !it->at_end() ; it->next() )   { ... }
/// \endcode
///
class Map_iterator_base {
    public:
	/// \brief deletes the object.
	virtual void release() const = 0;

	/// \brief resets itself to point to the first element.
	/// \return a status code
	virtual Map_status reset() const = 0;

	/// \brief moves to the desired element.
	/// \param index is the index of the element to move to
	/// \return a status code
	virtual Map_status set_to(
	    const miUint    index) const = 0;

	/// \brief moves to the next element.
	/// \return a status code
	virtual Map_status next() const = 0;

	/// \brief moves to the previous element.
	/// \return a status code
	virtual Map_status previous() const = 0;

	/// \brief skips the desired number of elements.
	/// \param amount is the number of elements to skip
	/// \return a status code
	virtual Map_status skip(
	    const miUint    amount) const = 0;

	/// \brief returns true if it's beyond the end.
	/// \param status is a status code
	/// \return true if it's beyond the end, false otherwise
	virtual bool at_end(
	    Map_status	*status = 0) const = 0;

	/// \brief returns the index of the element it points to.
	/// \param status is a status code
	/// \return the index of the current element
	virtual miUint current(
	    Map_status	*status = 0) const = 0;

	/// \brief returns a copy of the current element.
	/// \param element is the element which will hold the copy
	/// \return a status code
	virtual Map_status get(
	    Map_element		&element) const = 0;

	/// \brief retrieves the position of the current element.
	/// \param position is the output array
	/// \return a status code
	virtual Map_status get_position(
	    float		*position) const = 0;

	/// \brief retrieves the position of the current element, 3D case.
	/// \param position is the output vector
	/// \return a status code
	virtual Map_status get_position(
	    miVector		&position) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the float output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the integer output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the vector output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miVector		&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the color output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miColor		&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired field
	/// \param value is the pointer to the transform output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miMatrix		*value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the float array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		*value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the integer array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			*value) const = 0;

	/// \brief sets the current element.
	/// \param element is the element to set
	/// \return a status code
	virtual Map_status set(
	    const Map_element	&element) = 0;

	/// \brief sets the position of the current element.
	/// \param position is the input array
	/// \return a status code
	virtual Map_status set_position(
	    const float		*position) = 0;

	/// \brief sets the position of the current element, 3D case.
	/// \param position is the input vector
	/// \return a status code
	virtual Map_status set_position(
	    const miVector	&position) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the float input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const float		value) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the integer input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const int		value) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the vector input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miVector	&value) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the color input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miColor	&value) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired field
	/// \param value is the pointer to the transform output value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const miMatrix	*value) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the float array input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const float		*value) = 0;

	/// \brief sets the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the integer array input value
	/// \return a status code
	virtual Map_status set(
	    const Map_field_id	field_id,
	    const int		*value) = 0;
};

/// forward declaration
class Edit_map_iterator;

/// \brief Smart pointer to an access-only map iterator.
/// It defines a dereference operator which provides access to the const
/// methods of the wrapped Map_iterator_base object.
///
class Access_map_iterator {
public:
    /// \brief attaches the iterator to a read-only map.
    /// \param map is the map to attach to
    /// \param status is a status code
    Access_map_iterator(
	const Access_map &map,
	Map_status *status = 0);

    /// \brief attaches the iterator to a map.
    /// \param map is the map to attach to
    /// \param status is a status code
    Access_map_iterator(
	const Edit_map &map,
	Map_status *status = 0);

    /// \brief copy constructor.
    /// \param other is the iterator to copy
    /// \param status is a status code
    Access_map_iterator(
	const Access_map_iterator &other,
	Map_status *status = 0);

    /// \brief copy constructor.
    /// \param other is the iterator to copy
    /// \param status is a status code
    Access_map_iterator(
	const Edit_map_iterator &other,
	Map_status *status = 0);

    /// \brief destructor, deletes the iterator.
    ~Access_map_iterator();

    /// \brief copy assignment operator.
    /// \param other is the iterator to copy
    Access_map_iterator & operator=(
	const Access_map_iterator &other);

    /// \brief copy assignment operator.
    /// \param other is the iterator to copy
    Access_map_iterator & operator=(
	const Edit_map_iterator &other);

    /// \brief dereference operator.
    /// \return the map iterator object
    const Map_iterator_base * operator->(); 

private:
    Map_iterator_base *m_map_iterator;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Access_map_iterator.
typedef Access_map_iterator Map_iterator_access;

/// \brief Smart pointer to a read-write map iterator.
/// It defines a dereference operator which provides access to the
/// methods of the wrapped Map_iterator_base object.
///
class Edit_map_iterator {
public:
    /// \brief attaches the iterator to a map.
    /// \param map is the map to attach to
    /// \param status is a status code
    Edit_map_iterator(
	const Edit_map &map,
	Map_status *status = 0);

    /// \brief copy constructor.
    /// \param other is the iterator to copy
    /// \param status is a status code
    Edit_map_iterator(
	const Edit_map_iterator &other,
	Map_status *status = 0);

    /// \brief destructor, deletes the iterator.
    ~Edit_map_iterator();

    /// \brief copy assignment operator.
    /// \param other is the iterator to copy
    Edit_map_iterator & operator=(
	const Edit_map_iterator &other);

    /// \brief dereference operator.
    /// \return the map iterator object
    Map_iterator_base * operator->(); 

    /// \brief const dereference operator.
    /// \return the map iterator object
    const Map_iterator_base * operator->() const; 

private:
    Map_iterator_base *m_map_iterator;
};

/// \brief Typedef for backwards compatibility.
///
/// \deprecated Replaced by \c Edit_map_iterator.
typedef Edit_map_iterator Map_iterator_edit;

/// \brief Map_distance_base class.
///
/// \brief The Map_distance_base class is an interface class for all
/// the lookup distance functors.
///
class Map_distance_base {
public:
    /// \brief returns the dimension of the functor.
    /// \return the dimension of the functor
    virtual miUint get_dimension() const = 0;

    /// \brief returns the search point.
    /// \return a pointer to the search point
    virtual const float *get_point() const = 0;

    /// \brief returns the distance from a bounding box.
    /// \param min is the minimum point of the bounding box
    /// \param max is the maximum point of the bounding box
    /// \return the distance from the bounding box
    virtual float operator() (
	const float *min,
	const float *max) const = 0;

    /// \brief returns the distance from an element.
    /// \param element is the current element
    /// \return the distance from the element
    virtual float operator() (
	const Map_iterator_base *element) const = 0;
};


/// \brief Map_distance<DIM> class.
///
/// \brief The Map_distance class is an interface template class,
/// which defines all the virtual methods of Map_distance_base class
/// except the distance from an element.
/// \brief The distance from a bounding box is quadratic.
///
template<miUint DIM>
class Map_distance : public mi::shader_v3::Map_distance_base {
public:
    /// \brief DIMENSION of the distance functor, same of the map.
    static const miUint DIMENSION = DIM;

    /// \brief empty constructor.
    Map_distance()
    {}

    /// \brief constructor.
    /// \param point is the search point
    Map_distance(
	const float *point)
    {
	for (miUint i = 0; i < DIMENSION; ++i)
	    m_point[i] = point[i];
    }

    /// \brief returns the dimension of the functor.
    /// \return the dimension of the functor
    miUint get_dimension() const { return DIMENSION; }

    /// \brief returns the search point.
    /// \return a pointer to the search point
    const float *get_point() const { return m_point; }

    /// \brief returns the quadratic distance from a bounding box.
    /// \param min is the minimum point of the bounding box
    /// \param max is the maximum point of the bounding box
    /// \return the quadratic distance from the bounding box
    float operator() (
	const float *min,
	const float *max) const
    {
	float d = 0.0f;
	float da, db, max_da_db, tmp;

	for (miUint i = 0; i < DIMENSION; ++i) {
	    da = min[i] - m_point[i];
	    db = m_point[i] - max[i];

	    max_da_db = da > db ? da : db;
	    tmp = max_da_db > 0.0f ? max_da_db : 0.0f;

	    d += tmp * tmp;
	}

	return d;
    }

    /// \brief returns the quadratic distance from an element.
    /// \param element is the current element
    /// \return the quadratic distance from the element
    virtual float operator() (
	const Map_iterator_base *element) const = 0;

protected:
    /// \brief m_point is the search point
    float m_point[DIM];
};

/// \brief Map_quad_distance class.
///
/// \brief The Map_quad_distance functor is a concrete distance
/// functor that defines the operator that returns the distance
/// from an element (quadratic distance).
///
template<miUint DIM>
class Map_quad_distance : public mi::shader_v3::Map_distance<DIM> {
public:
    /// \brief constructor.
    /// \param point is the search point
    Map_quad_distance(
	const float *point)
	: Map_distance<DIM>::Map_distance(point)
    {}

    /// \brief returns the quadratic distance from an element.
    /// \param element is the current element
    /// \return the quadratic distance from the element
    float operator() (
	const Map_iterator_base *element) const
    {
	float d = 0.0f;
	float diff;
	float position[DIM];

	element->get_position(position);

	for (miUint i = 0; i < DIM; ++i) {
	    diff = this->m_point[i] - position[i];
	    d += diff * diff;
	}

	return d;
    }
};

/// \brief predefined quadratic distance functor for the 3-dimensional case.
///
typedef Map_quad_distance<3> Map_quad_distance3;

/// \brief an entry in a map lookup, the index of an element
/// and its distance from the search point.
///
struct Map_lookup_entry {
    /// \brief index of the element in the map.
    miUint  index;

    /// \brief distance of the element from the search point.
    float   distance;
};

/// \brief Map_lookup_base class.
///
/// \brief The Map_lookup_base class is an interface class which provides access
/// (read-only) to elements which are the result of a lookup inside a map.
/// Searches are run inside a map by calling the 'search' method which
/// takes a Map_distance_base distance functor as argument, provided by the
/// user, or by calling the 'search' method which takes a miVector as argument.
/// There is a wrapper class which provides a convenient way to manage
/// this class, which is the Map_lookup class.
/// For example, a shader might attach a map lookup to a map and use it
/// in the following way:
/// \code
/// // 'map' is a Access_map. Attaches a lookup to a map
/// Map_lookup lookup (map);
///
/// miVector point = ...;
///
/// // looks for the closest 10 elements to the given point
/// lookup->search (point, 10);
///
/// // loops through all the found elements, like an iterator,
/// // but accessing only the elements which have been found
/// // in the search
/// for ( ; !lookup->at_end() ; lookup->next() )    { ... }
///
/// \endcode
///
class Map_lookup_base {
    public:
	/// \brief deletes the object.
	virtual void release() const = 0;

	/// \brief returns the number of elements in the lookup.
	/// \return the number of elements in the lookup
	virtual miUint size() const = 0;

	/// \brief returns true if the lookup is empty.
	/// \return true if the lookup has no entries, false otherwise
	virtual bool is_empty() const = 0;

	/// \brief resets itself to point to the first element.
	/// \return a status code
	virtual Map_status reset() = 0;

	/// \brief moves to the next element.
	/// \return a status code
	virtual Map_status next() = 0;

	/// \brief returns true if it's beyond the end.
	/// \param status is a status code
	/// \return true if it's beyond the end, false otherwise
	virtual bool at_end(
	    Map_status	*status = 0) const = 0;

	/// \brief sorts the elements in ascending order of distance.
	/// \return a status code
	virtual Map_status sort() = 0;

	/// \brief sorts the elements in descending order of distance.
	/// \return a status code
	virtual Map_status sort_descending() = 0;

	/// \brief returns the n-th entry of the lookup.
	/// \param n is the index of the desired entry
	/// \param status is a status code
	/// \return the n-th entry of the lookup
	virtual Map_lookup_entry get(
	    const miUint    n,
	    Map_status	    *status = 0) const = 0;

	/// \brief returns the current lookup entry.
	/// \param status is a status code
	/// \return the current lookup entry
	virtual Map_lookup_entry get(
	    Map_status	*status = 0) const = 0;

	/// \brief returns the index in the map of the current element.
	/// \param status is a status code
	/// \return the index in the map of the current element
	virtual miUint get_index(
	    Map_status	*status = 0) const = 0;

	/// \brief returns the distance of the current element.
	/// \param status is a status code
	/// \return the distance of the current element
	virtual float get_distance(
	    Map_status	*status = 0) const = 0;

	/// \brief returns a copy of the current element.
	/// \param element is the element which will hold the copy
	/// \return a status code
	virtual Map_status get(
	    Map_element	&element) const = 0;

	/// \brief retrieves the position of the current element.
	/// \param position is the output array
	/// \return a status code
	virtual Map_status get_position(
	    float	*position) const = 0;

	/// \brief retrieves the position of the current element, 3D case.
	/// \param position is the output vector
	/// \return a status code
	virtual Map_status get_position(
	    miVector	&position) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the float output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the integer output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the vector output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miVector		&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field
	/// \param value is the color output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miColor		&value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \brief NOTE: 'value' is a pointer to a miMatrix.
	/// \param field_id is the id of the desired field
	/// \param value is the pointer to the transform output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    miMatrix		*value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field.
	/// \param value is the float array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    float		*value) const = 0;

	/// \brief retrieves the value of the desired field
	/// of the current element.
	/// \param field_id is the id of the desired field.
	/// \param value is the integer array output value
	/// \return a status code
	virtual Map_status get(
	    const Map_field_id	field_id,
	    int			*value) const = 0;

	/// \brief searches for the closest elements to a given point.
	/// \param distance_functor provides search point and distances
	/// \param max_elements max num of elements to return
	/// \param max_search_dist is the max search distance
	/// from point, in the same metric as the distance functor
	/// \return a status code
	virtual Map_status search(
	    const Map_distance_base &distance_functor,
	    const miUint	max_elements = 1,
	    const float		max_search_dist = miHUGE_SCALAR) = 0;

	/// \brief searches for the closest elements to a given point,
	/// specialized case of the above for a simple quadratic
	/// distance in 3D.
	/// \param point is the three dimensional search point
	/// \param max_elements max num of elements to return
	/// \param max_search_dist is the max search distance
	/// from the point (quadratic)
	/// \return a status code
	virtual Map_status search(
	    const miVector	&point,
	    const miUint	max_elements = 1,
	    const float		max_search_dist = miHUGE_SCALAR) = 0;
};

/// \brief Smart pointer to a map lookup.
/// It defines a dereference operator which provides access to the
/// methods of the wrapped Map_lookup_base object.
///
class Map_lookup {
public:
    /// \brief attaches the lookup to a read-only map.
    /// \param map is the map to attach to
    /// \param status is a status code
    Map_lookup(
	const Access_map &map,
	Map_status *status = 0);

    /// \brief copy constructor.
    /// \param other is the lookup to copy
    /// \param status is a status code
    Map_lookup(
	const Map_lookup &other,
	Map_status *status = 0);

    /// \brief destructor, deletes the lookup.
    ~Map_lookup();

    /// \brief copy assignment operator.
    /// \param other is the lookup to copy
    Map_lookup & operator=(
	const Map_lookup &other);

    /// \brief dereference operator.
    /// \return the map lookup object
    Map_lookup_base * operator->(); 

private:
    Map_lookup_base* m_map_lookup;
};

/// \brief Access_map wrapper class.
///
inline Access_map::Access_map(
    const miTag tag)
    : m_map_h(0)
{
    m_map_h = Access_interface()->accessMap(tag);
}

inline Access_map::Access_map(
    const char *filename,
    Map_status *status)
    : m_map_h(0)
{
    m_map_h = Access_interface()->accessMap(filename, status);
}

inline Access_map::~Access_map()
{
    if(m_map_h != 0)
	m_map_h->release();
}

inline const Map_base * Access_map::operator->()
{
    if(m_map_h != 0){
	return (*m_map_h).operator->();
    }
    return 0;
}

inline const Map_base * Access_map::operator->() const
{
    if(m_map_h != 0){
	return (*m_map_h).operator->();
    }
    return 0;
}

inline miTag Access_map::get_tag() const
{
    if(m_map_h != 0){
	return m_map_h->get_tag();
    }
    return 0;
}

inline miTag Access_map::store()
{
    if(m_map_h != 0){
	return m_map_h->store();
    }
    return 0;
}

/// \brief Edit_map wrapper class.
///
inline Edit_map::Edit_map(
    const Map_declaration &map_declaration)
    : m_map_h(0)
{
    m_map_h = Access_interface()->createMap(map_declaration.operator->());
}

inline Edit_map::Edit_map()
    : m_map_h(0)
{
    m_map_h = Access_interface()->createMap();
}

inline Edit_map::Edit_map(
    const miTag tag)
    : m_map_h(0)
{
    m_map_h = Access_interface()->editMap(tag);
}

inline Edit_map::Edit_map(
    const char *filename,
    Map_status *status)
    : m_map_h(0)
{
    m_map_h = Access_interface()->editMap(filename, status);
}

inline Edit_map::~Edit_map()
{
    if(m_map_h != 0)
	m_map_h->release();
}

inline Map_base * Edit_map::operator->()
{
    if(m_map_h != 0){
	return (*m_map_h).operator->();
    }
    return 0;
}

inline const Map_base * Edit_map::operator->() const
{
    if(m_map_h != 0){
	return (*m_map_h).operator->();
    }
    return 0;
}

inline miTag Edit_map::get_tag() const
{
    if(m_map_h != 0){
	return m_map_h->get_tag();
    }
    return 0;
}

inline miTag Edit_map::store()
{
    if(m_map_h != 0){
	return m_map_h->store();
    }
    return 0;
}

/// \brief Map_declaration wrapper class.
///
inline Map_declaration::Map_declaration(
    miUint dimension)
    : m_map_declaration(0)
{
    m_map_declaration = Access_interface()->createMapDeclaration(
	dimension);
}

inline Map_declaration::Map_declaration(
    const Access_map &map,
    Map_status *status)
    : m_map_declaration(0)
{
    m_map_declaration = Access_interface()->copyMapDeclaration(
	map.operator->(), status);
}

inline Map_declaration::Map_declaration(
    const Edit_map &map,
    Map_status *status)
    : m_map_declaration(0)
{
    m_map_declaration = Access_interface()->copyMapDeclaration(
	map.operator->(), status);
}

inline Map_declaration::Map_declaration(
    const Map_element &map_element,
    Map_status *status)
    : m_map_declaration(0)
{
    m_map_declaration = Access_interface()->copyMapDeclaration(
	map_element.operator->(), status);
}

inline Map_declaration::Map_declaration(
    const Map_declaration &other,
    Map_status *status)
    : m_map_declaration(0)
{
    m_map_declaration = Access_interface()->copyMapDeclaration(
	other.m_map_declaration, status);
}

inline Map_declaration & Map_declaration::operator=(
    const Map_declaration &other)
{
    if (m_map_declaration != 0)
	m_map_declaration->release();
    m_map_declaration = Access_interface()->copyMapDeclaration(
	other.m_map_declaration, 0);
    return *this;
}

inline Map_declaration::~Map_declaration()
{
    if (m_map_declaration != 0)
	m_map_declaration->release();
}

inline Map_declaration_base * Map_declaration::operator->()
{
    return m_map_declaration;
}

inline const Map_declaration_base * Map_declaration::operator->() const
{
    return m_map_declaration;
}

/// \brief Map_element wrapper class.
///
inline Map_element::Map_element()
    : m_map_element(0)
{
    m_map_element = Access_interface()->createMapElement();
}

inline Map_element::Map_element(
    const Map_declaration &declaration)
    : m_map_element(0)
{
    m_map_element = Access_interface()->createMapElement(
	declaration.operator->());
}

inline Map_element::Map_element(
    const Map_element &other)
    : m_map_element(0)
{
    m_map_element = Access_interface()->copyMapElement(
	other.m_map_element);
}

inline Map_element & Map_element::operator=(
    const Map_element &other)
{
    m_map_element->release();
    m_map_element = Access_interface()->copyMapElement(
	other.m_map_element);
    return *this;
}

inline Map_element::~Map_element()
{
    m_map_element->release();
}

inline Map_element_base * Map_element::operator->()
{
    return m_map_element;
}

inline const Map_element_base * Map_element::operator->() const
{
    return m_map_element;
}

/// \brief Access_map_iterator wrapper class.
///
inline Access_map_iterator::Access_map_iterator(
    const Access_map &map,
    Map_status *status)
    : m_map_iterator(0)
{
    m_map_iterator = Access_interface()->createMapIterator(
	map.operator->(), status);
}

inline Access_map_iterator::Access_map_iterator(
    const Edit_map &map,
    Map_status *status)
    : m_map_iterator(0)
{
    m_map_iterator = Access_interface()->createMapIterator(
	map.operator->(), status);
}

inline Access_map_iterator::Access_map_iterator(
    const Access_map_iterator &other,
    Map_status *status)
    : m_map_iterator(0)
{
    m_map_iterator = Access_interface()->copyMapIterator(
	other.m_map_iterator, status);
}

inline Access_map_iterator::Access_map_iterator(
    const Edit_map_iterator &other,
    Map_status *status)
    : m_map_iterator(0)
{
    m_map_iterator = Access_interface()->copyMapIterator(
	other.operator->(), status);
}

inline Access_map_iterator & Access_map_iterator::operator =(
    const Access_map_iterator &other)
{
    m_map_iterator->release();
    m_map_iterator = Access_interface()->copyMapIterator(
	other.m_map_iterator, 0);
    return *this;
}

inline Access_map_iterator & Access_map_iterator::operator =(
    const Edit_map_iterator &other)
{
    if (m_map_iterator != 0)
	m_map_iterator->release();
    m_map_iterator = Access_interface()->copyMapIterator(
	other.operator->(), 0);
    return *this;
}

inline Access_map_iterator::~Access_map_iterator()
{
    if (m_map_iterator != 0)
	m_map_iterator->release();
}

inline const Map_iterator_base * Access_map_iterator::operator->()
{
    return m_map_iterator;
}

/// \brief Edit_map_iterator wrapper class.
///
inline Edit_map_iterator::Edit_map_iterator(
    const Edit_map &map,
    Map_status *status)
    : m_map_iterator(0)
{
    m_map_iterator = Access_interface()->createMapIterator(
	map.operator->(), status);
}

inline Edit_map_iterator::Edit_map_iterator(
    const Edit_map_iterator &other,
    Map_status *status)
    : m_map_iterator(0)
{
    m_map_iterator = Access_interface()->copyMapIterator(
	other.m_map_iterator, status);
}

inline Edit_map_iterator & Edit_map_iterator::operator =(
    const Edit_map_iterator &other)
{
    if (m_map_iterator != 0)
	m_map_iterator->release();
    m_map_iterator = Access_interface()->copyMapIterator(
	other.m_map_iterator, 0);
    return *this;
}

inline Edit_map_iterator::~Edit_map_iterator()
{
    if (m_map_iterator != 0)
	m_map_iterator->release();
}

inline Map_iterator_base * Edit_map_iterator::operator->()
{
    return m_map_iterator;
}

inline const Map_iterator_base * Edit_map_iterator::operator->() const
{
    return m_map_iterator;
}

/// \brief Map_lookup wrapper class.
///
inline Map_lookup::Map_lookup(
    const Access_map &map,
    Map_status *status)
    : m_map_lookup(0)
{
    m_map_lookup = Access_interface()->createMapLookup(
	map.operator->(), status);
}

inline Map_lookup::Map_lookup(
    const Map_lookup &other,
    Map_status *status)
    : m_map_lookup(0)
{
    m_map_lookup = Access_interface()->copyMapLookup(
	other.m_map_lookup, status);
}

inline Map_lookup::~Map_lookup()
{
    if (m_map_lookup != 0)
	m_map_lookup->release();
}

inline Map_lookup & Map_lookup::operator = (
    const Map_lookup &other)
{
    if (m_map_lookup != 0)
	m_map_lookup->release();
    m_map_lookup = Access_interface()->copyMapLookup(
	other.m_map_lookup, 0);
    return *this;
}

inline Map_lookup_base * Map_lookup::operator->()
{
    return m_map_lookup;
}

} // namespace shader_v3
} // namespace mi

#endif //SHADER_MAP_H

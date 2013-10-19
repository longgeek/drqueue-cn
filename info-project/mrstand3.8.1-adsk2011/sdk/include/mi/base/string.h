//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/base/string.h
/// \brief String class with \c char character type, see \ref mi_base_string.
///
//*****************************************************************************

#ifndef MI_BASE_STRING_H
#define MI_BASE_STRING_H

#include <mi/base/config.h>
#include <mi/base/assert.h>
#include <mi/base/types.h>
#include <cstring>

namespace mi
{

namespace base
{

// An undocumented allocator interface. At this point it is only meant for and
// used by the mi::base::string class in this file. Might change its API or
// might get replaced by a different interface.
//
class IAllocator
{
public:
    // Allocate a memory block of the given size. This function can
    // be called at any time from any thread, including concurrent
    // calls from several threads at the same time.  If the requested
    // memory can not be returned this function must return NULL. 
    // 
    // The memory must be aligned to an address which can accommodate
    // any type of object on the operating system where the library
    // runs.
    //
    // \param  size     The requested memory size in bytes.
    // \return          A pointer to the allocated memory block.
    virtual void* malloc(Size size) = 0;

    // Release the given memory block. This function can be called at
    // any time from any thread, including concurrent calls from
    // several threads at the same time.
    //
    // \param memory The memory block previously allocated by a call to 
    // \c IAllocator::malloc.
    virtual void free(void* memory) = 0;
};

// An undocumented default implementation for the allocator interface above.
// Uses a static member variable in a static inline method to have an
// implementation in the header only. Singleton.
class Default_allocator : public IAllocator {
    Default_allocator() {}
    Default_allocator( const Default_allocator&) {}
public:

    virtual void* malloc(Size size) {
        return new char[size];
    }

    virtual void free(void* memory) {
        delete[] reinterpret_cast<char*>(memory);
    }

    static IAllocator* get_instance() {
        // We claim that this is multithreading safe because the
        // Default_allocator has an empty default constructor.
        // Whatever number of threads gets into the constructor, there
        // should be no way to screw up the initialization in each
        // thread. The optimizer might even be able to eliminate all
        // code here.
        static Default_allocator allocator;
        return &allocator;
    }
};


/** \defgroup mi_base_string String Class
    \ingroup mi_base
    \brief

       \par Include File:
       <tt> \#include <mi/base/string.h></tt>

    @{
 */

/// String class with \c char character type.
///
/// The string class provides basic construction and conversion from and to
/// <tt>const char*</tt> C-type strings and concatenation. The operations
/// provided follow the definition for a \c std::string class.
///
/// The string class contains an optimization for short strings. It does not
/// contain optimizations for copying strings, such as reference counting.
///
class String {
    // on the CELL platform, the string class has SHORT_SIZE as fixed size limit.
public:
    typedef char          value_type;      ///< Character type
    typedef Size          size_type;       ///< Size type
    typedef Difference    difference_type; ///< Difference type

    typedef char&         reference;       ///< Reference type
    typedef const char&   const_reference; ///< Const-reference type
    typedef char*         pointer;         ///< Pointer type
    typedef const char*   const_pointer;   ///< Const-pointer type

    typedef pointer       iterator;        ///< Random-access iterator type
    typedef const_pointer const_iterator;  ///< Random-access const-iterator type

    static const Size npos = Size(-1);     ///< Null position

    /// Maximum length of strings (incl. trailing \c '\\0' ) stored without
    /// additional dynamic memory allocation.
    // on the CELL platform, the string class has SHORT_SIZE as fixed size limit.
    static const Size SHORT_SIZE = 24;

private:

    // Length of the string.
    Size m_length;

    // Pointer to allocator object
    IAllocator *m_allocator;

    // Pointer to the string.
    char *m_string;

    // Buffer for strings allocated on the stack.
    char m_short_string_buffer[SHORT_SIZE];

    // Allocates size many bytes. Throws an exception if allocation fails.
    // static char* allocate( Size size) { return new char[size]; } // OLD
    char* allocate( Size size)
    {
        return reinterpret_cast<char*>(m_allocator->malloc( size));
    }

    // Deallocates the memory \p buf, which must be allocated with the
    // \c allocate function. \p buf may be zero, in which case nothing is
    // deallocated.
    // static void deallocate( char* buf) { delete[] buf; } // OLD
    void deallocate( char* buf) { m_allocator->free(buf); }

public:

    /// Default constructor initializes to the empty string.
    inline String()
            : m_length(0),
              m_allocator( Default_allocator::get_instance()),
              m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
    }

    inline String( IAllocator* allocator)
            : m_length(0),
              m_allocator( allocator),
              m_string(m_short_string_buffer)
    {
        mi_base_assert( allocator != 0);
        m_short_string_buffer[0] = '\0';
    }

    /// Constructor that copies the string \p str.
    // TODO: Add a variant with an allocator arg
    inline String( const char* str)
        : m_allocator( Default_allocator::get_instance())
    {
#ifdef MI_CELL
        if(str) {
            m_length = (Size)MISTD::strlen(str);
            if(m_length < SHORT_SIZE) {
                MISTD::strcpy(m_short_string_buffer,str);
                m_string = m_short_string_buffer;
            }
        } else {
            m_length = 0;
            m_string = m_short_string_buffer;
            m_short_string_buffer[0] = '\0';
        }
#else
        if(str) {
            m_length = (Size)MISTD::strlen(str);
            if(m_length < SHORT_SIZE) {
                MISTD::strcpy(m_short_string_buffer,str);
                m_string = m_short_string_buffer;
            } else {
                m_string = allocate( m_length + 1);
                MISTD::strcpy(m_string,str);
                m_short_string_buffer[0] = '\0';
            }
        } else {
            m_length = 0;
            m_string = m_short_string_buffer;
            m_short_string_buffer[0] = '\0';
        }
#endif
    }

    /// Copy constructor that copies the string \p str.
    // TODO: Add a variant with an allocator arg
    inline String( const String& str)
        : m_allocator( Default_allocator::get_instance())
    {
#ifdef MI_CELL
        m_length = str.length();
        if(m_length < SHORT_SIZE) {
            MISTD::strcpy(m_short_string_buffer, str.m_short_string_buffer);
            m_string = m_short_string_buffer;
        }
#else
        m_length = str.length();
        if(m_length < SHORT_SIZE) {
            MISTD::strcpy(m_short_string_buffer, str.m_short_string_buffer);
            m_string = m_short_string_buffer;
        } else {
            m_string = allocate( m_length + 1);
            MISTD::strcpy(m_string, str.m_string);
            m_short_string_buffer[0] = '\0';
        }
#endif
    }

    /// Assignment, assign \p str to this string.
    inline String& operator=( const String& str)
    {
#ifdef MI_CELL
        m_length = str.length();
        if(m_length < SHORT_SIZE) {
            MISTD::strcpy(m_short_string_buffer, str.m_short_string_buffer);
            m_string = m_short_string_buffer;
        }
#else
        m_length = str.length();
        if(m_length < SHORT_SIZE) {
            MISTD::strcpy(m_short_string_buffer, str.m_short_string_buffer);
            m_string = m_short_string_buffer;
        } else {
            if ( this != & str) {
                if(m_string != m_short_string_buffer)
                    deallocate( m_string);
                m_string = allocate( m_length + 1);
                MISTD::strcpy(m_string, str.m_string);
                m_short_string_buffer[0] = '\0';
            }
        }
#endif
        return *this;
    }

    /// Destructor.
    inline ~String()
    {
#ifndef MI_CELL
        if(m_string != m_short_string_buffer)
            deallocate( m_string);
#endif
    }

    /// Returns \c true if this string has \c size()==0 .
    inline bool empty() const
    {
        return m_length == Size(0);
    }

    /// Returns the number of characters in the string
    /// (excluding the \c '\\0' terminator)
    inline Size size() const
    {
        return m_length;
    }

    /// Returns the number of characters in the string
    /// (excluding the \c '\\0' terminator)
    inline Size length() const
    {
        return m_length;
    }

    /// Returns a non-null pointer to the C-style terminated string
    /// representation of this string.
    inline const char* c_str() const
    {
        return m_string;
    }

    /// Returns the <tt>i</tt>-th character of the string. The character at
    /// position \c size() is always \c '\\0'. Precondition: \p i<=size().
    inline const char& operator[] ( Size i) const
    {
        mi_base_assert_msg(i <= size(), "precondition");
        return m_string[i];
    }

    /// Returns the <tt>i</tt>-th character of the string. The character at
    /// position \c size() is always \c '\\0'; it is not permissible to write
    /// to that position. Precondition: \p i<=size().
    inline char& operator[] ( Size i)
    {
        mi_base_assert_msg(i <= size(), "precondition");
        return m_string[i];
    }

    /// Appends \c str to this string.
    inline String& operator+= ( const String& str)
    {
#ifdef MI_CELL
        Size nl = length() + str.length();
        if(nl < SHORT_SIZE) {
            MISTD::strcat(m_short_string_buffer, str.m_short_string_buffer);
        }
#else
        Size nl = length() + str.length();
        if(nl < SHORT_SIZE) {
            MISTD::strcat(m_short_string_buffer, str.m_short_string_buffer);
        } else {
            char *result = allocate( nl+1);
            MISTD::strcpy(result, m_string);
            MISTD::strcat(result, str.m_string);
            if(m_string != m_short_string_buffer)
                deallocate( m_string);
            m_string = result;
            m_short_string_buffer[0] = '\0';
        }
        m_length = nl;
#endif
        return *this;
    }
};

/// Equality.
inline bool operator==(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return (left.length() == right.length())
        && !MISTD::strcmp(left.c_str(),right.c_str());
}

/// Inequality.
inline bool operator!=(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return !(left == right);
}

/// Less than.
inline bool operator<(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return MISTD::strcmp(left.c_str(),right.c_str()) < 0;
}

/// Less than or equal.
inline bool operator<=(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return MISTD::strcmp(left.c_str(),right.c_str()) <= 0;
}

/// Greater than or equal.
inline bool operator>=(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return 0 <= MISTD::strcmp(left.c_str(),right.c_str());
}

/// Greater than.
inline bool operator>(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return 0 < MISTD::strcmp(left.c_str(),right.c_str());
}

/// Concatenates two strings.
inline String operator+(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{

    String result(left);
    result += right;
    return result;
}


/*@}*/ // end group mi_base_string

} // namespace base
} // namespace mi

#endif // MI_BASE_STRING_H

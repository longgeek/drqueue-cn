/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_METASL_RUNTIME_MI_STRING_H
#define MI_METASL_RUNTIME_MI_STRING_H

#include <cstdio>
#include <cstring>

#include "vector.h"
#include "matrix.h"
#include "spectrum.h"
#include "mi_rdiff.h"

namespace MI {

namespace STRING {


// String class for C++ shaders generated from MetaSL.
class String {

private:

    // Maximum length of strings stored on the stack plus one.
    static const int s_short_string_size = 24;

    // Length of the string.
    Sint32 m_length;

    // Pointer to the string.
    char *m_string;

    // Buffer for strings allocated on the stack.
    char m_short_string_buffer[s_short_string_size];

    // Append a string to this string.
    void append(
        const String &right)    // The string to append.
    {
        Sint32 nl = length() + right.length();
        if(nl < s_short_string_size) {
            ::strcat(m_short_string_buffer,right.c_str());
        } else {
            char *result = new char[nl+1];
            ::strcpy(result,m_string);
            ::strcat(result,right.c_str());
            if(m_string != m_short_string_buffer)
                delete[] m_string;
            m_string = result;
            m_short_string_buffer[0] = '\0';
        }
        m_length = nl;
    }

    // Append a string to this string.
    void append(
        const char *right)      // The string to append.
    {
        Sint32 nl = length() + Sint32(strlen(right));
        if(nl < s_short_string_size) {
            ::strcat(m_short_string_buffer,right);
        } else {
            char *result = new char[nl+1];
            ::strcpy(result,m_string);
            ::strcat(result,right);
            if(m_string != m_short_string_buffer)
                delete[] m_string;
            m_string = result;
            m_short_string_buffer[0] = '\0';
        }
        m_length = nl;
    }

public:

    // Constructor.
    inline explicit String()
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
    }

    // Constructor.
    inline String(
        const String &str)      // The string to initailize with.
    {
        m_length = str.length();
        if(m_length < s_short_string_size) {
            ::strcpy(m_short_string_buffer,str.c_str());
            m_string = m_short_string_buffer;
        } else {
            m_string = new char[m_length + 1];
            ::strcpy(m_string,str.c_str());
            m_short_string_buffer[0] = '\0';
        }
    }

    // Constructor.
    inline explicit String(
        const char *str)        // The string to initialize with.
    {
        if(str) {
            m_length = (Sint32)strlen(str);
            if(m_length < s_short_string_size) {
                ::strcpy(m_short_string_buffer,str);
                m_string = m_short_string_buffer;
            } else {
                m_string = new char[m_length + 1];
                ::strcpy(m_string,str);
                m_short_string_buffer[0] = '\0';
            }
        } else {
            m_length = 0;
            m_string = m_short_string_buffer;
            m_short_string_buffer[0] = '\0';
        }
    }

    // Constructor.
    inline explicit String(bool b)  // The boolean to initialize with.
        : m_string(m_short_string_buffer)
    {
        strcpy(m_short_string_buffer,b ? "true" : "false");
        m_length = strlen(m_short_string_buffer);
    }

    // Constructor.
    inline explicit String(int n)    // The int to initialize with.
        : m_string(m_short_string_buffer)
    {
        sprintf(m_short_string_buffer,"%d",n);
        m_length = strlen(m_short_string_buffer);
    }

    // Constructor.
    inline explicit String(float f)  // The float to initialize with.
        : m_string(m_short_string_buffer)
    {
        sprintf(m_short_string_buffer,"%f",f);
        m_length = strlen(m_short_string_buffer);
    }

    // Constructor.
    inline explicit String(const MATH::Vector2b &v2b) // The vector to initialize
                                                // with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v2b.x;
        *this += " ";
        *this += v2b.y;
    }

    // Constructor.
    inline explicit String(const MATH::Vector3b &v3b) // The vector to initialize
                                                // with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v3b.x;
        *this += " ";
        *this += v3b.y;
        *this += " ";
        *this += v3b.z;
    }

    // Constructor.
    inline explicit String(const MATH::Vector4b &v4b) // The vector to initialize
                                                // with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v4b.x;
        *this += " ";
        *this += v4b.y;
        *this += " ";
        *this += v4b.z;
        *this += " ";
        *this += v4b.w;
    }

    // Constructor.
    inline explicit String(const MATH::Vector2i &v2i) // The vector to initialize
                                                // with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v2i.x;
        *this += " ";
        *this += v2i.y;
    }

    // Constructor.
    inline explicit String(const MATH::Vector3i &v3i) // The vector to initialize
                                                // with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v3i.x;
        *this += " ";
        *this += v3i.y;
        *this += " ";
        *this += v3i.z;
    }

    // Constructor.
    inline explicit String(const MATH::Vector4i &v4i) // The vector to initialize
                                                // with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v4i.x;
        *this += " ";
        *this += v4i.y;
        *this += " ";
        *this += v4i.z;
        *this += " ";
        *this += v4i.w;
    }

    // Constructor.
    inline explicit String(const MATH::Vector2 &v2) // The vector to initialize with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v2.x;
        *this += " ";
        *this += v2.y;
    }

    // Constructor.
    inline explicit String(const MATH::Vector3 &v3) // The vector to initialize with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v3.x;
        *this += " ";
        *this += v3.y;
        *this += " ";
        *this += v3.z;
    }

    // Constructor.
    inline explicit String(const MATH::Vector4 &v4) // The vector to initialize with.
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += v4.x;
        *this += " ";
        *this += v4.y;
        *this += " ";
        *this += v4.z;
        *this += " ";
        *this += v4.w;
    }

    // Constructor.
    inline explicit String(const MATH::Matrix2x2f &m2x2)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m2x2[0]);
        *this += " ";
        *this += String(m2x2[1]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix2x3f &m2x3)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m2x3[0]);
        *this += " ";
        *this += String(m2x3[1]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix2x4f &m2x4)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m2x4[0]);
        *this += " ";
        *this += String(m2x4[1]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix3x2f &m3x2)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m3x2[0]);
        *this += " ";
        *this += String(m3x2[1]);
        *this += " ";
        *this += String(m3x2[2]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix3x3f &m3x3)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m3x3[0]);
        *this += " ";
        *this += String(m3x3[1]);
        *this += " ";
        *this += String(m3x3[2]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix3x4f &m3x4)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m3x4[0]);
        *this += " ";
        *this += String(m3x4[1]);
        *this += " ";
        *this += String(m3x4[2]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix4x2f &m4x2)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m4x2[0]);
        *this += " ";
        *this += String(m4x2[1]);
        *this += " ";
        *this += String(m4x2[2]);
        *this += " ";
        *this += String(m4x2[3]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix4x3f &m4x3)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m4x3[0]);
        *this += " ";
        *this += String(m4x3[1]);
        *this += " ";
        *this += String(m4x3[2]);
        *this += " ";
        *this += String(m4x3[3]);
    }

    // Constructor.
    inline explicit String(const MATH::Matrix4x4f &m4x4)  // The matrix
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(m4x4[0]);
        *this += " ";
        *this += String(m4x4[1]);
        *this += " ";
        *this += String(m4x4[2]);
        *this += " ";
        *this += String(m4x4[3]);
    }

    // Constructor.
    inline explicit String(const COLOR::Spectrum &s)   // The spectrum
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(s.get(0));
        *this += " ";
        *this += String(s.get(1));
        *this += " ";
        *this += String(s.get(2));
    }

    // Constructor.
    inline explicit String(const RDIFF::Ray_struct &r) // The ray
        : m_length(0)
        , m_string(m_short_string_buffer)
    {
        m_short_string_buffer[0] = '\0';
        *this += String(r.org);
        *this += " ";
        *this += String(r.dir);
    }

    // Assignment.
    inline String &operator=(
        const String &str)      // The string to assign.
    {
        m_length = str.length();
        if(m_length < s_short_string_size) {
            ::strcpy(m_short_string_buffer,str.c_str());
            m_string = m_short_string_buffer;
        } else {
            if(m_string != m_short_string_buffer)
                delete[] m_string;
            m_string = new char[m_length + 1];
            ::strcpy(m_string,str.c_str());
            m_short_string_buffer[0] = '\0';
        }
        return *this;
    }

    // Destructor.
    inline ~String()
    {
        if(m_string != m_short_string_buffer)
            delete[] m_string;
    }

    // Length of string.
    inline Sint32 length() const
    {
        return m_length;
    }

    // Character pointer.
    inline const char *c_str() const
    {
        return m_string;
    }

    // Character pointer.
    inline operator const char *() const
    {
        return m_string;
    }

    // Append string.
    inline String &operator+=(
        const String &right)    // The string to append.
    {
        append(right);
        return *this;
    }

    // Append string.
    inline String &operator+=(
        const char *right)      // The string to append.
    {
        append(right);
        return *this;
    }

    // Append boolean.
    inline String &operator+=(
        bool right)             // The boolean to append.
    {
        if(right)
            append("true");
        else
            append("false");
        return *this;
    }

    // Append integer.
    inline String &operator+=(
        int right)              // The integer to append.
    {
        char buffer[32];

        ::sprintf(buffer,"%d",right);
        append(buffer);
        return *this;
    }


    // Append double.
    inline String &operator+=(
        double right)           // The double to append.
    {
        char buffer[32];

        ::sprintf(buffer,"%f",right);
        append(buffer);
        return *this;
    }

};

// Equality.
inline bool operator==(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return (left.length() == right.length()) && !::strcmp(left,right);
}

// Inequality.
inline bool operator!=(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return !(left == right);
}

// Less than.
inline bool operator<(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return ::strcmp(left,right) < 0;
}

// Less than or equal.
inline bool operator<=(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return ::strcmp(left,right) <= 0;
}

// Greater than or equal.
inline bool operator>=(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return 0 <= ::strcmp(left,right);
}

// Greater than.
inline bool operator>(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{
    return 0 < ::strcmp(left,right);
}

// Concatenate strings.
inline String operator+(
    const String &left,     // The left argument.
    const String &right)    // The right argument.
{

    String result(left);
    result += right;
    return result;
}

// Concatenate string and boolean.
inline String operator+(
    const String &left,     // The left argument.
    bool right)             // The right argument.
{

    String result(left);
    result += right;
    return result;
}

// Concatenate string and integer.
inline String operator+(
    const String &left,     // The left argument.
    int right)              // The right argument.
{

    String result(left);
    result += right;
    return result;
}

// Concatenate string and double.
inline String operator+(
    const String &left,     // The left argument.
    double right)           // The right argument.
{

    String result(left);
    result += right;
    return result;
}

}

}

#endif // MI_METASL_RUNTIME_MI_STRING_H

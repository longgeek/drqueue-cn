/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SMART_PTR_H
#define MI_SMART_PTR_H 1

namespace MI {
namespace SHADER {

//
// Smart pointer for interfaces
//
// A smart pointer class for keeping pointers to interfaces
// returned by the shader state with automatic reference counting.
//
// For example:
//
// Smart_ptr sampler_sp( state->get_sampler() );
// float x = sampler_sp->sample();
//

template <typename T>
class Smart_ptr
{
  public:
    // constructor
    explicit Smart_ptr(
        T* pointer = 0)             // pointer
    : m_pointer( pointer )
    {
        if (m_pointer)
            m_pointer->add_ref();
    }

    // copy constructor
    Smart_ptr(
        const Smart_ptr& sp)    // smart pointer
    : m_pointer( sp.m_pointer )
    {
        if (m_pointer)
            m_pointer->add_ref();
    }

    // destructor
    ~Smart_ptr()
    {
        if (m_pointer)
            m_pointer->release();
    }

    // set to NULL
    void reset(T* pointer = 0)
    {
        // self-assignment is handled implicitly

        // Add a reference to copied pointer
        if (pointer)
            pointer->add_ref();

        // Release previous pointer
        if (m_pointer)
            m_pointer->release();

        // Copy pointer
        m_pointer = pointer;
    }

    // assignment operator
    Smart_ptr& operator = (
        const Smart_ptr& sp)    // smart pointer
    {
        // Add a reference to copied pointer
        if (sp.m_pointer)
            sp.m_pointer->add_ref();

        // Release previous pointer
        if (m_pointer)
            m_pointer->release();

        // Copy pointer
        m_pointer = sp.m_pointer;
        return *this;
    }

    // check for null pointer
    bool is_valid() const {
        return m_pointer != 0;
    }

  private:
    typedef bool (Smart_ptr::*unspecified_bool_type)() const;
  public:

    // conversion to bool
    operator unspecified_bool_type() const
    {
        return is_valid() ? &Smart_ptr::is_valid : 0;
    }

    // Dereference the pointer. Fails an assertion if the object is empty.
    T&       operator *  ()
    {
        return *m_pointer;
    }

    T const& operator *  () const
    {
        return *m_pointer;
    }

    T*       operator -> ()
    {
        return m_pointer;
    }

    T const* operator -> () const
    {
        return m_pointer;
    }

    // Get access to the raw pointer. Use with care.
    T*       get()
    {
        return m_pointer;
    }

    T const* get() const
    {
        return m_pointer;
    }

  private:
    T*  m_pointer;
};

// equal operator for Smart_ptr
template<class T> inline bool operator==(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs.get() == rhs.get();
}
// not-equal operator for Smart_ptr
template<class T> inline bool operator!=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs.get() != rhs.get();
}
// less-than operator for Smart_ptr
template<class T> inline bool operator<(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs.get() < rhs.get();
}
// less-equal operator for Smart_ptr
template<class T> inline bool operator<=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs.get() <= rhs.get();
}
// greater-than operator for Smart_ptr
template<class T> inline bool operator>(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs.get() > rhs.get();
}
// greater-equal operator for Smart_ptr
template<class T> inline bool operator>=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs.get() >= rhs.get();
}

// equal operator for Smart_ptr
template<class T> inline bool operator==(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs)    // right hand-side instance
{
    return lhs.get() == rhs;
}
// not-equal operator for Smart_ptr
template<class T> inline bool operator!=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs)    // right hand-side instance
{
    return lhs.get() != rhs;
}
// less-than operator for Smart_ptr
template<class T> inline bool operator<(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs)    // right hand-side instance
{
    return lhs.get() < rhs;
}
// less-equal operator for Smart_ptr
template<class T> inline bool operator<=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs)    // right hand-side instance
{
    return lhs.get() <= rhs;
}
// greater-than operator for Smart_ptr
template<class T> inline bool operator>(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs)    // right hand-side instance
{
    return lhs.get() > rhs;
}
// greater-equal operator for Smart_ptr
template<class T> inline bool operator>=(
    Smart_ptr<T> const &        lhs,    // left hand-side instance
    T const *                   rhs)    // right hand-side instance
{
    return lhs.get() >= rhs;
}

// equal operator for Smart_ptr
template<class T> inline bool operator==(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs == rhs.get();
}
// not-equal operator for Smart_ptr
template<class T> inline bool operator!=(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs != rhs.get();
}
// less-than operator for Smart_ptr
template<class T> inline bool operator<(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs < rhs.get();
}
// less-equal operator for Smart_ptr
template<class T> inline bool operator<=(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs <= rhs.get();
}
// greater-than operator for Smart_ptr
template<class T> inline bool operator>(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs > rhs.get();
}
// greater-equal operator for Smart_ptr
template<class T> inline bool operator>=(
    T const *                   lhs,    // left hand-side instance
    Smart_ptr<T> const &        rhs)    // right hand-side instance
{
    return lhs >= rhs.get();
}


}}      // namespace MI::SHADER

#endif // MI_SMART_PTR_H


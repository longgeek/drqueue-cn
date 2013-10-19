/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_METASL_RUNTIME_MI_ARRAY_H
#define MI_METASL_RUNTIME_MI_ARRAY_H 1

#include "mi_types.h"

namespace MI {
namespace ARRAY {

template<typename T> class Array {

private:

    Uint32 count;       // The number of elements.
    T *data;            // The array of elements.
    bool owner;         // Flag to indicate if array owns data.

public:

    // Construct array.
    Array()
        : count(0)
        , data(0)
        , owner(false)
    {
    }

    // Construct array of _count elements.
    Array(
            Uint32 _count,  // The number of elements.
            T *_data)       // The array elements.
        : count(_count)
        , data(_data)
        , owner(false)
    {
    }

    // Copy constructor.
    Array(
            const Array &_other)    // The array to copy.
    {
        count = _other.count;
        data = new T[count];
        owner = true;
        for(Uint32 i = 0; i < count; i++)
            data[i] = _other.data[i];
    }

    // Copy constructor.
    template<typename U>
    Array(
            const Array<U> &_other)    // The array to copy.
    {
        count = _other.get_count();
        data = new T[count];
        owner = true;
        for(Uint32 i = 0; i < count; i++)
            data[i] = _other.get_data()[i];
    }

    // Destructor.
    ~Array()
    {
        if(owner)
            delete[] data;
    }

    // Copy assignment.
    Array<T> &operator=(
            Array<T> &_other)   // The array to assign.
    {
        if(this != &_other) {
            if(owner)
                delete[] data;
            count = _other.count;
            data = new T[count];
            owner = true;
            for(Uint32 i = 0; i < count; i++)
                data[i] = _other.data[i];
        }
        return *this;
    }

    // Copy assignment.
    template<typename U>
    Array<T> &operator=(
            Array<U> &_other)   // The array to assign.
    {
        if(this != &_other) {
            if(owner)
                delete[] data;
            count = _other.get_count();
            data = new T[count];
            owner = true;
            for(Uint32 i = 0; i < count; i++)
                data[i] = _other.get_data()[i];
        }
        return *this;
    }

    // Set the owner flag.
    void set_owner(
        bool _owner)    // The value to set.
    {
        owner = _owner;
    }

    // Set the element count.
    void set_count(
        Uint32 _count)  // The number of elements.
    {
        count = _count;
    }

    // Get the element count.
    Uint32 get_count() const
    {
        return count;
    }

    // Set the array of elements.
    void set_data(
        T *_data)       // The array of elements.
    {
        data = _data;
    }

    // Get the array of elements.
    T *get_data() const
    {
        return data;
    }

    // Select element i.
    T &operator[](
        Uint32 i)       // The element index.
    {
        return data[i];
    }

    // Select const element i.
    const T &operator[](
        Uint32 i) const     // The element index.
    {
        return data[i];
    }

};

}
}

#endif //  MI_METASL_RUNTIME_MI_ARRAY_H

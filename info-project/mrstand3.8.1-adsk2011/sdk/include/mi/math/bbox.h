/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/
/// \file mi/math/bbox.h
/// \brief An axis-aligned N-dimensional bounding box class template
///        of fixed dimension with supporting functions, see \ref mi_math_bbox.
///
//*****************************************************************************

#ifndef MI_MATH_BBOX_H
#define MI_MATH_BBOX_H

#include <mi/base/types.h>
#include <mi/math/assert.h>
#include <mi/math/function.h>
#include <mi/math/vector.h>
#include <mi/math/matrix.h>

namespace mi { namespace math {

/** \defgroup mi_math_bbox Bounding Box Class
    \ingroup mi_math
    An axis-aligned N-dimensional bounding box class template
    of fixed dimension with supporting functions.

       \par Include File:
       <tt> \#include <mi/math/bbox.h></tt>

    @{
*/

//------- POD struct that provides storage for bbox elements ----------

/** Storage class for an axis-aligned N-dimensional bounding box class
    template of fixed dimension.

    Use the \c mi::math::Bbox template in your programs and this storage class
    only if you need a POD type, for example for parameter passing.

    A bounding box is represented by two \c mi::math::Vector_struct vectors
    representing the elementwise minimal box corner, \c min, and
    the elementwise largest box corner, \c max.
*/
template <typename T, Size DIM>
struct Bbox_struct
{
    Vector_struct<T,DIM> min;  ///< elementwise minimal box corner
    Vector_struct<T,DIM> max;  ///< elementwise maximal box corner
};


/** Axis-aligned N-dimensional bounding box class template of fixed dimension.

    A bounding box is represented by two \c mi::math::Vector vectors
    representing the elementwise minimal box corner, \c min, and
    the elementwise largest box corner, \c max.

    An instantiation of the bounding box class template is a model of the
    STL container concept. It provides random access to its two
    vectors and corresponding random access iterators.

    The template parameters have the following requirements:
      - \b T: an arithmetic type supporting <tt>+ - * / == != < > <= >= </tt>.
      - \b DIM: a value > 0 of type \c Size that defines the fixed dimension
                of the vectors used to represent the bounding box.

    \see
        For the free functions and operators available for bounding boxes
        see \ref mi_math_bbox.
*/
template <typename T, Size DIM>
class Bbox
{
public:
    typedef math::Vector<T,DIM> Vector;         ///< Corresponding vector type.
    typedef Bbox_struct<T,DIM>  Pod_type;       ///< POD class corresponding to this bbox.
    typedef Vector         value_type;          ///< Coordinate type.
    typedef Size           size_type;           ///< Size type, unsigned.
    typedef Difference     difference_type;     ///< Difference type, signed.
    typedef Vector *       pointer;             ///< Mutable pointer to vector.
    typedef const Vector * const_pointer;       ///< Const pointer to vector.
    typedef Vector &       reference;           ///< Mutable reference to vector.
    typedef const Vector & const_reference;     ///< Const reference to vector.

    static const Size DIMENSION = DIM;          ///< Constant dimension of the vectors.
    static const Size SIZE      = 2;            ///< Constant size of the bounding box.

    /// Constant size of the bounding box.
    static inline Size size()     { return SIZE; }

    /// Constant maximum size of the bounding box.
    static inline Size max_size() { return SIZE; }

    /// Enum type used to tag a special constructor that does not initialize the
    /// elements of the constructed bounding box.
    enum Uninitialized_tag {
        /// Enum value used to call a special constructor that does not initialize
        /// the elements of the constructed bounding box.
        UNINITIALIZED_TAG
    };

    Vector min;  ///< elementwise minimal box corner
    Vector max;  ///< elementwise maximal box corner

    /// Reinitializes this bounding box to the empty space.
    /// The vector \c min is set elementwise to \c base::numeric_traits<T>::max()
    /// and the vector \c max is set elementwise to
    /// \c base::numeric_traits<T>::negative_max(). This initialization allows to
    /// insert points and other bounding boxes; a cleared bounding box will
    /// take the value of the first inserted point or bound box.
    inline void clear()
    {
        for (Size i = 0; i < DIM; i++) {
            min[i] =  base::numeric_traits<T>::max MI_PREVENT_MACRO_EXPAND ();
            max[i] =  base::numeric_traits<T>::negative_max();
        }
    }

    /// Bounding box initialized to the empty space, see also the clear function.
    /// The vector \c min is set elementwise to \c base::numeric_traits<T>::max()
    /// and the vector \c max is set elementwise to
    /// \c base::numeric_traits<T>::negative_max(). This initialization allows to
    /// insert points and other bounding boxes; a cleared bounding box will
    /// take the value of the first inserted point or bound box.
    inline Bbox() { clear(); }

    /// Bounding box with its elements not initialized.
    inline explicit Bbox( Uninitialized_tag) {}

    /// Bounding box initialized from corresponding POD type.
    inline Bbox( const Bbox_struct<T,DIM>& bbox_struct )
    {
        min = bbox_struct.min;
        max = bbox_struct.max;
    }

    /// Bounding box initialized to a single \c point.
    inline explicit Bbox(
        const Vector& point)    ///< point.
    {
        min = point;
        max = point;
    }

    /// Bounding box initialized to the new extreme corner vectors, \c nmin and \c nmax.
    inline Bbox(
        const Vector& nmin,     ///< \c min corner vector
        const Vector& nmax)     ///< \c max corner vector
    {
        min = nmin;
        max = nmax;
    }

    /// 1D bounding box (interval) initialized to the new extreme corner vectors,
    /// \c (min_x) and \c (max_x).
    /// Precondition: <tt>DIM == 1</tt>.
    inline Bbox(
        T min_x,                ///< x-coordinate of \c min corner vector
        T max_x)                ///< x coordinate of \c max corner vector
    {
        mi_static_assert(DIM == 1);
        min = Vector( min_x);
        max = Vector( max_x);
    }

    /// 2D bounding box (interval) initialized to the new extreme corner vectors,
    /// \c (min_x,min_y) and \c (max_x,max_y).
    /// Precondition: <tt>DIM == 2</tt>.
    inline Bbox(
        T min_x,                ///< x-coordinate of \c min corner vector
        T min_y,                ///< y-coordinate of \c min corner vector
        T max_x,                ///< x coordinate of \c max corner vector
        T max_y)                ///< y coordinate of \c max corner vector
    {
        mi_static_assert(DIM == 2);
        min = Vector( min_x, min_y);
        max = Vector( max_x, max_y);
    }

    /// 3D bounding box (interval) initialized to the new extreme corner vectors,
    /// \c (min_x,min_y,min_z) and \c (max_x,max_y,max_z).
    /// Precondition: <tt>DIM == 3</tt>.
    inline Bbox(
        T min_x,                ///< x-coordinate of \c min corner vector
        T min_y,                ///< y-coordinate of \c min corner vector
        T min_z,                ///< z-coordinate of \c min corner vector
        T max_x,                ///< x coordinate of \c max corner vector
        T max_y,                ///< y coordinate of \c max corner vector
        T max_z)                ///< z coordinate of \c max corner vector
    {
        mi_static_assert(DIM == 3);
        min = Vector( min_x, min_y, min_z);
        max = Vector( max_x, max_y, max_z);
    }

    /// Constructs a bbox from a range \c [first,last) of items. The value type of
    /// \c InputIterator can be either \c Vector to insert points, or it can
    /// be \c Bbox to insert bboxes.
    ///
    /// \param first   first element of the sequence to insert
    /// \param last    past-the-end position of sequence to insert
    template <typename InputIterator>
    Bbox(
        InputIterator first,
        InputIterator last);


    /// Assignment.
    inline Bbox& operator=( const Bbox& other)
    {
        min = other.min;
        max = other.max;
        return *this;
    }

    /// Assignment from corresponding POD type.
    inline Bbox& operator=( const Bbox_struct<T,DIM>& other)
    {
        min = other.min;
        max = other.max;
        return *this;
    }

    /// Conversion to corresponding POD type.
    inline operator Bbox_struct<T,DIM>() const
    {
        Bbox_struct<T,DIM> result;
        result.min = min;
        result.max = max;
        return result;
    }

    /// Returns the pointer to the first vector, \c min.
    inline Vector * begin()
    {
        return & (min);
    }
    /// Returns the pointer to the first vector, \c min.
    inline const Vector * begin() const
    {
        return & (min);
    }

    /// Returns the past-the-end pointer, such that \c [begin(),end()] forms
    /// the range \c [min,max].
    inline Vector * end()
    {
        return begin() + SIZE;
    }
    /// Returns the past-the-end pointer, such that \c [begin(),end()] forms
    /// the range \c [min,max].
    inline const Vector * end() const
    {
        return begin() + SIZE;
    }

    /// Returns the vector \c min for \c i==0, and the vector \c max for \c i==1.
    inline Vector        &operator[](
        Size i) ///< index in [0,1].
    {
        mi_math_assert_msg(i < SIZE, "precondition");
        return begin()[i];
    }

    /// Returns the vector \c min for \c i==0, and the vector \c max for \c i==1.
    inline const Vector  &operator[](
        Size i) const  ///< index in [0,1].
    {
        mi_math_assert_msg(i < SIZE, "precondition");
        return begin()[i];
    }

    /// Returns true if the box is empty, for example, after the default
    /// constructor or the \c clear() method call.
    inline bool empty() const
    {
        for (Size i = 0; i < DIM; i++) {
            if (min[i] !=  base::numeric_traits<T>::max MI_PREVENT_MACRO_EXPAND())
                return false;
            if (max[i] !=  base::numeric_traits<T>::negative_max())
                return false;
        }
        return true;
    }

    /// Returns the rank of the bbox; 0 if it is a point or empty,
    /// 1 if it is a line, and so on.
    inline Size rank() const
    {
        Size rank = 0;
        for (Size i = 0; i < DIM; i++)
            rank += (min[i] < max[i]);
        return rank;
    }

    /// Returns true if \c rank() is 0, i.e., the bbox is a single point.
    inline bool is_point() const { return min == max; }

    /// Returns true if \c rank() is 1, i.e., the bbox is an axis-aligned line.
    inline bool is_line() const { return rank() == 1u; }

    /// Returns true if \c rank() is 2, i.e., the bbox is an axis-aligned plane.
    inline bool is_plane() const { return rank() == 2u; }

    /// Returns true if \c rank() is 3, i.e., the bbox has a volume.
    inline bool is_volume() const { return rank() == 3u; }

    /// Return true if the point is inside or on the boundary of the bbox.
    inline bool contains(
        const Vector& vec) const       ///< test this point
    {
        for (Size i = 0; i < DIM; i++) {
            if (vec[i] < min[i] || vec[i] > max[i])
                return false;
        }
        return true;
    }

    /// Returns true if this bbox and the \c other bbox intersect in their
    /// interiors or on their boundaries.
    inline bool intersects(
        const Bbox& other) const        ///< test this bbox
    {
        for (Size i = 0; i < DIM; i++) {
            if (min[i] > (other.max)[i] || max[i] < (other.min)[i])
                return false;
        }
        return true;
    }

    /// Assigns the union of this bbox and the \c other bbox to
    /// this bbox.
    inline void insert(
        const Bbox& other)              ///< bbox to add to this
    {
        min = elementwise_min( min, (other.min));
        max = elementwise_max( max, (other.max));
    }

    /// Assigns the union of this bbox and the \c point to
    /// this bbox.
    inline void insert(
        const Vector& point)            ///< point to add to this
    {
        min = elementwise_min( min, point);
        max = elementwise_max( max, point);
    }

    /// Inserts a range \c [first,last) of items into this bbox. The value type of
    /// \c InputIterator can be either \c Vector to insert points, or it can
    /// be \c Bbox to insert bboxes.
    ///
    /// \param first   first element of the sequence to insert
    /// \param last    past-the-end position of sequence to insert
    template <typename InputIterator>
    void insert(
        InputIterator first,
        InputIterator last);


    /// Returns the translation of this bbox by vectors that are inside
    /// the scaled bbox of vectors, i.e., \c t*vbox.
    /// Precondition: this bbox and \c vbox are not empty.
    ///
    /// \param vbox   vector bbox to add
    /// \param t      scale parameter. A negative scale inverts \c vbox.
    inline Bbox add_motionbox(
        const Bbox& vbox,
        T           t) const
    {
        mi_math_assert_msg( ! empty(),      "precondition");
        mi_math_assert_msg( ! vbox.empty(), "precondition");
        return t < 0 ? Bbox(min + (vbox.max) * t, max + (vbox.min) * t)
                     : Bbox(min + (vbox.min) * t, max + (vbox.max) * t);
    }

    /// Assigns the union of this bbox and the \c other bbox to
    /// this bbox. Makes the bounding box compatible with the
    /// \c std::back_inserter function, which allows you to use STL
    /// functions, such as \c std::copy to compute the union of a
    /// sequence of bounding boxes.
    inline void push_back(
        const Bbox& other)             ///< bbox to add to this
    {
        return insert( other);
    }

    /// Robustly grows the bounding box by a value computed automatically
    /// from the bounding box dimensions and location in space.
    ///
    /// If a bounding box is far away from the origin, just enlarging the bounding
    /// box by \p eps * (largest box extent) may result in cancellation. To avoid
    /// cancellation problems, this method computes the value for enlarging the box
    /// by computing coordinatewise the sum of the absolute values of the min and
    /// max coordinates and the bounding box extent. It takes then the maximum of
    /// all these sums, multiplies it by \p eps, adds it to \c bbox.max and subtracts
    /// it from \c bbox.min, enlarging the bounding box by an equal amount on all sides.
    ///
    void robust_grow(
        T eps = T(1.0e-5f));     ///< grow factor

    /// Returns the volume of the bbox.
    inline T volume() const
    {
        Vector diag = max - min;
        T vol = base::max MI_PREVENT_MACRO_EXPAND ( T(0), diag[0]);
        for (Size i = 1; i < DIM; i++)
            vol *= base::max MI_PREVENT_MACRO_EXPAND ( T(0), diag[i]);
        return vol;
    }

    /// Returns the length of the diagonal. Precondition: the bbox is not empty.
    inline T diagonal_length() const
    {
        mi_math_assert_msg( ! empty(), "precondition");
        Vector diag = max - min;
        return length( diag);
    }

    /// Returns the index of the dimension, in which the bounding box
    /// has its largest extent, i.e., 0=x, 1=y, 2=z.
    inline Size largest_extent_index() const
    {
        Vector diag = max - min;
        T maxval = diag[0];
        Size  maxidx = 0;
        for (Size i = 1; i < DIM; i++) {
            if (maxval < diag[i]) {
                maxval = diag[i];
                maxidx = i;
            }
        }
        return maxidx;
    }

    /// Returns the center point of the bbox.
    inline Vector center() const { return (max + min) * T(0.5);}

};

//------ Operator declarations for Bbox ---------------------------------------

// grow means to add a constant margin to all box faces;
// shrink means to shave away a constant margin from all box faces


/// Returns a bbox that is the \p bbox increased by a constant \p value at each face,
/// i.e., \p value is added to \c bbox.max and subtracted from \c bbox.min.
/// Precondition: \c bbox is not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM>  operator+ ( const Bbox<T,DIM>& bbox, T value)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    Bbox<T,DIM> result( Bbox<T,DIM>::UNINITIALIZED_TAG);
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (result.min)[i] = (bbox.min)[i] - value;
        (result.max)[i] = (bbox.max)[i] + value;
    }
    return result;
}

/// Returns a bbox that is the \c bbox shrunk by a constant \c value at each face,
/// i.e., \p value is subtracted from \c bbox.max and added to \c bbox.min.
/// Precondition: \c bbox is not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM>  operator- ( const Bbox<T,DIM>& bbox, T value)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    Bbox<T,DIM> result( Bbox<T,DIM>::UNINITIALIZED_TAG);
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (result.min)[i] = (bbox.min)[i] + value;
        (result.max)[i] = (bbox.max)[i] - value;
    }
    return result;
}

/// Returns a bbox that is a version of \p bbox scaled by \p factor,
/// i.e., \c bbox.max and \c bbox.min are multiplied by \p factor.
/// Precondition: \c bbox is not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM>  operator* ( const Bbox<T,DIM>& bbox, T factor)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    Bbox<T,DIM> result( Bbox<T,DIM>::UNINITIALIZED_TAG);
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (result.min)[i] = (bbox.min)[i] * factor;
        (result.max)[i] = (bbox.max)[i] * factor;
    }
    return result;
}

/// Returns a bbox that is a version of \p bbox divided by \p divisor,
/// i.e., \c bbox.max and \c bbox.min are divided by \p divisor.
/// Precondition: \c bbox is not empty and \p divisor is not null.
template <typename T, Size DIM>
inline Bbox<T,DIM>  operator/ ( const Bbox<T,DIM>& bbox, T divisor)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    mi_math_assert_msg( divisor != T(0), "precondition");
    Bbox<T,DIM> result( Bbox<T,DIM>::UNINITIALIZED_TAG);
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (result.min)[i] = (bbox.min)[i] / divisor;
        (result.max)[i] = (bbox.max)[i] / divisor;
    }
    return result;
}

/// Increases \p bbox by a constant \p value at each face,
/// i.e., \p value is added to \c bbox.max and subtracted from \c bbox.min.
/// Precondition: \c bbox is not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM>& operator+=( Bbox<T,DIM>& bbox, T value)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (bbox.min)[i] -= value;
        (bbox.max)[i] += value;
    }
    return bbox;
}

/// Shrink \c bbox by a constant \c value at each face,
/// i.e., \p value is subtracted from \c bbox.max and added to \c bbox.min.
/// Precondition: \c bbox is not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM>& operator-=( Bbox<T,DIM>& bbox, T value)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (bbox.min)[i] += value;
        (bbox.max)[i] -= value;
    }
    return bbox;
}

/// Scales \p bbox by \p factor,
/// i.e., \c bbox.max and \c bbox.min are multiplied by \p factor.
/// Precondition: \c bbox is not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM>& operator*=( Bbox<T,DIM>& bbox, T factor)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (bbox.min)[i] *= factor;
        (bbox.max)[i] *= factor;
    }
    return bbox;
}

/// Divide \p bbox by \p divisor,
/// i.e., \c bbox.max and \c bbox.min are divided by \p divisor.
/// Precondition: \c bbox is not empty and \p divisor is not null.
template <typename T, Size DIM>
inline Bbox<T,DIM>& operator/=( Bbox<T,DIM>& bbox, T divisor)
{
    mi_math_assert_msg( ! bbox.empty(), "precondition");
    mi_math_assert_msg( divisor != T(0), "precondition");
    for (Size i = 0; i < DIM; i++) { // single loop impl., less temporaries
        (bbox.min)[i] /= divisor;
        (bbox.max)[i] /= divisor;
    }
    return bbox;
}

/// Returns \c true if \c lhs is elementwise equal to \c rhs.
template <typename T, Size DIM>
inline bool  operator==(const Bbox<T,DIM>& lhs, const Bbox<T,DIM>& rhs)
{
    return (lhs.min) == (rhs.min) && (lhs.max) == (rhs.max);
}

/// Returns \c true if \c lhs is elementwise not equal to \c rhs.
template <typename T, Size DIM>
inline bool  operator!=(const Bbox<T,DIM>& lhs, const Bbox<T,DIM>& rhs)
{
    return (lhs.min) != (rhs.min) || (lhs.max) != (rhs.max);
}

/// Returns \c true if \c lhs is \ref LexOrder "lexicographically less than" \c rhs.
template <typename T, Size DIM>
inline bool operator< ( const Bbox<T,DIM> & lhs, const Bbox<T,DIM> & rhs)
{
    for (Size i = 0; i < DIM; i++) {
        if ( (lhs.min)[i] < (rhs.min)[i])
            return true;
        if ( (lhs.min)[i] > (rhs.min)[i])
            return false;
    }
    for (Size i = 0; i < DIM; i++) {
        if ( lhs.max[i] < rhs.max[i])
            return true;
        if ( lhs.max[i] > rhs.max[i])
            return false;
    }
    return false;
}

/// Returns \c true if \c lhs is \ref LexOrder "lexicographically less than or equal"
/// to \c rhs.
template <typename T, Size DIM>
inline bool operator<= ( const Bbox<T,DIM>& lhs, const Bbox<T,DIM>& rhs)
{
    return ! (rhs < lhs);
}

/// Returns \c true if \c lhs is \ref LexOrder "lexicographically greater than" \c rhs.
template <typename T, Size DIM>
inline bool operator> ( const Bbox<T,DIM> & lhs, const Bbox<T,DIM> & rhs)
{
    return rhs < lhs;
}

/// Returns \c true if \c lhs is \ref LexOrder "lexicographically greater than or equal"
/// to \c rhs.
template <typename T, Size DIM>
inline bool operator>= ( const Bbox<T,DIM>& lhs, const Bbox<T,DIM>& rhs)
{
    return ! (lhs < rhs);
}


//------ Free Functions for Bbox ----------------------------------------------


/// Returns the linear interpolation between \p bbox1 and \c bbox2,
/// i.e., it returns <tt>(1-t) * bbox1 + t * bbox2</tt>.
/// Precondition: \p bbox1 and \p bbox2 are not empty.
template <typename T, Size DIM>
inline Bbox<T,DIM> lerp(
    const Bbox<T,DIM> &bbox1,  ///< one bbox
    const Bbox<T,DIM> &bbox2,  ///< second bbox
    T          t)              ///< interpolation parameter in [0,1]
{
    mi_math_assert_msg( ! bbox1.empty(), "precondition");
    mi_math_assert_msg( ! bbox2.empty(), "precondition");
    T t2 = T(1) - t;
    return Bbox<T,DIM>( (bbox1.min)*t2 + (bbox2.min)*t, (bbox1.max)*t2 + (bbox2.max)*t);
}


/// Clip \c bbox1 at \c bbox2 and return the result. I.e., the resulting
/// bbox is the intersection of \c bbox1 with \c bbox2.
template <typename T, Size DIM>
inline Bbox<T,DIM> clip(
    const Bbox<T,DIM> &bbox1,   ///< first bbox
    const Bbox<T,DIM> &bbox2)   ///< second bbox
{
    Bbox<T,DIM> result(Bbox<T,DIM>::UNINITIALIZED_TAG);
    for (Size i = 0; i < DIM; i++)
    {
        result.min[i] = base::max MI_PREVENT_MACRO_EXPAND (bbox1.min[i], bbox2.min[i]);
        result.max[i] = base::min MI_PREVENT_MACRO_EXPAND (bbox1.max[i], bbox2.max[i]);

        if (result.max[i] < result.min[i]) // the bbox is empty
        {
            result.clear();
            return result;
        }
    }

    return result;
}


/// Returns the 3D bbox transformed by \c mat, where the bbox is interpreted
/// as a bbox of 3D points; the transformation including the translation part
/// is applied to the eight bbox corners and a new axis aligned bbox is computed
/// for these transformed corners.
///
/// \note
/// The transformed bbox is likely to be a more pessimistic
/// approximation of a geometry that was approximated by the original
/// bbox. Transforming the approximated geometry and computing a new
/// bounding box gives usually a tighter bounding box.
///
/// \param mat    4x4 transformation matrix
/// \param bbox   the bbox to transform
template <typename TT, typename T>
Bbox<T,3> transform_point(
    const Matrix<TT,4,4>& mat,
    const Bbox<T,3>&      bbox);


/// Returns the 3D bbox transformed by \c mat, where the bbox is interpreted
/// as a bbox of 3D vectors, such as motion vectors; only the linear part of the
/// transformation excluding the translation part is applied to the eight
/// bbox corners and a new axis aligned bbox is computed for these transformed
/// corners.
///
/// \param mat    4x4 transformation matrix
/// \param bbox   the bbox to transform
template <typename TT, typename T>
Bbox<T,3> transform_vector(
    const Matrix<TT,4,4>& mat,
    const Bbox<T,3>&      bbox);



//------ Definitions of non-inline function -----------------------------------


// Inserts a range \c [first,last) of items into this bbox.
//
template <typename T, Size DIM>
template <typename InputIterator>
void Bbox<T,DIM>::insert(
    InputIterator first, // first element of the sequence to insert.
    InputIterator last)  // past-the-end position of sequence to insert.
{
    for ( ; first != last; ++first)
        insert( *first);
}

// Constructs a bbox from a range \c [first,last) of items.
//
template <typename T, Size DIM>
template <typename InputIterator>
Bbox<T,DIM>::Bbox(
    InputIterator first, // first element of the sequence to insert.
    InputIterator last)  // past-the-end position of sequence to insert.
{
    clear();
    insert( first, last);
}


// Robustly grows the bounding box by a value computed automatically
// from the bounding box dimensions and location in space.
//
// If a bounding box is far away from the origin, just enlarging the bounding
// box by \p eps * (largest box extent) may result in cancellation. To avoid
// cancellation problems, this method computes the value for enlarging the box
// by computing coordinatewise the sum of the absolute values of the min and
// max coordinates and the bounding box extent. It takes then the maximum of
// all these sums, multiplies it by \p eps, adds it to \c bbox.max and subtracts
// it from \c bbox.min, enlarging the bounding box by an equal amount on all sides.
//
template <typename T, Size DIM>
void Bbox<T, DIM>::robust_grow(
    T    eps /*= 1.0e-5f*/)              // grow factor
{
    // Just enlarging the bbox by epsilon * (largest box extent)
    // is not sufficient, since there may be cancelation errors if the box is
    // far away from the origin. Hence we take into account the distance of
    // the box from the origin: the further the box is away, the larger we have to
    // make it. We just add the two contributions. If we are very far away, then
    // distance will dominate. For very large boxes, the extent will dominate.
    // We neglect exact weight factors. We are just a bit less generous with
    // the epsilon to compensate for the extra stuff we added. If we have objects
    // that in some direction are several orders of magnitude larger than in the
    // others, this method will not be perfect.
    //
    // compute size heuristic for each dimension
    Vector dist;
    for (Size i = 0; i < DIM; i++)
        dist[i] = base::abs(min[i]) + base::abs(max[i])
                + base::abs(max[i] - min[i]);
    // compute the grow factor
    T max_dist = T(0);
    for (Size i = 0; i < DIM; i++)
        max_dist = base::max( max_dist, dist[i] );
    const T margin = max_dist * eps;
    // grow the bounding box
    *this += margin;
}


//
// Returns the 3D bbox transformed by \c mat, where the bbox is interpreted
// as a bbox of 3D points.
//
template <typename TT, typename T>
Bbox<T,3> transform_point(
    const Matrix<TT,4,4>&  mat,  // transform with this matrix
    const Bbox<T,3>&       bbox) // bbox to transform
{
    if ( bbox.empty())
        return bbox;
    //
    // Transforms all eight corner points, and finds then the bounding box of
    // these eight points. The corners are computed in an optimized manner
    // which factorizes computations.
    //
    // The transformation is decomposed into the transformation of (min,1)
    // and the transformation of bbox difference vectors (max.x-min.x,0,0,0),(0,
    // max.y-min.y,0,0),(0,0,max.z-min.z,0). The transformation of max is e.g. the
    // sum of all 4 transformed vectors. The division by the homogeneous w is
    // deferred to the end.
    //
    Vector<T,3> corners[8];             // bbox corners
    corners[0] = transform_vector( mat, bbox.min);      // vertex 000
    corners[0].x += T(mat.wx); // translation on vertex 000
    corners[0].y += T(mat.wy);
    corners[0].z += T(mat.wz);

    // difference vectors between min and max
    Vector<T,3> dx = transform_vector(mat, Vector<T,3>((bbox.max).x - (bbox.min).x,0,0));
    Vector<T,3> dy = transform_vector(mat, Vector<T,3>(0,(bbox.max).y - (bbox.min).y,0));
    Vector<T,3> dz = transform_vector(mat, Vector<T,3>(0,0,(bbox.max).z - (bbox.min).z));

    corners[1] = corners[0] + dz;                       // vertex 001
    corners[2] = corners[0] + dy;                       // vertex 010
    corners[3] = corners[0] + dy + dz;                  // vertex 011
    corners[4] = corners[0] + dx;                       // vertex 100
    corners[5] = corners[0] + dx + dz;                  // vertex 101
    corners[6] = corners[0] + dx + dy;                  // vertex 110
    corners[7] = corners[0] + dx + dy + dz;             // vertex 110
    //
    // compute the w-coordinates separately. This is done to avoid copying from
    // 4D to 3D vectors. Again, the computation is decomposed.
    //
    // w-coordinate for difference vectors between min and max
    T  wx = T(mat.xw * ((bbox.max).x - (bbox.min).x));
    T  wy = T(mat.yw * ((bbox.max).y - (bbox.min).y));
    T  wz = T(mat.zw * ((bbox.max).z - (bbox.min).z));
    // w-coordinate for corners
    T  w[8];
    w[0] = T(mat.xw * (bbox.min).x + mat.yw * (bbox.min).y
           + mat.zw * (bbox.min).z + mat.ww);
    w[1] = w[0] + wz;                                   // vertex 001
    w[2] = w[0] + wy;                                   // vertex 010
    w[3] = w[0] + wy + wz;                              // vertex 011
    w[4] = w[0] + wx;                                   // vertex 100
    w[5] = w[0] + wx + wz;                              // vertex 101
    w[6] = w[0] + wx + wy;                              // vertex 110
    w[7] = w[0] + wx + wy + wz;                         // vertex 111

    // divide the other coordinates (x,y,z) by w to obtain 3D coordinates
    for (unsigned int i=0; i<8; ++i) {
        if (w[i]!=0 && w[i]!=1) {
            T inv = T(1)/w[i];
            corners[i].x *= inv;
            corners[i].y *= inv;
            corners[i].z *= inv;
        }
    }
    Bbox<T,3> result( corners, corners+8);
    return result;
}


// Returns the 3D bbox transformed by \c mat, where the bbox is interpreted
// as a bbox of 3D vectors, such as motion vectors. Only the linear part of the
// transformation excluding the translation part is applied to the eight
// bbox corners and a new axis aligned bbox is computed for these transformed
// corners.
//
template <typename TT, typename T>
Bbox<T,3> transform_vector(
    const Matrix<TT,4,4>& mat,  // transform with this matrix
    const Bbox<T,3>&      bbox) // bbox to transform
{
    if ( bbox.empty())
        return bbox;
    // See transform_point above for implementation notes.
    Vector<T,3> corners[8];             // bbox corners
    corners[0] = transform_vector( mat, (bbox.min));         // vertex 000

    // difference vectors between min and max
    Vector<T,3> dx = transform_vector(mat, Vector<T,3>((bbox.max).x - (bbox.min).x,0,0));
    Vector<T,3> dy = transform_vector(mat, Vector<T,3>(0,(bbox.max).y - (bbox.min).y,0));
    Vector<T,3> dz = transform_vector(mat, Vector<T,3>(0,0,(bbox.max).z - (bbox.min).z));

    corners[1] = corners[0] + dz;                       // vertex 001
    corners[2] = corners[0] + dy;                       // vertex 010
    corners[3] = corners[0] + dy + dz;                  // vertex 011
    corners[4] = corners[0] + dx;                       // vertex 100
    corners[5] = corners[0] + dx + dz;                  // vertex 101
    corners[6] = corners[0] + dx + dy;                  // vertex 110
    corners[7] = corners[0] + dx + dy + dz;             // vertex 110
    Bbox<T,3> result( corners, corners+8);
    return result;
}

/*@}*/ // end group mi_math_bbox

}} // namespace mi::math

#endif // MI_MATH_BBOX_H

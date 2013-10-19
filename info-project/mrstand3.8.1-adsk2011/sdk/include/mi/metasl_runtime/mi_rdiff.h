/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_RDIFF_H
#define MI_RDIFF_H 1

#include "mi_types.h"
#include "math.h"

namespace MI {
namespace RDIFF {

using MATH::Vector3;

struct Ray_struct
{
    Vector3 org, dir; // origin and direction vectors
};

struct Ray_base : public Ray_struct
{
    Ray_base() // leave uninitialized
    { }

    Ray_base(
        const Vector3 &org, // origin
        const Vector3 &dir) // direction
    {
        this->org = org;
        this->dir = dir;
    }

    bool operator==(const Ray_base& rhs) const // equal
    {
        return (org == rhs.org) && (dir == rhs.dir);
    }

    bool operator!=(const Ray_base& rhs) const // not equal
    {
        return !operator==(rhs);
    }
};

struct Ray_diff_struct
{
    Ray_struct r, drdx, drdy;
};

struct Ray_diff_base : public Ray_diff_struct
{
    Ray_diff_base(
        const Ray_struct& r,    // ray
        const Ray_struct& drdx, // derivative wrt x
        const Ray_struct& drdy) // derivative wrt y
    {
        this->r = r;
        this->drdx = drdx;
        this->drdy = drdy;
    }

    Ray_diff_base(
        const Ray_base& r,    // ray
        const Ray_base& drdx, // derivative wrt x
        const Ray_base& drdy) // derivative wrt y
    {
        this->r = r;
        this->drdx = drdx;
        this->drdy = drdy;
    }
};

}} // namespace RDIFF, MI

#endif  // MI_RDIFF_H

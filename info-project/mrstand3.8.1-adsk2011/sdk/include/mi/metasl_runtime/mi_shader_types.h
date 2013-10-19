/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_SHADER_TYPES_H
#define MI_SHADER_TYPES_H

#include "mi_types.h"

namespace MI {
namespace SHADER {

// A Tag is the unique key for database elements. It is used to search the Info
// elements in the database cache. The value 0 is reserved and refers to
// "no tag".
typedef Uint32 Tag;


/// String ID
///
/// String literals are automatically mapped to IDs to avoid costly string
/// operations at shader runtime.
typedef Uint64 String_id;

typedef Uint32 Ray_type;
typedef Uint32 Ray_flags;


}}

#endif //MI_SHADER_TYPES_H

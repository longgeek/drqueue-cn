/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 *****************************************************************************/

#ifndef MI_COMPILER_UTILS_H
#define MI_COMPILER_UTILS_H

#include <cstring>
#include "mi_shader_state.h"

namespace MI {
namespace SHADER {


// map scene_data's first argument to the data ID
inline State::Data_source scene_data_to_source_id(const char* data)
{
    if (!strcmp(data,"mi_instance"))
        return State::INSTANCE_DATA;
    else if (!strcmp(data,"mi_object"))
        return State::OBJECT_DATA;
    else if (!strcmp(data,"mi_primitive"))
        return State::PRIMITIVE_DATA;
    else if (!strcmp(data,"mi_options"))
        return State::OPTIONS_DATA;
    else
        return State::DATA_ALIGN;
}


// stringify State::Data_source
inline const char* stringify_datasrc(State::Data_source src)
{
#define DSCASE(id) case State::id: return "State::" #id;
    switch (src) {
        DSCASE(INSTANCE_DATA);
        DSCASE(OBJECT_DATA);
        DSCASE(PRIMITIVE_DATA);
        DSCASE(OPTIONS_DATA);
        default: return 0;
    }
#undef DSCASE
}


// convenience
inline const char* scene_data_to_source_id_str(const char* data)
{
    return stringify_datasrc(scene_data_to_source_id(data));
}


// map scene_data's third argument to the data type ID
inline State::Data_type scene_data_to_type_id(const char* data)
{
    if (!strcmp(data,"data"))
        return State::SCENE_DATA;
    else if (!strcmp(data,"bbox min"))
        return State::SCENE_ATTR_BBOX_MIN;
    else if (!strcmp(data,"bbox max"))
        return State::SCENE_ATTR_BBOX_MAX;
    else
        return State::SCENE_ALIGN;
}


// stringify State::Data_type
inline const char* stringify_datatp(State::Data_type tp)
{
#define DTCASE(id) case State::id: return "State::" #id;
    switch (tp) {
        DTCASE(SCENE_DATA);
        DTCASE(SCENE_ATTR_BBOX_MIN);
        DTCASE(SCENE_ATTR_BBOX_MAX);
        default: return 0;
    }
}


// convenience
inline const char* scene_data_to_type_id_str(const char* data)
{
    return stringify_datatp(scene_data_to_type_id(data));
}


// map MetaSL coordinate system names to IDs
inline State::Coordsystem get_coordsystem(const char* name)
{
    if (0==strcmp(name,"world") ||
        0==strcmp(name,"internal"))
        return State::COORD_WORLD;
    else if (0==strcmp(name,"object"))
        return State::COORD_OBJECT;
    else if (0==strcmp(name,"camera"))
        return State::COORD_CAMERA;
    else if (0==strcmp(name,"raster"))
        return State::COORD_RASTER;
    else if (0==strcmp(name,"light"))
        return State::COORD_LIGHT;
    return State::COORD_UNDEFINED;
}


// stringify Coordsystem IDs
inline const char* stringify_coordsys(State::Coordsystem csys)
{
#define CSCASE(id) case State::id: return "State::" #id;
    switch (csys) {
        CSCASE(COORD_WORLD);
        CSCASE(COORD_OBJECT);
        CSCASE(COORD_CAMERA);
        CSCASE(COORD_RASTER);
        CSCASE(COORD_LIGHT);
        CSCASE(COORD_UNDEFINED);
        default: return 0;
    }
#undef CSCASE
}


// convenience
inline const char* get_coordsystem_str(const char* name)
{
    return stringify_coordsys(get_coordsystem(name));
}


}}

#endif //MI_COMPILER_UTILS_H

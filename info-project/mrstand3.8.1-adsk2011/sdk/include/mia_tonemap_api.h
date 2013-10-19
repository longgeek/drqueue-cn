/******************************************************************************
* Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
* Germany. All rights reserved.
******************************************************************************
* Created:  05.07.20
* Module:   architectural
* Purpose:  tonemapping api
*
* Exports:
*
*      mia_tonemap_api*()
*
* History:
*   07.03.12: Created
*   08.05.28: Zap: Added "reverse" tonemapping callable function.
*
* Description:
*****************************************************************************/

#define miA_TONEMAP_API_VERSION  1
#define miA_TONEMAP_PHOTOGRAPHIC 0x1

typedef struct {
    /* Actual parameters of the tone mapper */
    miScalar cm2_scale;
    miColor  whitepoint;
    miScalar film_iso;
    miScalar camera_shutter;
    miScalar f_number;
    miScalar vignetting;

    miScalar burn;
    miScalar crunch;
    miScalar saturation;
    miScalar gamma;

    /* Copied from the rendering camera */
    miScalar camera_aspect, camera_focal, camera_aperture;
    /* Luminance weights, copy from state->options */
    miColor  lumw;
} mia_tonemap_api_photographic;

typedef struct {
    int api_version; /* miA_TONEMAP_API_VERSION */
    int tonemap_id;  /* ID of tonemapper to call, currently only miA_TONEMAP_PHOTOGRAPHIC */

    /* Handle to tonemappers private data. Allocated by _init and destroyed by _exit */
    void *handle;

    /* For image transformation */
    int   x_resolution, y_resolution;

    void *image_in;
    void *image_out;
    void *abort_info;

    int (*read_function) (void *, miColor *, int, int);
    int (*write_function)(void *, miColor *, int, int); 
    int (*abort_function)(void *, int, int);

    /* Parameters */
    union {
        mia_tonemap_api_photographic photo;
    } tm;
} mia_tonemap_api;

/* Functions */

#ifdef __cplusplus
#define MIEXTERNC extern "C"
#else
#define MIEXTERNC
#endif

MIEXTERNC DLLEXPORT void      mia_tonemap_api_init(mia_tonemap_api *tms);
MIEXTERNC DLLEXPORT void      mia_tonemap_api_transform_color(mia_tonemap_api *tms, miColor *color, miScalar x, miScalar y);
MIEXTERNC DLLEXPORT void      mia_tonemap_api_untransform_color(mia_tonemap_api *tms, miColor *color, miScalar x, miScalar y);
MIEXTERNC DLLEXPORT miBoolean mia_tonemap_api_transform_image(mia_tonemap_api *tms);
MIEXTERNC DLLEXPORT void      mia_tonemap_api_exit(mia_tonemap_api *tms);


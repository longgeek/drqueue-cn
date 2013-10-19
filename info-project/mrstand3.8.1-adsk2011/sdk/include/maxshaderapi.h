/******************************************************************************
 * Copyright 1986-2007 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 ******************************************************************************
 ******************************************************************************
 * Copyright (c) 2003, Autodesk, Inc.
 * All rights reserved.
 ******************************************************************************
 * Author:		Daniel Levesque
 * Created:		29 September 2003
 * Module:		MAX to mi translator
 * Purpose:		Definitions of an API to expose 3ds max shader functionality to
 *				3rd party developers.
 *
 * Exports:
 *
 * History:
 *
 *
 * Description:
 *
 *      Definitions of an API to expose 3ds max shader functionality to
 *		3rd party developers.
 *
 ******************************************************************************
 */
#ifndef _MAXSHADERAPI_H_
#define _MAXSHADERAPI_H_

#include <shader.h>
#include <geoshader.h>
#include <float.h>

#ifdef WIN_NT
#define ADSKSHADERS_DLLEXPORT extern "C" __declspec(dllexport)
#define ADSKSHADERS_DLLIMPORT extern "C" __declspec(dllimport)
#elif defined( __GNUC__ )
#define ADSKSHADERS_DLLEXPORT extern "C"  __attribute__((visibility("default")))
#define ADSKSHADERS_DLLIMPORT extern "C"
#else
#define ADSKSHADERS_DLLEXPORT
#define ADSKSHADERS_DLLIMPORT
#endif

#define MAXSHADERS_DLLEXPORT ADSKSHADERS_DLLEXPORT

#ifdef THIS_IS_MAX_SHADER_DLL
// Compiling the max shader dll: export the functions
#define MAXSHADERS_API ADSKSHADERS_DLLEXPORT
#else
// Compiling another dll: import the functions
#define MAXSHADERS_API ADSKSHADERS_DLLIMPORT
#endif

#if defined(DEBUG) || defined(_DEBUG)
#include <assert.h>
/* need to define this here, since DEC casts EX to int in assert() */
#define miASSERT(EX)    ((EX)?((void)0):assert(EX))
#else
#define miASSERT(EX)    ((void)0)
#endif

#ifdef _MSC_VER
#define isnan _isnan
#endif

typedef struct {
		miBoolean		isMtlEdit;
		miColor			ambientLight;
		miColor			globalLightLevel;
		miBoolean		forceDoubleSided;
		miScalar		gammaCorrection;
		miScalar		nearRange;
		miScalar		farRange;
		miScalar		physicalScale;	/* Physical scale to convert between physical units (candelas) and the 0-1 color world */
		miScalar		pixelAspectRatio;	/* Pixel aspect ratio. This isn't available in mental ray, so we have to pass it using this structure */
		miTag			toneOpShader;
		miColor			backgroundColor;
		miBoolean		doingBakeToTexture;
		miBoolean		toneOpInactive;	
		miScalar		internalToMeterScale;	// Scales internal units to meters.
		miBoolean		isProtein;		// Rendering in the context of Protein?
		miBoolean		isYUp;			//is the scene Y-Up?
		miScalar	        BlurredReflectionMultiplier;
		miScalar	        BlurredRefractionMultiplier;
		miInteger       AreaShadowSamples;
} mrSceneData;

/* Data block attached to each object. This is "max_ObjectData" in 3dsmax.mi. */
typedef struct {
		miVector		bvmin;			// PROTEIN: Not used
		miVector		bvmax;			// PROTEIN: Not used
		// Map channel index re-mapping
		// 3DSMAX: the array remaps a map channel ID to an index: mapchan[3dsmaxUVChanID]==correspondingMRUVIndex
		// PROTEIN: mapchan[mrUVIndex]==ProteinUVChanID
		int             i_mapchan;
		int             n_mapchan;
		int				mapchan[1];
        miTag           particleData;	// PROTEIN: Not used
} mrObjectData;

/* Particle data block attached to each particle object. This is "max_ParticleData" in 3dsmax.mi */
/* Each array in this structure should have a number of elements that is equal to "numParticles" */
/* or 0, if the translator judged that the data channel was not required. */
typedef struct mrParticleData {
    int numParticles;

    int i_particleAge;
    int n_particleAge;
    int particleAge[1];

    int i_particleLife;
    int n_particleLife;
    int particleLife[1];

    int i_particleSize;
    int n_particleSize;
    miScalar particleSize[1];

    int i_particlePosition;
    int n_particlePosition;
    miVector particlePosition[1];

    int i_particleVelocity;
    int n_particleVelocity;
    miVector particleVelocity[1];

    int i_particleCenter;
    int n_particleCenter;
    int particleCenter[1];
} mrParticleData;

typedef struct {
		miColor			wireColor;
		int				nodeID;
		int				nodeRenderID;
		int             i_light;        /* index of first light						*/
		int             n_light;        /* number of lights							*/
		miTag           light[1];		/* list of lights							*/
		int             i_shadow;       /* index of first shadow maker				*/
		int             n_shadow;       /* number of shadow makers					*/
		miTag           shadow[1];		/* list of shadow makers					*/
		miBoolean		useGlobalLights;	/* Use the global lights list? */
		int				i_mtlRequirements;
		int				n_mtlRequirements;
		int				mtlRequirements[1];
		miInteger		lightIncludeExcludeID;
} mrNodeData;

/* Returns the scene data. */
MAXSHADERS_API 
mrSceneData* GetSceneData(miState* state);

/* Returns the object data of the intersected object. */
MAXSHADERS_API 
mrObjectData* GetObjectData(miState* state);

MAXSHADERS_API
mrObjectData* GetObjectDataFromInstance(miTag instanceTag);

/* Returns the node data of the intersected instance. */
MAXSHADERS_API 
mrNodeData* GetNodeData(miTag instanceTag);

/* Returns the particle data retrieved from the given object data. */
/* Note that only particle objects have particle data. Also, particle objects */
/* will not have paticle data, unless a particle map was attached to the material of the object. */
MAXSHADERS_API 
mrParticleData* GetParticleData(miState* state, mrObjectData* objectData);	/* Object data needs to be NON-NULL! */

/* Returns the material ID for a specific primitive of a specific box */
int GetMaterialIDFromBox(miBox* box, int pri_idx);

/* Returns the material ID of the intersected primitive. More optimal version of GetMaterialID() */
/* if the caller already has a pointer to the object data. */
/* Note that if the object data is NULL, the face label will be considered as the material ID */
MAXSHADERS_API 
int GetMaterialID(miState* state);	/* Object data needs to be NON-NULL! */

/* Returns the patricle ID of the intersected primitive. */
MAXSHADERS_API 
miUint GetParticleID(register miState* state);

/* Returns the smoothing group of the intersected primitive. */
MAXSHADERS_API 
int GetFaceSmoothingGroup(miState* state);	/* Object data needs to be NON-NULL! */

/* Returns the edge visibility flag of the intersected primitive. */
/* An array of 3 booleans indicates whether each of the three edges should be visible. */
/* Note that this data is virtually useless if displacement was applied to the object. */
/* If the object data is NULL, then all edges are considered visible. */
MAXSHADERS_API 
void GetEdgeVisibility(register miState* state, miBoolean edgeVis[3]);	/* Object data needs to be NON-NULL! */

/* Applies the tone operator on a color. */
/* Returns miFALSE if there is no tone operator. */
MAXSHADERS_API
miBoolean ToneOpScaledToRGB(miState* state, miColor* result, miBoolean applyOnlyIfProcessBackgroundEnabled = miFALSE);

/* Applies the inverse tone operator on a color. You should call this when your shader returns a color */
/* that shouldn't be affected by the tone operator. */
MAXSHADERS_API
/* Returns miFALSE if there is no tone operator. */
miBoolean ApplyInverseToneOperator(miState* state, miColor* result);

/* Calculates the tangent basis vectors for the current point. Note that the tangent basis */
/* vectors are not always available - they are calculated & translated by the translator */
/* only in specific cases, when they are needed. */
MAXSHADERS_API
void GetTangentBasisVectors(miState* state, miVector t[2]);

/* Returns whether state->instance should be considered a shadow maker of state->light_instance, */
/* based on the contents of the list of shadow makers in mrNodeData. */
/* You need to pass a non-NULL pointer to the mrNodeData associated with state->instance, for */
/* efficiency reasons (to avoid retrieving that pointer multiple times. */
MAXSHADERS_API
miBoolean IsInstanceShadowMakerForLight(miState* state, const mrNodeData* nodeData);

// Remaps a UV channel _ID_, from the host application, to a map channel _index_ in mental ray.
// Returns -1 if the ID could not be matched. This is the ONLY way to correctly interpret
// the "mapChannel" member of mrObjectData, as it behaves differently based on the host
// application.
// The object data may be passed as an optimization (or if the object to be evaluated differs
// from the one in the state) , but will be retrieved from the state if NULL is passed.
MAXSHADERS_API
int GetUVChannelIndexFromID(miState* state, mrObjectData* objectData, int uvChannelID);

struct MaterialToShader_INST;

MAXSHADERS_API
miBoolean CallMaterial(miColor* result, register miState* state, miTag mtlTag, MaterialToShader_INST* inst = 0);

inline void CheckForNaN(miState* state, miColor& color)
{
	if (!(!isnan(color.r) && !isnan(color.g) && !isnan(color.b) && (miRAY_PHOTON(state->type) || !isnan(color.a))))
	{
		mi_error("A ray encountered an invalid color (NaN), using black instead.");
		color.r = 0.f; 
		color.g = 0.f;
		color.b = 0.f;
		color.a = 1.0f;
	}
}

inline void CheckForNaN(miState* state,  miVector& vector)
{
	miASSERT(!isnan(vector.x) && !isnan(vector.y) && !isnan(vector.z));
}

bool GetSafeParticleID(register miState* state, miUint &id);

#endif

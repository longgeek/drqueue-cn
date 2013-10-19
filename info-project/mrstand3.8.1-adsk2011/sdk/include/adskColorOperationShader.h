/*!
  \file
  \brief Base class for shaders that operate on result colors
*/
#ifndef ADSK_COLOROPERATION_SHADER_H
#define ADSK_COLOROPERATION_SHADER_H

#if defined __cplusplus

#ifndef ADSK_SHADER_H
#include <adskShader.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

enum ColorOperationMode
{
    ColorOpPassThrough         = 0,
    ColorOpApply               = 1,
    ColorOpNoContribution      = 2,
    ColorOpResultToBeauty      = 3
};

#define COLOR_OPERATION_SHADER_BASE_PARAMETERS \
    ADSK_BASE_SHADER_PARAMETERS                \
    miInteger renderPassMode;

namespace
{
/*!
  \brief Data structure used for storing the baseline parameters for
  color operation shaders.
*/
struct ColorOperationShaderBaseParameters {
    COLOR_OPERATION_SHADER_BASE_PARAMETERS
};

/*!
  \brief Data structure used to store intemediate frame buffer compositing results
*/
struct ColorOperationFbResult {
    miColor color;
    miColor opacity;
    miColor compositeColor;
    miColor compositeOpacity;
};

} // unnamed namespace

/*!
  \brief Color operation shader base class

  \tparam ColorOperationShaderParameters The type of the pass shader parameters. The structure is expected
    to contain COLOR_OPERATION_SHADER_BASE_PARAMETERS

  \tparam ColorOperationResultType the shader result structure.

  \tparam ColorOperationComputation The helper class. The type specified here must
    implement the following methods:
    <ul>
    <li> void initialize(ColorOperationShaderResult* pResult, miState* state, ColorOperationShaderParameters* pParameters,
      unsigned int numberOfFrameBuffers, PassTypeInfo* passTypeInfo, FrameBufferInfo* frameBufferInfo)
      performs initialization tasks that are required once per shader call. </li>
    <li> unsigned int branchCount() returns the number of color inputs that are operated, and that
      may produce frame buffer contribution when evaluated. </li>
    <li> miColor evaluateBranchColor(miState* state, ColorOperationShaderParameters* pParameters, int branch) 
      evaluates the color input indicated by branch and returns the result of the evaluation. Note:
      for shaders that are known to have only one branch, initialization may be performed in this function.</li>
    <li> void computeAndCompositeResult(ColorOperationFbResult& compResult, int branch) composits the branch
      result in compResult color/opacity into compResult compositeColor/compositeOpacity . </li>
    </ul>

  \tparam VERSION The version number of this shader.
*/
template<typename ColorOperationShaderParameters,
         typename ColorOperationResultType,
         typename ColorOperationComputation,
         int VERSION = 1>
class ColorOperationShader : public Material<ColorOperationShaderParameters, ShaderHelper<ColorOperationShaderParameters>, VERSION>
{
public:
    typedef Material<ColorOperationShaderParameters, ShaderHelper<ColorOperationShaderParameters>, VERSION> ParentClass;

  /*!
    \brief ColorOperationShader constructor. This will be called
    once per shader instance, and is where data for each shader
    instance should be initialized.

    \param pState A pointer to the mental ray state structure.

    \param pParameters A pointer to the shader parameters.
  */
  ColorOperationShader(miState *pState, ColorOperationShaderParameters *pParameters);

  /*!
    \brief ColorOperationShader destructor. The member variables \c
    mDestructorState and \c mDestructorParameters will be set
    correctly when the destructor is called.
  */
  virtual ~ColorOperationShader() {}

  /*!
    \brief Main shading function.
           
    This is the function which is called for shader samples.

    \param pResult A pointer to the mental ray color result.

    \param pState A pointer to the mental ray state
    structure.

    \param pParameters A pointer to the shader parameters.
  */
  miBoolean operator()(miColor *pResult, miState *pState, ColorOperationShaderParameters *pParameters);
};

template<typename ColorOperationShaderParameters,
         typename ColorOperationResultType,
         typename ColorOperationComputation,
         int VERSION>
         ColorOperationShader<ColorOperationShaderParameters,
         ColorOperationResultType,
         ColorOperationComputation,
         VERSION>::ColorOperationShader(miState *pState, 
                                        ColorOperationShaderParameters *pParameters) :
  Material<ColorOperationShaderParameters, ShaderHelper<ColorOperationShaderParameters>, VERSION>(pState, pParameters)
{
}

template<typename ColorOperationShaderParameters,
         typename ColorOperationResultType,
         typename ColorOperationComputation,
         int VERSION>
    miBoolean ColorOperationShader<ColorOperationShaderParameters,
    ColorOperationResultType,
    ColorOperationComputation,
    VERSION>::operator()(miColor* pResult,
                         miState* state,
                         ColorOperationShaderParameters* pParameters)
{
    ColorOperationComputation lColorOperationComputation(state,pParameters);
    ColorOperationResultType* const shaderResult = (ColorOperationResultType*)pResult;
    // Fetch frame buffer information
    PassTypeInfo* passTypeInfo;
    FrameBufferInfo* frameBufferInfo;
    unsigned int numberOfFrameBuffers = 0;
    FrameBufferState* fbState = getFrameBufferState(state);
    if (state->type != miRAY_SHADOW && fbState)
        numberOfFrameBuffers = getFrameBufferInfo(state, passTypeInfo, frameBufferInfo);

    if (!lColorOperationComputation.initialize(shaderResult, state, pParameters, numberOfFrameBuffers, passTypeInfo, frameBufferInfo))
    {
        return miTRUE;
    }

    const unsigned int branchCount = lColorOperationComputation.branchCount();
    *pResult = BLACK;

    miInteger mode = *mi_eval_integer(&pParameters->renderPassMode);
    miInteger traceLevel = state->reflection_level + state->refraction_level;

    ColorOperationFbResult masterResult;
    masterResult.color = BLACK;
    masterResult.opacity = BLACK;
    masterResult.compositeColor = BLACK;
    masterResult.compositeOpacity = BLACK;

    if (numberOfFrameBuffers > 0 && mode == ColorOpApply)
    {
        ColorOperationFbResult* fbResult = (ColorOperationFbResult*)alloca(sizeof(ColorOperationFbResult)*numberOfFrameBuffers);
        //Initialize accumulators
        for (unsigned int fb = 0; fb < numberOfFrameBuffers; fb++)
        {
            fbResult[fb].compositeColor = BLACK;
            fbResult[fb].compositeOpacity = BLACK;
            frameBufferInfo[fb].stack[traceLevel].currentValue = BLACK;
            frameBufferInfo[fb].stack[traceLevel].opacity = BLACK;
        }

        //Cycle through color inputs
        for (unsigned int branch = 0; branch < branchCount; branch++)
        {
            //Fetch the color value for the current branch
            bool keepGoing = lColorOperationComputation.evaluateBranchColor(state, pParameters, branch, masterResult);
            keepGoing &= lColorOperationComputation.computeAndCompositeResult(masterResult, branch);
            for (unsigned int fb = 0; fb < numberOfFrameBuffers; fb++)
            {
                fbResult[fb].color = frameBufferInfo[fb].stack[traceLevel].currentValue;
                fbResult[fb].opacity = masterResult.opacity;
                lColorOperationComputation.computeAndCompositeResult(
                    fbResult[fb], 
                    branch);
                frameBufferInfo[fb].stack[traceLevel].currentValue = BLACK;
                frameBufferInfo[fb].stack[traceLevel].opacity = BLACK;
            }
            masterResult.color = BLACK;
            masterResult.opacity = BLACK;

            if (!keepGoing)
            {
                break;
            }
        }

        lColorOperationComputation.finalize(shaderResult, state, pParameters, masterResult);

        //Save composite result
        for (unsigned int fb = 0; fb < numberOfFrameBuffers; fb++)
        {
            frameBufferInfo[fb].stack[traceLevel].currentValue = fbResult[fb].compositeColor;
            frameBufferInfo[fb].stack[traceLevel].opacity = fbResult[fb].compositeOpacity;
        }

    }
    else
    {
        // The simple no render pass case
        for (unsigned int branch = 0; branch < branchCount; branch++)
        {
            bool keepGoing = lColorOperationComputation.evaluateBranchColor(state, pParameters, branch, masterResult);
            keepGoing &= lColorOperationComputation.computeAndCompositeResult(masterResult, branch);
            if (!keepGoing)
            {
                break;
            }
        }    

        lColorOperationComputation.finalize(shaderResult, state, pParameters, masterResult);

        if (mode == ColorOpNoContribution || mode == ColorOpResultToBeauty)
        {
            for (unsigned int fb = 0; fb < numberOfFrameBuffers; fb++)
            {
                frameBufferInfo[fb].stack[traceLevel].currentValue = BLACK;
            }      
        }

        if (mode == ColorOpResultToBeauty)
        {
            ParentClass::writeToFrameBuffers(state,
                                             frameBufferInfo,
                                             passTypeInfo,
                                             *pResult,
                                             BEAUTY,
                                             false);
            ParentClass::writeToFrameBuffers(state,
                                             frameBufferInfo,
                                             passTypeInfo,
                                             *pResult,
                                             BEAUTY_NO_SHADOW,
                                             false);
        }
    }
    return miTRUE;
}

/*!
    \brief Base class for color operations that have a single color input

    Provided for convenience. It predefines the branchCount, initialize and finalize methods.
    Only the evaluateBranch() and computeAndCompositeResult() methods need to be implemented.
    In this use case, all initialization code and parameter evaluations are implemented 
    in the evaluateBranch method, which will only be called once. All transform
    operations are performed in computeAndCompositeResult.
*/
template<typename ColorOperationShaderParameters, typename ColorOperationShaderResult>
class SimpleColorOperationComputation
{
public:
    inline unsigned int branchCount() 
    {
        return 1;
    }

    inline bool initialize(ColorOperationShaderResult* pResult, miState* state, ColorOperationShaderParameters* pParameters,
        unsigned int numberOfFrameBuffers, PassTypeInfo* passTypeInfo, FrameBufferInfo* frameBufferInfo) 
    {
        mNumberOfFrameBuffers = numberOfFrameBuffers;
        mPassTypeInfo = passTypeInfo;
        mFrameBufferInfo = frameBufferInfo;
        return true;
    }
    
    inline void finalize(ColorOperationShaderResult *pResult, miState* state, ColorOperationShaderParameters* pParameters, ColorOperationFbResult& masterResult)
    {
        (*(miColor*)pResult) = masterResult.compositeColor;
    }

protected:
    unsigned int        mNumberOfFrameBuffers;
    FrameBufferInfo*    mFrameBufferInfo;
    PassTypeInfo*       mPassTypeInfo;
};

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus
#endif // ADSK_COLOR_OPERATION_SHADER_H

// ==========================================================================
// Copyright 2009 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

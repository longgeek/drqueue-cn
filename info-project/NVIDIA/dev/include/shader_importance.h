
/******************************************************************************
 * Copyright 1986, 2013 NVIDIA Corporation. All rights reserved.
 ******************************************************************************
 *
 *  Created     : 28.04.2010
 *  Author      : sehera
 *  Module      : api
 *  Purpose     : mental ray C++ shader interface extensions
 *
 *  \file shader_importance.h
 *  mental ray C++ shader interface extensions.
 *
 *  This file provides interfaces that allow to change the state importance
 *  in a convinient way.
 *
 *  shader_importance.h is included by mi_shader_if.h, which in turn is
 *  included from shader.h if the shader is compiled as C++ code.
 *  A shader does not need to include this file directly.
 */

#ifndef SHADER_IMPORTANCE_H_
#define SHADER_IMPORTANCE_H_
#include "mi_shader_if.h"

namespace mi {
namespace shader_v3 {

class State_importance
{
public:

    State_importance()
	: m_old_importance(-1.0f)
	, m_state(0)
    {}
    State_importance(miState* state, float importance)
	: m_old_importance(state->importance)
	, m_state(state)
    {
	if(m_old_importance<0.0f)
	    m_state->importance = importance;
	else
	    m_state->importance *=importance;
    }
    ~State_importance()
    {
	if(m_state)
	    m_state->importance = m_old_importance;
    }

    void set(miState *state, float importance)
    {
	if(m_state)
	    return;
	m_state = state;
	m_old_importance = m_state->importance;
	if(m_old_importance<0.0f)
	    m_state->importance = importance;
	else
	    m_state->importance *=importance;
    }


private:
    float	 	m_old_importance;
    miState*		m_state;

};

}
}


#endif /* SHADER_IMPORANCE_H_ */

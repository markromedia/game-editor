#include "opengl.h"
#include "graphics/glstate.hpp"

std::set<GLuint> GLState::global_states;
std::set<GLuint> GLState::client_states;
GLenum GLState::_sfactor;
GLenum GLState::_dfactor;

bool GLState::setState(std::set<GLuint>& states, GLuint state, bool isEnable) 
{
	std::set<GLuint>::iterator disabled_it = states.find(state);
	std::set<GLuint>::iterator enabled_it = states.find(0x1 << 31 | state);
	std::set<GLuint>::iterator i1 = isEnable ? enabled_it : disabled_it;
	std::set<GLuint>::iterator i2 = isEnable ? disabled_it : enabled_it;

	if (i1 == states.end() || i2 != states.end())  
	{
		if (i2 != states.end())				// Remove "opposite" state (i.e. if enable, and a disabled state is present, remove it)
		{
			states.erase(i2);
		}

		if (isEnable) {
			states.insert(0x1 << 31 | state);
		} 
		else
		{
			states.insert(state);
		}

		return true;
	}
	return false;
}


void GLState::Enable(GLuint state) 
{
	if (GLState::setState(global_states, state, true)) 
	{
		glEnable(state);
	}
}

void GLState::Disable(GLuint state) 
{
	if (GLState::setState(global_states, state, false)) 
	{
		glDisable(state);
	}
}

void GLState::EnableClientState(GLuint state)
{
	if (GLState::setState(global_states, state, true)) 
	{
		glEnableClientState(state);
	}
}

void GLState::DisableClientState(GLuint state)
{
	if (GLState::setState(global_states, state, false)) 
	{
		glDisableClientState(state);
	}
}

void GLState::SetBlendModes(GLenum sfactor, GLenum dfactor)
{
	if (sfactor != _sfactor || dfactor != _dfactor)
	{
		glBlendFunc(sfactor, dfactor);
		_sfactor = sfactor;
		_dfactor = dfactor;
	}
}
/// Declares the gl state class.
#ifndef __GL_STATE__hpp
#define __GL_STATE__hpp

#include "opengl.h"
#include <vector>
#include <set>

class GLState
{
private:
	static std::set<GLuint> global_states;
	static std::set<GLuint> client_states;

	static bool setState(std::set<GLuint>& states, GLuint state, bool isEnable);

	//for blend more
	static GLenum _sfactor;
	static GLenum _dfactor;
public:

	static void Enable(GLuint state);

	static void Disable(GLuint state);

	static void EnableClientState(GLuint state);

	static void DisableClientState(GLuint state);

	static void SetBlendModes(GLenum sfactor, GLenum dfactor);
};

#endif  // __GL_STATE__hpp
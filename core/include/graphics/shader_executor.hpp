#ifndef __RENDEREX_hpp
#define __RENDEREX_hpp

#include "opengl.h"

namespace graphics {
	//forward declarations
	class RenderOperation;

	class ShaderExecutor
	{
	protected:
		GLuint programObject;
	public:
		/// Initialises this object.
		virtual void Init() = 0;

		/// Executes this render executor
		/// @param [in,out]	renderOp	If non-null, the render operation.
		virtual void Execute(graphics::RenderOperation* renderOp) = 0;
	};
}

#endif  // __RENDEREX_hpp

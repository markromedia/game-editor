#ifndef __RENDEREX_hpp
#define __RENDEREX_hpp

#include "opengl.h"

namespace Graphics {
	//forward declarations
	class RenderOperation;

	class RenderExecutor 
	{
	protected:
		GLuint programObject;
	public:
		/// Initialises this object.
		virtual void Init() = 0;

		/// Executes this render executor
		/// @param [in,out]	renderOp	If non-null, the render operation.
		virtual void Execute(Graphics::RenderOperation* renderOp) = 0;
	};
}

#endif  // __RENDEREX_hpp

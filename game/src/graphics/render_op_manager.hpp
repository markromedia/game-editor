#ifndef __RENDER_OP_MANAGER_hpp
#define __RENDER_OP_MANAGER_hpp

#include <string>
#include <vector>

namespace Graphics {
	//forward declarations
	class RenderOperation;
	class Color4f;

	class RenderOperationManager
	{
	private:
		/// @summary	The instance.
		static RenderOperationManager* instance;

		/// @summary	The render operations.
		std::vector<RenderOperation> render_operations;

		/// Checks for and/or create instance.
		static void _checkCreateInstance();

		/// Default constructor.
		RenderOperationManager(void);
	public:
		/// Returns a render op which is tied to the draw texture operation
		static RenderOperation* GetDrawTextureOp(std::string texture, int width, int height, int texture_width, int texture_height);

		/// Gets a draw model operation.
		/// @param	model	The model.
		/// @return	null if it fails, else the draw model operation.
		static RenderOperation* RenderOperationManager::GetDrawModelOp(int model);

		/// Gets a draw wireframe operation.
		/// @param	model	The model.
		/// @return	null if it fails, else the draw wireframe operation.
		static RenderOperation* RenderOperationManager::GetDrawWireframeOp(int model);
	};
}

#endif  // __RENDER_OP_MANAGER_hpp
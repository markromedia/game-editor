#ifndef __FRAME_hpp
#define __FRAME_hpp

#include <queue>

namespace Graphics {
	//forward declarations 
	class RenderExecutor;
	class RenderOperation;
	class Camera;

	class Frame
	{
	private:
		/// @summary	The list of render executors.
		std::vector<RenderExecutor*> executors;
	public:
		/// Default constructor.
		Frame(void);

		/// initialize this object
		void Init();

		/// @summary	The queue of render operations
		std::queue<RenderOperation*>			render_queue;

		/// Adds render operation to the render queue
		/// @param [in,out]	renderOperation	If non-null, the render operation.
		/// @param [in,out]	camera		   	If non-null, the camera.
		void QueueRenderOperation(RenderOperation* renderOperation, Camera* camera);

		/// Renders the frame and empties the render queue.
		void Render();
	};
}
#endif  // __FRAME_hpp
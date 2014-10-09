#ifndef __RENDER_QUEUE__screen__
#define __RENDER_QUEUE__screen__

#include <SDL.h>
#include <iostream>
#include <queue>
#include <map>
#include <string>

namespace Graphics {
    //forward declarations
    class RenderExecutor;
    class RenderOperation;
    class Camera;

    class RenderQueue {
    private:
        /// @summary	The instance.
        static RenderQueue *_instance;
        /// @summary	The list of render executors.
        std::map<int, RenderExecutor *> _executors;
        /// @summary	the drawing window.
        SDL_Window* _window;
    public:
        /// @summary	The queue of render operations
        std::queue<RenderOperation *> _queue;
        /// @summary creates the instance
        static void Init(SDL_Window* window);
        /// Adds render operation to the render queue
        /// @param [in,out]	renderOperation	If non-null, the render operation.
        /// @param [in,out]	camera		   	If non-null, the camera.
        static void QueueRenderOperation(RenderOperation *renderOperation, Camera *camera);
        /// Renders the frame and empties the render queue.
        static void Execute();
        /// Adds a render executor to 'executor'.
        /// @param	name				The name.
        /// @param [in,out]	executor	If non-null, the executor.
        static void AddRenderExecutor(int id, RenderExecutor *executor);
    };
}


#endif /* defined(__RENDER_QUEUE__screen__) */

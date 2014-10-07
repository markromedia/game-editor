/// Declares the gl state class.
#ifndef __AWESOMIUM__hpp
#define __AWESOMIUM__hpp

#include <Awesomium/WebCore.h>

#include "game.hpp"
#include "graphics/render_operation.hpp"


class AwesomiumHandler
{
private:
	/// @summary	The webcore.
	Awesomium::WebCore* _webcore;

	/// @summary	The render operation
	Graphics::RenderOperation* _render_operation;
public:
	/// Initialises this object.
	void Init();

	/// Executes the event action.
	/// @param [in,out]	Event	If non-null, the event.
	void OnEvent(SDL_Event* Event);

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);
};

class AwesomiumSurface : public Awesomium::Surface {
public:
};

class AwesomiumSurfaceFactory : public Awesomium::SurfaceFactory {
public:
};

#endif  // __AWESOMIUM__hpp
/// Declares the gl state class.
#ifndef __AWESOMIUM__hpp
#define __AWESOMIUM__hpp

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>

#include "game.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/texture.hpp"
#include <graphics/transform.hpp>
#include <queue>

class AwesomiumSurfaceFactory;
class AwesomiumHandler
{
private:
	/// @summary	The webcore.
	Awesomium::WebCore* _webcore;

	/// @summary	The awesomium factory
	AwesomiumSurfaceFactory* _awesomium_surface_factory;
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
private:
	int _width, _height;
public:
	AwesomiumSurface(int width, int height);

	/// @summary	The texture.
	Graphics::Texture* _texture;

	/// @summary	The render operation
	Graphics::RenderOperation* _render_operation;

	void Paint(unsigned char* src_buffer,
				int src_row_span,
				const Awesomium::Rect& src_rect,
				const Awesomium::Rect& dest_rect);

	void Scroll(int dx, int dy, const Awesomium::Rect& clip_rect);
};

class AwesomiumSurfaceFactory : public Awesomium::SurfaceFactory {
public:
	std::vector<AwesomiumSurface*> _awesomium_surfaces;

	Awesomium::Surface* CreateSurface(Awesomium::WebView* view,
											int width,
											int height);

	void DestroySurface(Awesomium::Surface* surface);
};

#endif  // __AWESOMIUM__hpp
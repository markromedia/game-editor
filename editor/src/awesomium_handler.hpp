/// Declares the gl state class.
#ifndef __AWESOMIUM__hpp
#define __AWESOMIUM__hpp

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include "game.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/texture.hpp"
#include <graphics/transform.hpp>
#include <queue>

class AwesomiumSurfaceFactory;
class JavascriptDelegate;
class AwesomiumHandler
{
private:
	/// awesomium stuffs
	Awesomium::WebCore* _webcore;
	Awesomium::WebSession* _websession;
	Awesomium::WebView* _webview;

	//the javascript delegate
	JavascriptDelegate* _javascript_delegate;

	/// @summary	The awesomium factory
	AwesomiumSurfaceFactory* _awesomium_surface_factory;

	/// Reload user interface.
	void doReloadUi();

	/// @summary	true to do reload.
	bool _reload_ui;

	//keyboard events handling
	void handleSDLKeyEvent(Awesomium::WebView* webView, const SDL_Event& event);
	int getWebKeyFromSDLKey(SDL_Keycode key);
public:

	/// Initialises this object.
	void Init();

	/// Executes the event action.
	/// @param [in,out]	Event	If non-null, the event.
	void OnEvent(SDL_Event* Event);

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);

	/// Reload user interface.
	void ReloadUi();
};

class AwesomiumSurface : public Awesomium::Surface {
private:
	int _width, _height;

	unsigned char* _buffer;

	
public:
	bool dirty;

	AwesomiumSurface(int width, int height);

	/// @summary	The texture.
	graphics::Texture* _texture;

	/// @summary	The render operation
	graphics::RenderOperation* _render_operation;

	void Paint(unsigned char* src_buffer,
				int src_row_span,
				const Awesomium::Rect& src_rect,
				const Awesomium::Rect& dest_rect);

	void Scroll(int dx, int dy, const Awesomium::Rect& clip_rect);

	void UpdateTexture();
};

class AwesomiumSurfaceFactory : public Awesomium::SurfaceFactory {
public:
	std::vector<AwesomiumSurface*> _awesomium_surfaces;

	Awesomium::Surface* CreateSurface(Awesomium::WebView* view,
											int width,
											int height);

	void DestroySurface(Awesomium::Surface* surface);
};

class AwesomiumResourceInterceptor : public Awesomium::ResourceInterceptor
{
public:
	Awesomium::ResourceResponse* OnRequest(Awesomium::ResourceRequest* request);
};

#endif  // __AWESOMIUM__hpp
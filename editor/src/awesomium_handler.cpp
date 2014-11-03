#include "awesomium_handler.hpp"

#include <algorithm>

#define GLM_FORCE_RADIANS 

#include "graphics/render_op_manager.hpp"
#include "graphics/render_queue.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/screen.h"
#include "platform/FileSystem.hpp"
#include <graphics/texture_manager.hpp>
#include "javascript_delegate.hpp"
#include <graphics/primitives.hpp>

void AwesomiumHandler::Init()
{
	int width = Screen::Width();
	int height = Screen::Height();

	_webcore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	//set custom surface factory
	_awesomium_surface_factory = new AwesomiumSurfaceFactory();
	_webcore->set_surface_factory(_awesomium_surface_factory);
	_webcore->set_resource_interceptor(new AwesomiumResourceInterceptor());
	//configure session
	_websession = _webcore->CreateWebSession(Awesomium::WSLit(""), Awesomium::WebPreferences());
	
	_webview = _webcore->CreateWebView(width, height, _websession);
	_webview->SetTransparent(true);

	//register the javascript delegate
	_javascript_delegate = new JavascriptDelegate(this, _webview);
	_webview->set_js_method_handler(_javascript_delegate);

	doReloadUi();
}
	
void AwesomiumHandler::doReloadUi()
{
	Awesomium::WebURL url(Awesomium::WSLit("asset://editor/index.html"));;
    _webview->LoadURL(url);

	while (_webview ->IsLoading()) {
	  _webcore->Update();
	}

	Sleep(1000);
	_reload_ui = false;
}


void AwesomiumHandler::OnEvent(SDL_Event* Event)
{
	switch(Event->type){		
		case SDL_MOUSEMOTION : {
			_webview->InjectMouseMove(Event->motion.x, Event->motion.y);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			if (Event->button.button == SDL_BUTTON_LEFT) {
				_webview->InjectMouseDown(Awesomium::kMouseButton_Left);
			} else if (Event->button.button == SDL_BUTTON_RIGHT) {
				_webview->InjectMouseDown(Awesomium::kMouseButton_Right);
			} else if (Event->button.button == SDL_BUTTON_MIDDLE) {
				_webview->InjectMouseDown(Awesomium::kMouseButton_Middle);
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			if (Event->button.button == SDL_BUTTON_LEFT) {
				_webview->InjectMouseUp(Awesomium::kMouseButton_Left);
			} else if (Event->button.button == SDL_BUTTON_RIGHT) {
				_webview->InjectMouseUp(Awesomium::kMouseButton_Right);
			} else if (Event->button.button == SDL_BUTTON_MIDDLE) {
				_webview->InjectMouseUp(Awesomium::kMouseButton_Middle);
			}
			break;
		}
		case SDL_KEYDOWN :
		case SDL_KEYUP : {
			//handleSDLKeyEvent(_webview, *Event);
			break;				 
		}
	}
}

void AwesomiumHandler::handleSDLKeyEvent(Awesomium::WebView* webView, const SDL_Event& event) {
  if (!(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP))
    return;
 
  Awesomium::WebKeyboardEvent keyEvent;
 
  keyEvent.type = event.type == SDL_KEYDOWN?
                  Awesomium::WebKeyboardEvent::kTypeKeyDown :
                  Awesomium::WebKeyboardEvent::kTypeKeyUp;
 
  char* buf = new char[20];
  keyEvent.virtual_key_code = getWebKeyFromSDLKey(event.key.keysym.sym);
  Awesomium::GetKeyIdentifierFromVirtualKeyCode(keyEvent.virtual_key_code,
      &buf);
  strcpy(keyEvent.key_identifier, buf);
  delete[] buf;
 
  keyEvent.modifiers = 0;
 
  if (event.key.keysym.mod & KMOD_LALT || event.key.keysym.mod & KMOD_RALT)
    keyEvent.modifiers |= Awesomium::WebKeyboardEvent::kModAltKey;
  if (event.key.keysym.mod & KMOD_LCTRL || event.key.keysym.mod & KMOD_RCTRL)
    keyEvent.modifiers |= Awesomium::WebKeyboardEvent::kModControlKey;
  if (event.key.keysym.mod & KMOD_LSHIFT || event.key.keysym.mod & KMOD_RSHIFT)
    keyEvent.modifiers |= Awesomium::WebKeyboardEvent::kModShiftKey;
  if (event.key.keysym.mod & KMOD_NUM)
    keyEvent.modifiers |= Awesomium::WebKeyboardEvent::kModIsKeypad;
 
  keyEvent.native_key_code = event.key.keysym.scancode;
 
  if (event.type == SDL_KEYUP) {
    webView->InjectKeyboardEvent(keyEvent);
  } else {
    unsigned int chr;
    if ((event.key.keysym.scancode & 0xFF80) == 0)
      chr = event.key.keysym.scancode & 0x7F;
    else
      chr = event.key.keysym.scancode;
 
    keyEvent.text[0] = chr;
    keyEvent.unmodified_text[0] = chr;
 
    webView->InjectKeyboardEvent(keyEvent);
 
    if (chr) {
      keyEvent.type = Awesomium::WebKeyboardEvent::kTypeChar;
      keyEvent.virtual_key_code = chr;
      keyEvent.native_key_code = chr;
      webView->InjectKeyboardEvent(keyEvent);
    }
  }
}

void AwesomiumHandler::Update(float dt)
{
	if (_reload_ui)
	{
		doReloadUi();
	}

	_webcore->Update();
	for(std::vector<AwesomiumSurface*>::iterator it = _awesomium_surface_factory->_awesomium_surfaces.begin(); it != _awesomium_surface_factory->_awesomium_surfaces.end(); ++it) {
		if ((*it)->dirty) {
			(*it)->UpdateTexture();
		}
		graphics::RenderQueue::QueueRenderOperation((*it)->_render_operation, Game::OrthoCamera);
	}
}

void AwesomiumHandler::ReloadUi()
{
	_reload_ui = true;
}

AwesomiumSurface::AwesomiumSurface(int width, int height) : _width(width), _height (height)
{
	//init the drawable buffer
	_buffer = new unsigned char[width * height * 4];
	memset(_buffer, 0, sizeof(char)* width * height * 4 ); //zero everything out
	
	_render_operation = new graphics::RenderOperation();
	_render_operation->Operation_Type = graphics::RenderOperation::DRAW_TEXTURE;

	//transform. 
	graphics::Transform transform;
    transform.translate(width / 2.0f, height / 2.0f, 0);
	_render_operation->ModelMatrix = transform.getMatrix();
	
	//load texture
	_render_operation->_material->_diffuse_texture(graphics::TextureManager::CreateTexture(GL_BGRA_EXT, width, height));
	
	//create vbo and quad
	_render_operation->VertexBuffer = graphics::VertexBufferManager::GetBuffer(USE_TEXTURE);
	graphics::Quad quad = graphics::Primitives::CreateQuad(_render_operation->VertexBuffer, width, height);

	//text coords
	quad.v1->s = 0; quad.v1->t = 0;
	quad.v2->s = 1; quad.v2->t = 0;
	quad.v3->s = 0; quad.v3->t = 1;
	quad.v4->s = 1; quad.v4->t = 1;
}

void AwesomiumSurface::Paint(unsigned char* src_buffer, int src_row_span, Awesomium::Rect const& src_rect, Awesomium::Rect const& dest_rect)
{
	int rowspan = _width * 4;
	
	for (int row = 0; row < dest_rect.height; row++) {
		memcpy(_buffer + (row + dest_rect.y) * rowspan + (dest_rect.x * 4),
				src_buffer + (row + src_rect.y) * src_row_span + (src_rect.x * 4),
				dest_rect.width * 4);
	}
	
	dirty = true;
}

void AwesomiumSurface::Scroll(int dx, int dy, Awesomium::Rect const& clip_rect)
{
}

void AwesomiumSurface::UpdateTexture()
{
	glBindTexture(GL_TEXTURE_2D, _render_operation->_material->_diffuse_texture()->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, _buffer);
	dirty = false;
}

Awesomium::Surface* AwesomiumSurfaceFactory::CreateSurface(Awesomium::WebView* view, int width, int height)
{
	_awesomium_surfaces.push_back(new AwesomiumSurface(width, height));
	return _awesomium_surfaces.back();
}

void AwesomiumSurfaceFactory::DestroySurface(Awesomium::Surface* surface)
{
}

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

Awesomium::ResourceResponse* AwesomiumResourceInterceptor::OnRequest(Awesomium::ResourceRequest* request)
{
	bool isAsset = std::strcmp(ToString(request->url().scheme()).c_str(), "asset")==0;
    bool isFile = std::strcmp(ToString(request->url().scheme()).c_str(), "file")==0;

    if(!isAsset && !isFile)
    {
        //if it is neither of these we "may" still intercept the call, this allows for offline-online versions to work
        return Awesomium::ResourceInterceptor::OnRequest(request);
    }

    if(isAsset)
    {
        //Blah blah, do whatever
    }
    else if(isFile)
    {
        //Blah blah, same
    }

    //As you can see this isn't very, but it worked for my purposes
    std::string contentpath = FileSystem::GetResourceFilePath("resources/editor/ui") + ToString(request->url().path()); 

    Awesomium::WebString datatype;
    std::string filename = Awesomium::ToString(request->url().filename());

    //I still want to check for the correct mime type
    if     (has_suffix(filename, ".html")) datatype = Awesomium::WSLit("text/html");
    else if(has_suffix(filename, ".js"))   datatype = Awesomium::WSLit("text/javascript");
    else if(has_suffix(filename, ".css"))  datatype = Awesomium::WSLit("text/css");
    else if(has_suffix(filename, ".swf"))  datatype = Awesomium::WSLit("application/x-shockwave-flash");
    else if(has_suffix(filename, ".zip"))  datatype = Awesomium::WSLit("application/zip");
    else if(has_suffix(filename, ".txt"))  datatype = Awesomium::WSLit("text/plain");
    else if(has_suffix(filename, ".text")) datatype = Awesomium::WSLit("text/plain");
    else if(has_suffix(filename, ".png"))  datatype = Awesomium::WSLit("image/png");
    else if(has_suffix(filename, ".jpeg")) datatype = Awesomium::WSLit("image/jpeg");
    else if(has_suffix(filename, ".jpg"))  datatype = Awesomium::WSLit("image/jpeg");
    else if(has_suffix(filename, ".webm")) datatype = Awesomium::WSLit("video/webm");
    else if(has_suffix(filename, ".mp4"))  datatype = Awesomium::WSLit("video/mp4");
    else if(has_suffix(filename, ".ogv"))  datatype = Awesomium::WSLit("video/ogg");
    else if(has_suffix(filename, ".flv"))  datatype = Awesomium::WSLit("video/flv");

    if(!datatype.IsEmpty())
    {
        FILE * pFile;
        long lSize;
        unsigned char * buffer;
        size_t result;

        pFile = fopen ( contentpath.c_str() , "rb" );
        if (pFile!=NULL)
        {
            // obtain file size:
            fseek (pFile , 0 , SEEK_END);
            lSize = ftell (pFile);
            rewind (pFile);

            // allocate memory to contain the whole file:
            buffer = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
            if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

            // copy the file into the buffer:
            result = fread (buffer,1,lSize,pFile);
            if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

            //This is where the magic happens!!
            return Awesomium::ResourceResponse::Create(lSize, buffer, datatype);

            // terminate
            fclose (pFile);
            free (buffer);
        }
        else
        {
            //send this off to the default request handler instead of it being a local file
            return Awesomium::ResourceInterceptor::OnRequest(request);
        }
    }else
    {
        //send this off to the default request handler instead of it being a local file
        return Awesomium::ResourceInterceptor::OnRequest(request);
    }

}

/// Helper Macro
#define mapKey(a, b) case SDLK_##a: return Awesomium::KeyCodes::AK_##b;
 
/// Get an Awesomium KeyCode from an SDLKey Code
int AwesomiumHandler::getWebKeyFromSDLKey(SDL_Keycode key) {
  switch (key) {
    mapKey(BACKSPACE, BACK)
    mapKey(TAB, TAB)
    mapKey(CLEAR, CLEAR)
    mapKey(RETURN, RETURN)
    mapKey(PAUSE, PAUSE)
    mapKey(ESCAPE, ESCAPE)
    mapKey(SPACE, SPACE)
    mapKey(EXCLAIM, 1)
    mapKey(QUOTEDBL, 2)
    mapKey(HASH, 3)
    mapKey(DOLLAR, 4)
    mapKey(AMPERSAND, 7)
    mapKey(QUOTE, OEM_7)
    mapKey(LEFTPAREN, 9)
    mapKey(RIGHTPAREN, 0)
    mapKey(ASTERISK, 8)
    mapKey(PLUS, OEM_PLUS)
    mapKey(COMMA, OEM_COMMA)
    mapKey(MINUS, OEM_MINUS)
    mapKey(PERIOD, OEM_PERIOD)
    mapKey(SLASH, OEM_2)
    mapKey(0, 0)
    mapKey(1, 1)
    mapKey(2, 2)
    mapKey(3, 3)
    mapKey(4, 4)
    mapKey(5, 5)
    mapKey(6, 6)
    mapKey(7, 7)
    mapKey(8, 8)
    mapKey(9, 9)
    mapKey(COLON, OEM_1)
    mapKey(SEMICOLON, OEM_1)
    mapKey(LESS, OEM_COMMA)
    mapKey(EQUALS, OEM_PLUS)
    mapKey(GREATER, OEM_PERIOD)
    mapKey(QUESTION, OEM_2)
    mapKey(AT, 2)
    mapKey(LEFTBRACKET, OEM_4)
    mapKey(BACKSLASH, OEM_5)
    mapKey(RIGHTBRACKET, OEM_6)
    mapKey(CARET, 6)
    mapKey(UNDERSCORE, OEM_MINUS)
    mapKey(BACKQUOTE, OEM_3)
    mapKey(a, A)
    mapKey(b, B)
    mapKey(c, C)
    mapKey(d, D)
    mapKey(e, E)
    mapKey(f, F)
    mapKey(g, G)
    mapKey(h, H)
    mapKey(i, I)
    mapKey(j, J)
    mapKey(k, K)
    mapKey(l, L)
    mapKey(m, M)
    mapKey(n, N)
    mapKey(o, O)
    mapKey(p, P)
    mapKey(q, Q)
    mapKey(r, R)
    mapKey(s, S)
    mapKey(t, T)
    mapKey(u, U)
    mapKey(v, V)
    mapKey(w, W)
    mapKey(x, X)
    mapKey(y, Y)
    mapKey(z, Z)
    mapKey(DELETE, DELETE)
    mapKey(KP_0, NUMPAD0)
    mapKey(KP_1, NUMPAD1)
    mapKey(KP_2, NUMPAD2)
    mapKey(KP_3, NUMPAD3)
    mapKey(KP_4, NUMPAD4)
    mapKey(KP_5, NUMPAD5)
    mapKey(KP_6, NUMPAD6)
    mapKey(KP_7, NUMPAD7)
    mapKey(KP_8, NUMPAD8)
    mapKey(KP_9, NUMPAD9)
    mapKey(KP_PERIOD, DECIMAL)
    mapKey(KP_DIVIDE, DIVIDE)
    mapKey(KP_MULTIPLY, MULTIPLY)
    mapKey(KP_MINUS, SUBTRACT)
    mapKey(KP_PLUS, ADD)
    mapKey(KP_ENTER, SEPARATOR)
    mapKey(KP_EQUALS, UNKNOWN)
    mapKey(UP, UP)
    mapKey(DOWN, DOWN)
    mapKey(RIGHT, RIGHT)
    mapKey(LEFT, LEFT)
    mapKey(INSERT, INSERT)
    mapKey(HOME, HOME)
    mapKey(END, END)
    mapKey(PAGEUP, PRIOR)
    mapKey(PAGEDOWN, NEXT)
    mapKey(F1, F1)
    mapKey(F2, F2)
    mapKey(F3, F3)
    mapKey(F4, F4)
    mapKey(F5, F5)
    mapKey(F6, F6)
    mapKey(F7, F7)
    mapKey(F8, F8)
    mapKey(F9, F9)
    mapKey(F10, F10)
    mapKey(F11, F11)
    mapKey(F12, F12)
    mapKey(F13, F13)
    mapKey(F14, F14)
    mapKey(F15, F15)
    mapKey(NUMLOCKCLEAR, NUMLOCK)
    mapKey(CAPSLOCK, CAPITAL)
    mapKey(SCROLLLOCK, SCROLL)
    mapKey(RSHIFT, RSHIFT)
    mapKey(LSHIFT, LSHIFT)
    mapKey(RCTRL, RCONTROL)
    mapKey(LCTRL, LCONTROL)
    mapKey(RALT, RMENU)
    mapKey(LALT, LMENU)
    mapKey(MODE, MODECHANGE)
    mapKey(HELP, HELP)
    mapKey(PRINTSCREEN, SNAPSHOT)
    mapKey(SYSREQ, EXECUTE)
  default:
    return Awesomium::KeyCodes::AK_UNKNOWN;
  }
}
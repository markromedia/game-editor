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

	doReloadUi();
	
	//register the javascript delegate
	_javascript_delegate = new JavascriptDelegate(this, _webview);
	_webview->set_js_method_handler(_javascript_delegate);
    
    std::vector<File> files = FileSystem::ListDirectoryContents(FileSystem::GetResourceFilePath("/Users/MarkUdit/code/flight/build/editor/Debug/resources/editor/ui"));
}
	
void AwesomiumHandler::doReloadUi()
{
	Awesomium::WebURL url(Awesomium::WSLit("asset://editor/index.html"));;
    _webview->LoadURL(url);

	while (_webview ->IsLoading()) {
	  _webcore->Update();
	}

//	Sleep(1000);
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
		Graphics::RenderQueue::QueueRenderOperation((*it)->_render_operation, Game::OrthoCamera);
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
	
	_render_operation = new Graphics::RenderOperation();
	_render_operation->Operation_Type = Graphics::RenderOperation::DRAW_TEXTURE;

	//transform. 
	Graphics::Transform transform;
    transform.translate(width / 2.0f, height / 2.0f, 0);
	_render_operation->ModelMatrix = transform.getMatrix();
	
	//load texture
	_render_operation->_material->_diffuse_texture(Graphics::TextureManager::CreateTexture(GL_BGRA_EXT, width, height));
	
	//create vbo and quad
	_render_operation->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(USE_TEXTURE);
	Graphics::Quad quad = Graphics::Primitives::CreateQuad(_render_operation->VertexBuffer, width, height);

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
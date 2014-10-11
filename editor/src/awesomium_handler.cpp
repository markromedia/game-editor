#include "awesomium_handler.hpp"

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/render_op_manager.hpp"
#include "graphics/render_queue.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/transform.hpp"
#include "graphics/screen.h"
#include <graphics/texture_manager.hpp>

void AwesomiumHandler::Init()
{
	int width = Screen::Width();
	int height = Screen::Height();

	_webcore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	//set custom surface factory
	_awesomium_surface_factory = new AwesomiumSurfaceFactory();
	_webcore->set_surface_factory(_awesomium_surface_factory);
	
	Awesomium::WebView* view = _webcore->CreateWebView(width, height);
	view->SetTransparent(true);

	Awesomium::WebString web_string = Awesomium::WebString::CreateFromUTF8("data:text/html,<body style=\"background-color: transparent\"><h1>Hello World</h1></body>", strlen("data:text/html,<body style=\"background-color: transparent\"><h1>Hello World</h1></body>"));

    Awesomium::WebURL url(web_string);
    view->LoadURL(url);

	while (view->IsLoading()) {
	  _webcore->Update();
	}

	Sleep(300);
	_webcore->Update();
}

void AwesomiumHandler::OnEvent(SDL_Event* Event)
{
}


void AwesomiumHandler::Update(float dt)
{
	for(std::vector<AwesomiumSurface*>::iterator it = _awesomium_surface_factory->_awesomium_surfaces.begin(); it != _awesomium_surface_factory->_awesomium_surfaces.end(); ++it) {
		Graphics::RenderQueue::QueueRenderOperation((*it)->_render_operation, Game::OrthoCamera);
	}
}

AwesomiumSurface::AwesomiumSurface(int width, int height) : _width(width), _height (height)
{
	_render_operation = new Graphics::RenderOperation();
	_render_operation->Operation_Type = Graphics::RenderOperation::DRAW_TEXTURE;

	//transform. 
	Graphics::Transform transform;
    transform.translate(width / 2.0f, height / 2.0f, 0);
	_render_operation->ModelMatrix = transform.getMatrix();
	
	//load texture
	_render_operation->Diffuse_Texture = Graphics::TextureManager::CreateTexture(GL_BGRA_EXT, width, height);
	
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
	glBindTexture(GL_TEXTURE_2D, _render_operation->Diffuse_Texture->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, src_buffer);
}

void AwesomiumSurface::Scroll(int dx, int dy, Awesomium::Rect const& clip_rect)
{
	int a = 1;
}

Awesomium::Surface* AwesomiumSurfaceFactory::CreateSurface(Awesomium::WebView* view, int width, int height)
{
	_awesomium_surfaces.push_back(new AwesomiumSurface(width, height));
	return _awesomium_surfaces.back();
}

void AwesomiumSurfaceFactory::DestroySurface(Awesomium::Surface* surface)
{
}
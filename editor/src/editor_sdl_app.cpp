#include "editor_sdl_app.hpp"
#include "screen.h"

EditorSdlApp::EditorSdlApp()
{
	SDLWindow = NULL;
	Running = true;
}

EditorSdlApp::EditorSdlApp( const EditorSdlApp& from )
{
	*this = from;
}

EditorSdlApp& EditorSdlApp::operator=( const EditorSdlApp& from )
{
	return *this;
}

EditorSdlApp::~EditorSdlApp( void )
{
}

int EditorSdlApp::OnExecute()
{
	if(OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	unsigned int previous_time = SDL_GetTicks();
	while(Running) {

		unsigned int time = SDL_GetTicks();
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}
		
		float dt = time - previous_time;
		editor->Update(dt);

		previous_time = time;
	}

	OnCleanup();

	return 0;
}

bool EditorSdlApp::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	//Request OpenGL 4.1 context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,            32);
	
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    if((SDLWindow = SDL_CreateWindow("Flight Editor",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     0,
                                     0,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED)) == NULL) {
		return false;
	}
    
	//grab screen size after maximized window created
    int w, h;
    SDL_GetWindowSize(SDLWindow, &w, &h);
    Screen::Init(w, h);

	/* Create our opengl context and attach it to our window */ 
	ctx = SDL_GL_CreateContext(SDLWindow);
    if (!ctx) {
        LOG_DEBUG("SDL_GL_CreateContext failed with error:");
        LOG_DEBUG(SDL_GetError());
    }

	LOG_DEBUG("Using OpenGL Version:");
	LOG_DEBUG((char*) glGetString(GL_VERSION));

	LOG_DEBUG("Using GLSL Version:");
	LOG_DEBUG((char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

	/* Initialize GLEW */
	LOG_DEBUG("Initializing GLEW");
    glewExperimental = GL_TRUE;
	glewInit();
	CHECK_GL_ERROR();

	/* set viewport */
	glViewport(0, 0, Screen::Width(), Screen::Height());
	
	/* This makes our buffer swap synchronized with the monitor's vertical refresh */ 
	SDL_GL_SetSwapInterval(1);

	//init the editor
	this->editor = new Editor();
	this->editor->Init();

	//make sure the game has opengl
	Game::SDLWindow = SDLWindow;
	Game::OpenGLContext = ctx;

	return true;
}

void EditorSdlApp::OnEvent( SDL_Event* Event )
{
	if(Event->type == SDL_QUIT) {
		Running = false;
	} 
	editor->OnEvent(Event);
}

void EditorSdlApp::OnCleanup()
{
	SDL_Quit();
}



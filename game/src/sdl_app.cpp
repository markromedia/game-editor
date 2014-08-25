#include "sdl_app.hpp"

SdlApp::SdlApp()
{
	SDLWindow = NULL;
	Running = true;
	game = new Game();
}

SdlApp::SdlApp( const SdlApp& from )
{
	*this = from;
}

SdlApp& SdlApp::operator=( const SdlApp& from )
{
	return *this;
}

SdlApp::~SdlApp( void )
{
}

int SdlApp::OnExecute()
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
		game->Update(dt);

		/*
		unsigned int end_time = SDL_GetTicks();

		unsigned int d = end_time - time;
		if (d < 32)
		{
			SDL_Delay(32 - d);		
		}
		*/

		previous_time = time;
	}

	OnCleanup();

	return 0;
}

bool SdlApp::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	//Request OpenGL 4.1 context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,            32);
//
//	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,        8);
//	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
//	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,        8);
//	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
//
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if((SDLWindow = SDL_CreateWindow("Flight",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == NULL) {
		return false;
	}

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
	glewInit();
	CHECK_GL_ERROR();

	/* set viewport */
	glViewport(0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
	
	/* This makes our buffer swap synchronized with the monitor's vertical refresh */ 
	SDL_GL_SetSwapInterval(1);

	// initialize librocket
	//libRocketSystemInterface = new LibRocketSystemInterface();
	//libRocketRenderer = new LibRocketRenderer();
	//Rocket::Core::SetSystemInterface(libRocketSystemInterface);
	//Rocket::Core::SetRenderInterface(libRocketRenderer);
	//Rocket::Core::Initialise();
	//Game::LibRocketContext = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT));

	// set game variables
	Game::SDLWindow = SDLWindow;
	Game::OpenGLContext = ctx;

	// initialize the game
	game->Init();

	return true;
}

void SdlApp::OnEvent( SDL_Event* Event )
{
	if(Event->type == SDL_QUIT) {
		Running = false;
	}
	game->OnEvent(Event);
}

void SdlApp::OnCleanup()
{
	SDL_Quit();
}



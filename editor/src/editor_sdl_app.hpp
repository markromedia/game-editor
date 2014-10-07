/// @file	component.hpp
/// #include "component.hpp" <BR>
/// --llib
///
/// Superclass of the components

//necessary for GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#ifndef _EDITOR_SDL_APP_hpp
#define _EDITOR_SDL_APP_hpp

//INCLUDES
//#include <Windows.h>
#include "opengl.h"
#include <SDL.h>
//#include <Rocket/Core.h>
#include "editor.hpp"
#include "constants.cpp"
#include "graphics/glstate.hpp"
#include "logger.hpp"
#include "gllogger.hpp"

class EditorSdlApp
{
public:
	/// Default constructor.
	EditorSdlApp(void);

	/// Copy constructor.
	///
	/// @param	from	Source for the.
	EditorSdlApp(const EditorSdlApp& from);

	/// Destructor.
	~EditorSdlApp(void);

	/// Assignment operator.
	///
	/// @param	from	Source for the.
	///
	/// @return	A shallow copy of this object.
	EditorSdlApp&                     operator=(const EditorSdlApp& from);  

	/// Executes the sdl app.
	///
	/// @return	.
	int OnExecute();
protected:

	/// Executes the initialise action.
	///
	/// @return	true if it succeeds, false if it fails.
	bool OnInit();

	/// Callback for events.
	///
	/// @param [in,out]	Event	If non-null, the event.
	void OnEvent(SDL_Event*		Event);

	/// Executes the cleanup action.
	void OnCleanup();

private:

	/// @summary	whether or not the app is running.
	bool Running;

	/// @summary	The sdl window.
	SDL_Window* SDLWindow;

	/// @summary	The opengl context.
	SDL_GLContext ctx;

	/// @summary	The game.
	Editor* editor;

};
#endif  // _EDITOR_SDL_APP_hpp
/// Declares the gl state class.
#ifndef __EDITOR__hpp
#define __EDITOR__hpp

#include "Awesomium/WebCore.h"

#include "game.hpp"
#include "awesomium_handler.hpp"

class Editor
{
private:
	/// @summary	The game.
	Game* _game;

	/// @summary	The awesomium handler.
	AwesomiumHandler* _awesomium_handler;
public:
	static bool _reload_awesomium;

	/// Initialises this object.
	void Init();

	/// Executes the event action.
	/// @param [in,out]	Event	If non-null, the event.
	void OnEvent(SDL_Event* Event);

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);
};

#endif  // __EDITOR__hpp
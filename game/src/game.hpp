/// @file	game.hpp
/// #include "game.hpp" <BR>
/// --llib
///
/// Declares the game class.
#ifndef _GAME_hpp
#define _GAME_hpp

// INCLUDES
#include <SDL.h>
//#include <Rocket/Core.h>
#include "graphics/frame.hpp"
#include "graphics/camera.hpp"

#include "camera_control.hpp"

//forward declaration
class Scene; 

///-----------------------------------------------------------------------------------------------
class Game
{
private:
	std::vector<float>			frame_times;
	/// Adds a frame time.
	void addFrameTime(float f);

	CameraControl* cameraControl;
public:
	/// Default constructor.
	Game(void);

	void Init();

	/// The main update function
	///
	/// @param	dt	The delta time.
	/// @param	Event any possibly sdl event (such as input). can be null
	void Update(float dt);

	/// Executes the event action.
	///
	/// @param [in,out]	Event	If non-null, the event.
	void OnEvent(SDL_Event* Event);

	/// @summary	The current scene.
	Scene*								current_scene;

	/// These are injected by sdl
	static SDL_Window*					SDLWindow;
	static SDL_GLContext				OpenGLContext;

	// The librocket context
	//static Rocket::Core::Context*		LibRocketContext;

	/// @summary	The main drawable frame
	static Graphics::Frame*				ScreenFrame;

	// the curent framerate/previous frame times
	static float						FrameRate, update_time, render_time;

	/// the cameras
	static Graphics::Camera				*PerspectiveCamera;
	static Graphics::Camera				*OrthoCamera;
	static Graphics::Camera				*SkyboxCamera;


};

///-----------------------------------------------------------------------------------------------
class Scene
{
public:
	/// Initialises this object.
	virtual void Init() = 0;

	/// called to update the main scene with the delta time
	///
	/// @param	dt	The delta time.
	virtual void Update(float dt) = 0;
};

#endif  // _GAME_hpp
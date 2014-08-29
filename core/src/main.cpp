// last-spacefighter.cpp : Defines the entry point for the console application.
//

// Include the lua headers (the extern "C" is a requirement because we're
// using C++ and lua has been compiled as C code)
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

// This is the only header we need to include for LuaBind to work
//#include "luabind/luabind.hpp"

#include "sdl_app.hpp"

#include <iostream>
#include <string>

void lua()
{
	// Create a new lua state
	//lua_State *myLuaState = luaL_newstate();

	//// Connect LuaBind to this lua state
	//luabind::open(myLuaState);

	//// Define a lua function that we can call
	//luaL_dostring(
	//	myLuaState,
	//	"function add(first, second)\n"
	//	"  return first + second\n"
	//	"end\n"
	//	);

	//std::cout << "Result: "
	//	<< luabind::call_function<int>(myLuaState, "add", 2, 3)
	//	<< std::endl;

	//lua_close(myLuaState);
}

int main(int argc, char* argv[])
{
	//lua();
	SdlApp sdlApp;
	return sdlApp.OnExecute();
}


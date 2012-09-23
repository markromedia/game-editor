#include "librocket_system.hpp"
#include <sdl2/SDL.h>

float LibRocketSystemInterface::GetElapsedTime()
{
	return SDL_GetTicks();
}


bool LibRocketSystemInterface::LogMessage( Rocket::Core::Log::Type type, const Rocket::Core::String& message )
{
	switch (type)
	{
		case Rocket::Core::Log::LT_ERROR:
		case Rocket::Core::Log::LT_ASSERT:
			LOG_ERROR(message.CString());
			break;
		case Rocket::Core::Log::LT_WARNING:
			LOG_WARNING(message.CString());
			break;
		case Rocket::Core::Log::LT_INFO:
			LOG_INFO(message.CString());
			break;
		case Rocket::Core::Log::LT_DEBUG:
			LOG_DEBUG(message.CString());
			break;

	}

	return true;
}


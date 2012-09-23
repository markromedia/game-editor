#ifndef LIBROCKET_SYSTEMINTERFACE_H
#define LIBROCKET_SYSTEMINTERFACE_H

#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core.h>
#include "../logger.hpp"

class LibRocketSystemInterface : public Rocket::Core::SystemInterface
{
public:
	/// Get the number of seconds elapsed since the start of the application.
	/// @return Elapsed time, in seconds.
	virtual float GetElapsedTime();

	/// Log the specified message.
	/// @param[in] type Type of log message, ERROR, WARNING, etc.
	/// @param[in] message Message to log.
	/// @return True to continue execution, false to break into the debugger.
	virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
};

#endif


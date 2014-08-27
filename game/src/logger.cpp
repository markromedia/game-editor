#include "logger.hpp"

#include <SDL.h>

Logger* Logger::instance = NULL;

Logger::Logger()
{
	preformance_log = false;
}

void Logger::writeToLog( std::string msg, bool lineFeed)
{
	if (lineFeed)
		std::cout << msg << std::endl;
	else
		std::cout << msg;
}

Logger* Logger::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Logger();	
		instance->logLevel = LOGGER_LEVEL_DEBUG;
	}
	return instance;
}

void Logger::SetListenerLogLevel( int level )
{
	this->logLevel = level;
}

void Logger::NoLevel(std::string msg)
{
	if (logLevel >= LOGGER_LEVEL_ERROR) {
		writeToLog(msg, true);
	}
}

void Logger::Debug( std::string msg)
{
	if (logLevel >= LOGGER_LEVEL_DEBUG) {
		writeToLog("DEBUG: ");
		writeToLog(msg, true);		
	}
}

void Logger::Info( std::string msg)
{
	if (logLevel >= LOGGER_LEVEL_INFO) {
		writeToLog("INFO: ");
		writeToLog(msg, true);		
	}
}

void Logger::Warning( std::string msg)
{
	if (logLevel >= LOGGER_LEVEL_WARNING) {
		writeToLog("WARNING: ");
		writeToLog(msg, true);		
	}
}

void Logger::Error( std::string msg)
{
	if (logLevel >= LOGGER_LEVEL_ERROR) {
		writeToLog("ERROR: ");
		writeToLog(msg, true);		
	}
}

///---------------------------------------------------------------------------------------
void Logger::StartLogPreformance()
{
	p_total_time = SDL_GetTicks();
}

void Logger::StopLogPreformance()
{
	p_total_time = SDL_GetTicks() - p_total_time;
	if (1000 / p_total_time < PREF_THRESHOLD)
	{
		WritePreformanceLog();
	}
	pLogElements.clear();
	p_total_time = 0;
}

void Logger::LogPreformance( std::string name )
{
	PLogElement element;
	element.name = name;
	element.start_time = SDL_GetTicks();
	pLogElements.push_back(element);
}

void Logger::StopPreformance( std::string name )
{
	for(std::vector<PLogElement>::iterator it = pLogElements.begin(); it != pLogElements.end(); ++it) 
	{
		if (name == it->name)
		{
			it->stop_time = SDL_GetTicks();
			return;
		}
	}
}

void Logger::WritePreformanceLog()
{
	std::cout << "Frame Stats:" << std::endl << "Total time: " << (p_total_time) << " ms" << std::endl;
	std::cout << "frame rate: " << (1000.0f / p_total_time) << std::endl;

	for(std::vector<PLogElement>::iterator it = pLogElements.begin(); it != pLogElements.end(); ++it) 
	{
		std::cout << it->name << ": " << (it->stop_time - it->start_time) << " ms" << std::endl;
	}
	std::cout << std::endl;
}




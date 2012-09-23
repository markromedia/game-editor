/// Declares simple logging class
#ifndef __LOGGER__hpp
#define __LOGGER__hpp

#define LOGGER_LINEFEED "%s\r\n"
#define LOGGER_LEVEL_NONE 0
#define LOGGER_LEVEL_ERROR 1
#define LOGGER_LEVEL_WARNING 2
#define LOGGER_LEVEL_INFO 3
#define LOGGER_LEVEL_DEBUG 4

#define LOG_ERROR(msg) Logger::GetInstance()->Error(msg)
#define LOG_WARNING(msg) Logger::GetInstance()->Warning(msg)
#define LOG_INFO(msg) Logger::GetInstance()->Info(msg)
#define LOG_DEBUG(msg) Logger::GetInstance()->Debug(msg)

#define PREF_THRESHOLD 50

#include <vector>
#include <string>
#include <iostream>

struct PLogElement 
{
	std::string name;
	float start_time;
	float stop_time;
};

class Logger
{
private:
	Logger();

	int logLevel;

	bool preformance_log;

	static Logger* instance;

	void writeToLog(const char* msg, bool lineFeed = false);

	std::vector<PLogElement> pLogElements;

	float p_total_time;
public:
	static Logger* GetInstance();

	// sets the level above which messages are sent to listener
	// general log level affects this also, setting this above that level
	// will have no effect. 	
	void SetListenerLogLevel(int level);
	
	// different methods for different level of log messages
	void Debug(const char *msg);
	void Info(const char *msg);
	void Warning(const char *msg);
	void Error(const char *msg);

	/// start/stop preformance logging
	void StartLogPreformance();
	void StopLogPreformance();

	//log specific preformance functionality
	void LogPreformance(std::string name);
	void StopPreformance(std::string name);

	//Writes the preformance log out
	void WritePreformanceLog();
};

#endif  // __LOGGER__hpp
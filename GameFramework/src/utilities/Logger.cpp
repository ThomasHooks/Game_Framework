#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>

#include "Logger.h"




Logger::Logger(Level levelIn)
	: _level(levelIn),
	  filePath("./log.txt") {

	message(Level::INFO, "Logging started", Output::TXT_FILE);
}



Logger::Logger(Level levelIn, std::string fileLocation)
	: _level(levelIn),
	  filePath(fileLocation) {

	message(Level::INFO, "Logging started", Output::TXT_FILE);
}



Logger::~Logger() {

	message(Level::INFO, "Logging stopped", Output::TXT_FILE);
	writeToFile("\n\n");
}



/*
 * @param	levelIn What level the message will be displayed
 *
 * @param	message The text to be displayed
 *
 * @param	outputIn The medium the message will be displayed on
 *
 * This method will log a message if its level is at or below the logging level
 */
void Logger::message(Level levelIn, const std::string &message, Output outputIn){

	if(levelIn != Level::NONE && levelIn <= this->_level) {

		/*
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::string timeStamp = ctime(&end_time);
		*/

		std::string logLevel[6] = {"", "[***FATAL***] ", "[**ERROR**] ", "[*WARNING*] ", "[Info] ", "[Trace] "};
		std::time_t const nowTime = std::time(nullptr);
		switch(outputIn) {

		case Output::CONSOLE:
			//std::cout << logLevel[static_cast<int>(levelIn)] << message <<  ": " << timeStamp;
			std::cout << logLevel[static_cast<int>(levelIn)] << message << ": " << std::put_time(std::localtime(&nowTime), "%F %T") << std::endl;
			break;

		case Output::TXT_FILE:
			writeToFile(logLevel[static_cast<int>(levelIn)] + message +  ": ");
			break;

		default:
			break;
		}
	}
}



/*
 * @return	The current logging level for this logger
 *
 * Gets the current logging level for this logger
 */
Logger::Level Logger::getLogLevel() const {
	return this->_level;
}



/*
 * @param	levelIn The new logging level
 *
 * Changes the logging level
 * Only messages that are at or above the logging level will be displayed
 */
void Logger::setLogLevel(Level levelIn){
	this->_level = levelIn;
}



/*
 * @param	filePathIn The new location of the log file
 *
 * Changes the log file's location
 */
void Logger::setFilePath(const std::string &filePathIn){
	this->filePath = filePathIn;
}



/*
 * @param	message The message that will be written to the file
 *
 * Writes a message in the log file set by the user
 * The default log file location is './log.txt'
 */
void Logger::writeToFile(const std::string &message){

	std::ofstream logFile;
	logFile.open(this->filePath, std::ios::out | std::ios::app);
	std::time_t const nowTime = std::time(nullptr);
	if(logFile.is_open()){
		//Was able to open the log file
		//So write the message to the log file
		logFile << message << std::put_time(std::localtime(&nowTime), "%F %T") << std::endl;
		logFile.close();
	}

	else{
		//Unable to open log file: error handle
		//Get system time
		/*
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::string timeStamp = ctime(&end_time);
		*/

		//Log error to Console
		std::cout << "[**ERROR**] " << "Cannot write to log file: '" <<
				this->filePath << "' " << std::put_time(std::localtime(&nowTime), "%F %T") << std::endl;
	}
}








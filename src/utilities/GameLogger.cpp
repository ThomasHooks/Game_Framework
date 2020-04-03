//============================================================================
// Name       		: GameLogger.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/02/2020
//============================================================================




#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "GameLogger.h"




GameLogger::GameLogger(EnumLogLevel levelIn)
	: _level(levelIn),
	  filePath("./log.txt") {

	message(EnumLogLevel::INFO, "Logging started", EnumLogOutput::TXT_FILE);
}



GameLogger::GameLogger(EnumLogLevel levelIn, std::string fileLocation)
	: _level(levelIn),
	  filePath(fileLocation) {

	message(EnumLogLevel::INFO, "Logging started", EnumLogOutput::TXT_FILE);
}



GameLogger::~GameLogger() {

	message(EnumLogLevel::INFO, "Logging stopped", EnumLogOutput::TXT_FILE);
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
void GameLogger::message(EnumLogLevel levelIn, const std::string &message, EnumLogOutput outputIn){

	if(levelIn != EnumLogLevel::NONE && levelIn <= this->_level) {

		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::string timeStamp = ctime(&end_time);
		std::string logLevel[6] = {"", "[***FATAL***] ", "[**ERROR**] ", "[*WARNING*] ", "[Info] ", "[Trace] "};

		switch(outputIn) {

		case EnumLogOutput::CONSOLE:
			std::cout << logLevel[static_cast<int>(levelIn)] << message <<  ": " << timeStamp;
			break;

		case EnumLogOutput::TXT_FILE:
			writeToFile(logLevel[static_cast<int>(levelIn)] + message +  ": " + timeStamp);
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
EnumLogLevel GameLogger::getLogLevel() const {
	return this->_level;
}



/*
 * @param	levelIn The new logging level
 *
 * Changes the logging level
 * Only messages that are at or above the logging level will be displayed
 */
void GameLogger::setLogLevel(enum EnumLogLevel levelIn){
	this->_level = levelIn;
}



/*
 * @param	filePathIn The new location of the log file
 *
 * Changes the log file's location
 */
void GameLogger::setFilePath(const std::string &filePathIn){
	this->filePath = filePathIn;
}



/*
 * @param	message The message that will be written to the file
 *
 * Writes a message in the log file set by the user
 * The default log file location is './log.txt'
 */
void GameLogger::writeToFile(const std::string &message){

	std::ofstream logFile;
	logFile.open(this->filePath, std::ios::out | std::ios::app);

	if(logFile.is_open()){
		//Was able to open the log file
		//So write the message to the log file
		logFile << message;
		logFile.close();
	}

	else{
		//Unable to open log file: error handle
		//Get system time
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::string timeStamp = ctime(&end_time);

		//Log error to Console
		std::cout << "[**ERROR**] " << "Cannot write to log file: '" <<
				this->filePath << "' " << timeStamp;
	}
}








//============================================================================
// Name       		: GameLogger.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/01/2020
//============================================================================




#include "GameLogger.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>




GameLogger::GameLogger(Level levelIn)
	: _level(levelIn), filePath("./log.txt"){
	//Set default log file location to the applications relative directory
	message(Level::INFO, "Logging started", Output::TXT_FILE);
}



GameLogger::GameLogger(Level levelIn, std::string fileLocation)
	: _level(levelIn), filePath(fileLocation){
	message(Level::INFO, "Logging started", Output::TXT_FILE);
}



GameLogger::~GameLogger() {
	//Nothing to free from the heap

	message(Level::INFO, "Logging stopped", Output::TXT_FILE);
	writeToFile("\n\n");
}



void GameLogger::message(Level levelIn, const std::string &message, Output out){
	/*
	 *	This method will log a message if its level is
	 *	at or below the logging level
	 *
	 * @param	level		What level the message will be displayed
	 *
	 * @param	message		The text to be displayed
	 *
	 * @param	out			The medium the message will be displayed on
	 */




	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::string timeStamp = ctime(&end_time);

	switch (levelIn){

	case Level::NONE:
		//None is not used to display messages
		break;



	case Level::FATAL:
		if (out == Output::CONSOLE && _level >= Level::FATAL){
			//Output to console
			std::cout << "[***FATAL***] " << message <<  ": " << timeStamp;
		}

		else if(out == Output::TXT_FILE && _level >= Level::FATAL){
			//Output to .txt file
			writeToFile("[***FATAL***] " + message +  ": " + timeStamp);
		}
		break;



	case Level::ERROR:
		if (out == Output::CONSOLE && _level >= Level::ERROR){
			//Output to console
			std::cout << "[**ERROR**] " << message <<  ": " << timeStamp;
		}

		else if(out == Output::TXT_FILE && _level >= Level::ERROR){
			//Output to .txt file
			writeToFile("[**ERROR**] " + message +  ": " + timeStamp);
		}
		break;



	case Level::WARNING:
		if (out == Output::CONSOLE && _level >= Level::WARNING){
			//Output to console
			std::cout << "[*WARNING*] " << message << ": " << timeStamp;
		}

		else if(out == Output::TXT_FILE && _level >= Level::WARNING){
			//Output to .txt file
			writeToFile("[*WARNING*] " + message +  ": " + timeStamp);
		}
		break;



	case Level::INFO:
		if (out == Output::CONSOLE && _level >= Level::INFO){
			//Output to console
			std::cout << "[Info] " << message << ": " << timeStamp;
		}

		else if(out == Output::TXT_FILE && _level >= Level::INFO){
			//Output to .txt file
			writeToFile("[Info] " + message +  ": " + timeStamp);
		}
		break;



	case Level::TRACE:
		if (out == Output::CONSOLE && _level >= Level::TRACE){
			//Output to console
			std::cout << "[Trace] " << message <<  ": " << timeStamp;
		}

		else if(out == Output::TXT_FILE && _level >= Level::TRACE){
			//Output to .txt file
			writeToFile("[Trace] " + message +  ": " + timeStamp);
		}
		break;
	}

	return;
}



Level GameLogger::getLogLevel(void) const {
	return this->_level;
}



void GameLogger::setLogLevel(enum Level levelIn){
	this->_level = levelIn;
}



void GameLogger::setFilePath(const std::string &filePathIn){
	this->filePath = filePathIn;
}



void GameLogger::writeToFile(const std::string &message){
	/*
	 * Writes a message in the log file set by the user
	 *
	 * @param	message		the message that will be written to the file
	 *
	 * This method logs a message provided by the caller to the log file set
	 * by method set_filePath(std::string path). The default log file
	 * location is './log.txt' unless it is changed by set_filePath() method.
	 */




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

	return;
}








//============================================================================
// Name       		: GameLogger.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/24/2020
//============================================================================




#include "GameLogger.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>




GameLogger::GameLogger()
	: e_level(Level::Info), filePath("./log.txt"){
	//Set default logging level to info
	//Set default log file location to the applications relative directory
	Message(Level::Info, "Logging started", Output::File_txt);
}



GameLogger::GameLogger(Level level)
	: e_level(level), filePath("./log.txt"){
	//Set default log file location to the applications relative directory
	Message(Level::Info, "Logging started", Output::File_txt);
}



GameLogger::GameLogger(Level level, std::string fileLocation)
	: e_level(level), filePath(fileLocation){
	Message(Level::Info, "Logging started", Output::File_txt);
}



GameLogger::~GameLogger() {
	//Nothing to free from the heap

	Message(Level::Info, "Logging stopped", Output::File_txt);
	WriteToFile("\n\n");
}

//----------------------------------------------------------------------------

void GameLogger::Message(Level level,
		const std::string &message, Output out){
	/*
	 *	brief				This method will log a message if its level is
	 *						at or below the logging level
	 *
	 *
	 *	param	level		What level the message will be displayed
	 *
	 *	param	message		The text to be displayed
	 *
	 *	param	out			The medium the message will be displayed on
	 */




	//Get system time
	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::string timeStamp = ctime(&end_time);

	switch (level){

	case Level::None:
		//None is not used to display messages
		break;




	case Level::Fatal:
		if (out == Output::Console && e_level >= Level::Fatal){
			//Output to console
			std::cout << "[***FATAL***] " << message <<  ": " << timeStamp;
		}

		else if(out == Output::File_txt && e_level >= Level::Fatal){
			//Output to .txt file
			WriteToFile("[***FATAL***] " + message +  ": " + timeStamp);
		}
		break;




	case Level::Error:
		if (out == Output::Console && e_level >= Level::Error){
			//Output to console
			std::cout << "[**ERROR**] " << message <<  ": " << timeStamp;
		}

		else if(out == Output::File_txt && e_level >= Level::Error){
			//Output to .txt file
			WriteToFile("[**ERROR**] " + message +  ": " + timeStamp);
		}
		break;




	case Level::Warning:
		if (out == Output::Console && e_level >= Level::Warning){
			//Output to console
			std::cout << "[*WARNING*] " << message << ": " << timeStamp;
		}

		else if(out == Output::File_txt && e_level >= Level::Warning){
			//Output to .txt file
			WriteToFile("[*WARNING*] " + message +  ": " + timeStamp);
		}
		break;




	case Level::Info:
		if (out == Output::Console && e_level >= Level::Info){
			//Output to console
			std::cout << "[Info] " << message << ": " << timeStamp;
		}

		else if(out == Output::File_txt && e_level >= Level::Info){
			//Output to .txt file
			WriteToFile("[Info] " + message +  ": " + timeStamp);
		}
		break;




	case Level::Trace:
		if (out == Output::Console && e_level >= Level::Trace){
			//Output to console
			std::cout << "[Trace] " << message <<  ": " << timeStamp;
		}

		else if(out == Output::File_txt && e_level >= Level::Trace){
			//Output to .txt file
			WriteToFile("[Trace] " + message +  ": " + timeStamp);
		}
		break;
	}

	return;
}

//----------------------------------------------------------------------------

void GameLogger::WriteToFile(const std::string &message){
	/*
	 * brief				Writes a message in the log file set by the user
	 *
	 * param	message		the message that will be written to the file
	 *
	 * This method logs a message provided by the caller to the log file set
	 * by method set_filePath(std::string path). The default log file
	 * location is './log.txt' unless it is changed by set_filePath() method.
	 */




	std::ofstream logFile;
	logFile.open(get_filePath(), std::ios::out | std::ios::app);

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
				get_filePath() << "' " << timeStamp;
	}

	return;
}








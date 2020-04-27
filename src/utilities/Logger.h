//============================================================================
// Name       		: Logger
// Author     		: Thomas Hooks
// Last Modified	: 04/20/2020
//============================================================================




#ifndef LOGGER_H_
#define LOGGER_H_


#include <string>




class Logger {

public:

	enum struct Level : unsigned char {

		NONE = 0,	//Nothing will be logged

		FATAL,		//Issues that cause the application to abort

		ERROR,		//Issues that interfere with application operation

		WARNING,	//Unusual application operation

		INFO,		//Routine application operation

		TRACE		//Information to perform diagnostics
	};



	enum struct Output : unsigned char {

		CONSOLE = 0,	//Outputs to the console window

		TXT_FILE		//Outputs to the log.txt file
	};



	Logger(Level levelIn);



	Logger(Level levelIn, std::string fileLocation);



	~Logger();



	Logger(const Logger &other) = delete;



	Logger(Logger &&other) = delete;



	/*
	 * @param	levelIn What level the message will be displayed
	 *
	 * @param	message The text to be displayed
	 *
	 * @param	outputIn The medium the message will be displayed on
	 *
	 * This method will log a message if its level is at or below the logging level
	 */
	void message(Level levelIn, const std::string &message, Output outputIn);



	/*
	 * @return	The current logging level for this logger
	 *
	 * Gets the current logging level for this logger
	 */
	Level getLogLevel() const;



	/*
	 * @param	levelIn The new logging level
	 *
	 * Changes the logging level
	 * Only messages that are at or above the logging level will be displayed
	 */
	void setLogLevel(Level levelIn);



	/*
	 * @param	filePathIn The new location of the log file
	 *
	 * Changes the log file's location
	 */
	void setFilePath(const std::string &filePathIn);



private:

	Level _level;

	std::string filePath;



	/*
	 * @param	message The message that will be written to the file
	 *
	 * Writes a message in the log file set by the user
	 * The default log file location is './log.txt'
	 */
	void writeToFile(const std::string &message);
};


#endif /* LOGGER_H_ */




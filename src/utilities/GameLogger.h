//============================================================================
// Name       		: GameLogger.h
// Author     		: Thomas Hooks
// Last Modified	: 04/02/2020
//============================================================================




#ifndef SRC_GAME_LOGGER_H_
#define SRC_GAME_LOGGER_H_


#include <iostream>
#include <memory>

#include "EnumLogLevel.h"
#include "EnumLogOutput.h"


class GameLogger {

public:

	GameLogger(EnumLogLevel levelIn);



	GameLogger(EnumLogLevel levelIn, std::string fileLocation);



	~GameLogger();



	GameLogger(const GameLogger &other) = delete;



	GameLogger(GameLogger &&other) = delete;



	/*
	 * @param	levelIn What level the message will be displayed
	 *
	 * @param	message The text to be displayed
	 *
	 * @param	outputIn The medium the message will be displayed on
	 *
	 * This method will log a message if its level is at or below the logging level
	 */
	void message(EnumLogLevel levelIn, const std::string &message, EnumLogOutput outputIn);



	/*
	 * @return	The current logging level for this logger
	 *
	 * Gets the current logging level for this logger
	 */
	EnumLogLevel getLogLevel() const;



	/*
	 * @param	levelIn The new logging level
	 *
	 * Changes the logging level
	 * Only messages that are at or above the logging level will be displayed
	 */
	void setLogLevel(EnumLogLevel levelIn);



	/*
	 * @param	filePathIn The new location of the log file
	 *
	 * Changes the log file's location
	 */
	void setFilePath(const std::string &filePathIn);



private:

	EnumLogLevel _level;

	std::string filePath;



	/*
	 * @param	message The message that will be written to the file
	 *
	 * Writes a message in the log file set by the user
	 * The default log file location is './log.txt'
	 */
	void writeToFile(const std::string &message);
};


#endif /* SRC_GAME_LOGGER_H_ */




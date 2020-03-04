//============================================================================
// Name       		: GameLogger.h
// Author     		: Thomas Hooks
// Last Modified	: 03/01/2020
//============================================================================




#ifndef SRC_GAME_LOGGER_H_
#define SRC_GAME_LOGGER_H_




#include <iostream>
#include <memory>




enum struct Level : unsigned char{
	//This enumeration encapsulates the logging level

	NONE = 0,	//Nothing will be logged

	FATAL,		//Issues that cause the application to abort

	ERROR,		//Issues that interfere with application operation

	WARNING,	//Unusual application operation

	INFO,		//Routine application operation

	TRACE		//Information to perform diagnostics
};



enum struct Output : unsigned char{
	//This enumeration encapsulates the log output type

	CONSOLE = 0,
	TXT_FILE
};

//TODO make GameLogger a singleton

class GameLogger {

public:

	GameLogger(Level levelIn);
	GameLogger(Level levelIn, std::string fileLocation);

	~GameLogger();

	GameLogger(const GameLogger &other) = delete;
	GameLogger(GameLogger &&other) = delete;

	void message(Level levelIn, const std::string &message, Output out);

	Level getLogLevel(void) const;
	void setLogLevel(Level levelIn);

	void setFilePath(const std::string &filePathIn);

private:

	Level _level;

	std::string filePath;

	void writeToFile(const std::string &message);
};


#endif /* SRC_GAME_LOGGER_H_ */




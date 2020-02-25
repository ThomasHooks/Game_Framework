//============================================================================
// Name       		: GameLogger.h
// Author     		: Thomas Hooks
// Last Modified	: 02/24/2020
//============================================================================




#ifndef SRC_GAME_LOGGER_H_
#define SRC_GAME_LOGGER_H_




#include <iostream>




enum struct Level : unsigned char{
	//This enumeration encapsulates the logging level

	None = 0,	//Nothing will be logged

	Fatal,		//Issues that cause the application to abort

	Error,		//Issues that interfere with application operation

	Warning,	//Unusual application operation

	Info,		//Routine application operation

	Trace		//Information to perform diagnostics
};



enum struct Output : unsigned char{
	//This enumeration encapsulates the log output type

	Console = 0,
	File_txt
};

//----------------------------------------------------------------------------

class GameLogger {

public:

	GameLogger();

	GameLogger(Level level);

	GameLogger(Level level, std::string fileLocation);

	~GameLogger();

	GameLogger(const GameLogger &other) = delete;

	GameLogger(GameLogger &&other) = delete;


	void Message(Level level, const std::string &message, Output out);


	Level get_logLevel(void) const {return e_level;}

	void set_logLevel(Level level) {e_level = level;}


	std::string get_filePath(void) const {return filePath;}

	void set_filePath(std::string path) {filePath = path;}


private:

	Level e_level;

	std::string filePath;

	void WriteToFile(const std::string &message);
};




#endif /* SRC_GAME_LOGGER_H_ */


//============================================================================








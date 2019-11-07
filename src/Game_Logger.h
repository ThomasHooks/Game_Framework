//============================================================================
// Name       		: Game_Logger.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
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

class Game_Logger {

public:

	Game_Logger();

	Game_Logger(Level level);

	Game_Logger(Level level, std::string fileLocation);

	~Game_Logger();

	Game_Logger(const Game_Logger &other) = delete;

	Game_Logger(Game_Logger &&other) = delete;


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








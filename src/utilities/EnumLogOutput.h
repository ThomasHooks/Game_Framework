//============================================================================
// Name       		: EnumLogOutput.h
// Author     		: Thomas Hooks
// Last Modified	: Apr 2, 2020
//============================================================================




#ifndef ENUMLOGOUTPUT_H_
#define ENUMLOGOUTPUT_H_




//This enumeration encapsulates the log output type
enum struct EnumLogOutput : unsigned char {

	CONSOLE = 0,	//Outputs to the console window

	TXT_FILE		//Outputs to the log.txt file
};


#endif /* ENUMLOGOUTPUT_H_ */

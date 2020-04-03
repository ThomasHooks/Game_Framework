//============================================================================
// Name       		: EnumLogLevel.h
// Author     		: Thomas Hooks
// Last Modified	: Apr 2, 2020
//============================================================================




#ifndef ENUMLOGLEVEL_H_
#define ENUMLOGLEVEL_H_




//This enumeration encapsulates the logging level
enum struct EnumLogLevel : unsigned char {

	NONE = 0,	//Nothing will be logged

	FATAL,		//Issues that cause the application to abort

	ERROR,		//Issues that interfere with application operation

	WARNING,	//Unusual application operation

	INFO,		//Routine application operation

	TRACE		//Information to perform diagnostics
};


#endif /* ENUMLOGLEVEL_H_ */




//============================================================================
// Name       		: EnumBehavior.h
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#ifndef ENUMBEHAVIOR_H_
#define ENUMBEHAVIOR_H_


//This enumeration encapsulates how an entity reacts to the player(s)
enum struct EnumBehavior : unsigned char {

	PASSIVE = 0,
	NEUTRAL,
	AGGRESSIVE
};


#endif /* ENUMBEHAVIOR_H_ */



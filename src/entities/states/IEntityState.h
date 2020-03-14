//============================================================================
// Name       		: IEntityState.h
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#ifndef STATES_IENTITYSTATE_H_
#define STATES_IENTITYSTATE_H_


#include <string>


class IEntityState {

public:

	IEntityState(const std::string &tagIn);



	virtual ~IEntityState() {}



	//Used to update this state
	virtual void process() = 0;



	/*
	 * @return	A String of EntityState's tag
	 *
	 * Gets the EntityState's tag
	 */
	const std::string& getTag();



protected:

	//Used to register the EntityState's tag
	void setTag(const std::string &tagIn);



private:

	std::string tag;
};


#endif /* STATES_IENTITYSTATE_H_ */




//============================================================================
// Name       		: IEntityCapability.h
// Author     		: Thomas Hooks
// Last Modified	: 03/16/2020
//============================================================================




#ifndef CAPABILITIES_IENTITYCAPABILITY_H_
#define CAPABILITIES_IENTITYCAPABILITY_H_


#include <string>


class IEntityCapability {

public:

	IEntityCapability() {}



	virtual ~IEntityCapability() {}



	//Called to update this state
	virtual void process(class IEntity &context) = 0;
};


#endif /* CAPABILITIES_IENTITYCAPABILITY_H_ */




//============================================================================
// Name       		: IEntityState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#include "IEntityState.h"




IEntityState::IEntityState(const std::string &tagIn)
	: tag(tagIn) {}



const std::string& IEntityState::getTag() {
	return this->tag;
}



void IEntityState::setTag(const std::string &tagIn){
	this->tag = tagIn;
}








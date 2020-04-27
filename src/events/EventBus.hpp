//============================================================================
// Name       		: EventBus
// Author     		: Thomas Hooks
// Last Modified	: Apr 19, 2020
//============================================================================




#ifndef EVENTS_EVENTBUS_HPP_
#define EVENTS_EVENTBUS_HPP_


#include <vector>

#include "../utilities/Logger.h"
#include "EventDispatcher.hpp"




class EventBus {

	template<class EventType>
	using Callback = std::function<void(const EventType&)>;

public:

	EventBus(Logger *logger)
		: logger(logger) {}



	~EventBus() {}



	template<class EventType>
	int subscribe(Callback<EventType> listener) {

		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size()) this->handlers.push_back(std::make_unique<EventDispatcher>(logger));

		int listernerID = this->handlers[handlerID]->subscribe<EventType>(listener);
		return listernerID;
	}



	template<class EventType>
	void unsubscribe(int listenerID) {

		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size()) this->handlers.push_back(std::make_unique<EventDispatcher>(logger));

		this->handlers[handlerID]->unsubscribe(listenerID);
	}



	template<class EventType, typename... TArgs>
	void publish(TArgs... mArgs) {
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size()) this->handlers.push_back(std::make_unique<EventDispatcher>(logger));

		this->handlers[handlerID]->publish<EventType>((mArgs)...);
	}



	template<class EventType>
	void dispatch() {

		//The template is only here to ensure that the specified EventDispatcher actually exists
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size()) this->handlers.push_back(std::make_unique<EventDispatcher>(logger));

		this->handlers[handlerID]->dispatchAllEvents();
	}



	void dispatchAllEvents() {

		for (auto& itr : this->handlers) {
			itr->dispatchAllEvents();
		}
	}



protected:

	std::vector<std::unique_ptr<EventDispatcher>> handlers;

	Logger *logger;
};


#endif /* EVENTS_EVENTBUS_HPP_ */




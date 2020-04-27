//============================================================================
// Name       		: EventDispatcher
// Author     		: Thomas Hooks
// Last Modified	: Apr 20, 2020
//============================================================================




#ifndef EVENTS_EVENTDISPATCHER_HPP_
#define EVENTS_EVENTDISPATCHER_HPP_


#include <functional>
#include <memory>
#include <map>
#include <queue>

#include "../utilities/Logger.h"
#include "IEvent.hpp"




//TODO: add automatic unsubscribing
class EventDispatcher {

	const uint32_t MAX_LISTENER_ID = 4294967294;

	template<class EventType>
	using Callback = std::function<void(const EventType&)>;

	struct CallbackWrapperBase;

	template<class EventType>
	struct CallbackWrapper;

public:

	EventDispatcher(Logger *logger)
		: nextListernerID(0),
		  logger(logger) {}



	virtual ~EventDispatcher() {}



	template<class EventType>
	unsigned int subscribe(Callback<EventType> listener) {

		if (this->nextListernerID == MAX_LISTENER_ID) this->nextListernerID = 0;
		this->listeners.insert({ this->nextListernerID, std::make_unique<CallbackWrapper<EventType>>(listener) });
		return this->nextListernerID++;
	}



	void unsubscribe(unsigned int listenerID) {
		this->listeners.erase(listenerID);
	}



	template<class EventType, typename... TArgs>
	void publish(TArgs... mArgs) {
		this->events.push(std::make_unique<EventType>((mArgs)...));
	}



	void dispatchAllEvents() {

		while (!this->events.empty()) {
			for (auto iter = this->listeners.begin(); iter != this->listeners.end(); /* Incrementing is handled in the loop */) {
				//
				if (!iter->second->isValid()) {
					//Erasing the invalid callback invalidates the iterator which is why incrementing is handled in the loop
					iter = this->listeners.erase(iter);
					//Log a warning as listeners should unsubscribe before going out of scope
				}
				else {
					iter->second->call(*this->events.front().get());
					iter++;
				}
			}
			this->events.pop();
		}
	}



protected:

	std::map<int, std::unique_ptr<CallbackWrapperBase>> listeners;

	std::queue<std::unique_ptr<BaseEvent>> events;

	unsigned int nextListernerID;

	Logger *logger;



private:

	//These nested structs are for casting the argument
	//of the listener's callback, back to the correct Event type
	struct CallbackWrapperBase {

		virtual ~CallbackWrapperBase() {}

		virtual void call(const BaseEvent& event) = 0;

		virtual bool isValid() = 0;
	};



	template<class EventType>
	struct CallbackWrapper : CallbackWrapperBase {

		CallbackWrapper(Callback<EventType> callable)
		: callable(callable) {}

		void call(const BaseEvent& event) override {
			this->callable(static_cast<const EventType&>(event));
		}

		virtual bool isValid() {
			return this->callable != nullptr;
		}

	protected:

		Callback<EventType> callable;
	};
};


#endif /* EVENTS_EVENTDISPATCHER_HPP_ */




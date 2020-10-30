#ifndef EVENTS_EVENTBUS_HPP_
#define EVENTS_EVENTBUS_HPP_


#include <vector>

#include "EventDispatcher.hpp"




class EventBus
{
	template<class EventType>
	using Callback = std::function<void(const EventType&)>;

public:

	~EventBus() = default;



	EventBus(const EventBus& other) = delete;



	void operator=(const EventBus& other) = delete;



	/*
	 * Subscribes a listener's callback function to this event type
	 *
	 * @param	EventType	Specifies the event type
	 * @param	listener	Callback function of the listener
	 *
	 * @return	The listener's subscription ID
	 */
	template<class EventType>
	static int subscribe(Callback<EventType> listener)
	{
		return getInstance().subscribe_impl(listener);
	}



	/*
	 * Unsubscribes the given listener from all future events
	 *
	 * @param	EventType	Specifies the event type
	 * @param	listenerID	Specifies the listerner to be unsubscribed
	 */
	template<class EventType>
	static void unsubscribe(int listenerID)
	{
		getInstance().unsubscribe_impl<EventType>(listenerID);
	}



	/*
	 * Queues an event that will be dispatched later
	 *
	 * @param	EventType	Specifies the event type
	 * @param	mArgs		Constructor arguments for this event type
	 */
	template<class EventType, typename... TArgs>
	static void publish(TArgs... mArgs)
	{
		getInstance().publish_impl<EventType>((mArgs)...);
	}



	/*
	 * Dispatches all events for the given event type
	 *
	 * @param	EventType	Specifies the event type
	 */
	template<class EventType>
	static void dispatch()
	{
		getInstance().dispatch_impl<EventType>();
	}



	/*
	 * Dispatches all queued events for all registered event types
	 */
	static void dispatchAllEvents();



private:

	EventBus() = default;



	static EventBus& getInstance();



	template<class EventType>
	int subscribe_impl(Callback<EventType> listener)
	{
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size())
			this->handlers.push_back(std::make_unique<EventDispatcher>());

		int listernerID = this->handlers[handlerID]->subscribe<EventType>(listener);
		return listernerID;
	}



	template<class EventType>
	void unsubscribe_impl(int listenerID)
	{
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size())
			this->handlers.push_back(std::make_unique<EventDispatcher>());

		this->handlers[handlerID]->unsubscribe(listenerID);
	}



	template<class EventType, typename... TArgs>
	void publish_impl(TArgs... mArgs)
	{
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size())
			this->handlers.push_back(std::make_unique<EventDispatcher>());

		this->handlers[handlerID]->publish<EventType>((mArgs)...);
	}



	template<class EventType>
	void dispatch_impl()
	{
		//The template is only here to ensure that the specified EventDispatcher actually exists
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= this->handlers.size())
			this->handlers.push_back(std::make_unique<EventDispatcher>());

		this->handlers[handlerID]->dispatchAllEvents();
	}



	void dispatchAllEvents_impl();



	std::vector<std::unique_ptr<EventDispatcher>> handlers;
};


#endif /* EVENTS_EVENTBUS_HPP_ */




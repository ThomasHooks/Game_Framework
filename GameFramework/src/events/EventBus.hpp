#ifndef EVENTS_EVENTBUS_HPP_
#define EVENTS_EVENTBUS_HPP_


#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <memory>

#include "IEvent.hpp"




class EventBus
{
	class Dispatcher
	{
		const uint32_t MAX_LISTENER_ID = 4294967294;

		template<class EventType>
		using Callback = std::function<void(const EventType&)>;



		/*
		 * These nested structs are for casting the argument
		 * of the listener's callback back to the correct Event type
		 */

		struct CallbackWrapperBase
		{
			virtual ~CallbackWrapperBase()
			{}

			virtual void call(const BaseEvent& event) = 0;

			virtual bool isValid() = 0;
		};



		template<class EventType>
		struct CallbackWrapper : CallbackWrapperBase
		{
			CallbackWrapper(Callback<EventType> callableIn)
				: m_callable(callableIn)
			{}

			void call(const BaseEvent& event) override
			{
				m_callable(static_cast<const EventType&>(event));
			}

			virtual bool isValid()
			{
				return m_callable != nullptr;
			}

		protected:

			Callback<EventType> m_callable;
		};



	public:

		Dispatcher() 
			: m_nextListernerID(0) 
		{}



		virtual ~Dispatcher() = default;



		/// <summary>
		/// Subscribes a listener's callback function to this event dispatcher
		/// </summary>
		/// <typeparam name="EventType">Specifies the event type</typeparam>
		/// <param name="listener">Callback function of the listener</param>
		/// <returns>The listener's subscription ID</returns>
		template<class EventType>
		unsigned int subscribe(Callback<EventType> listener)
		{
			if (m_nextListernerID == MAX_LISTENER_ID)
				m_nextListernerID = 0;

			m_listeners.insert({ m_nextListernerID, std::make_unique<CallbackWrapper<EventType>>(listener) });
			return m_nextListernerID++;
		}



		/// <summary>
		/// Unsubscribes the given listener from all future events from this dispatcher
		/// </summary>
		/// <param name="listenerID">Specifies the listerner to be unsubscribed</param>
		void unsubscribe(unsigned int listenerID)
		{
			m_listeners.erase(listenerID);
		}



		/// <summary>
		/// Queues an event that will be dispatched later
		/// </summary>
		/// <typeparam name="EventType">Specifies the event type</typeparam>
		/// <typeparam name="...TArgs"></typeparam>
		/// <param name="...mArgs">Constructor arguments for this event type</param>
		template<class EventType, typename... TArgs>
		void publish(TArgs... mArgs)
		{
			m_events.push(std::make_unique<EventType>((mArgs)...));
		}



		/// <summary>
		/// Dispatches all queued events in this dispatcher
		/// </summary>
		void dispatchAllEvents()
		{
			while (!m_events.empty())
			{
				for (auto iter = m_listeners.begin(); iter != m_listeners.end(); /* Incrementing is handled in the loop */)
				{
					if (!iter->second->isValid())
						//Erasing the invalid callback invalidates the iterator which is why incrementing is handled here
						iter = m_listeners.erase(iter);
					else
					{
						iter->second->call(*m_events.front().get());
						iter++;
					}
				}
				m_events.pop();
			}
		}



	protected:

		std::map<int, std::unique_ptr<CallbackWrapperBase>> m_listeners;

		std::queue<std::unique_ptr<BaseEvent>> m_events;

		unsigned int m_nextListernerID;
	};



	template<class EventType>
	using Callback = std::function<void(const EventType&)>;



public:

	~EventBus() = default;



	EventBus(const EventBus& other) = delete;



	void operator=(const EventBus& other) = delete;



	/// <summary>
	/// Subscribes a listener's callback function to this event type
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	/// <param name="listener">Callback function of the listener</param>
	/// <returns>The listener's subscription ID</returns>
	template<class EventType>
	static int subscribe(Callback<EventType> listener)
	{
		return getInstance().subscribe_impl(listener);
	}



	/// <summary>
	/// Unsubscribes the given listener from all future events of this type
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	/// <param name="listenerID">Specifies the listerner to be unsubscribed</param>
	template<class EventType>
	static void unsubscribe(int listenerID)
	{
		getInstance().unsubscribe_impl<EventType>(listenerID);
	}



	/// <summary>
	/// Queues an event that will be dispatched later
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	/// <typeparam name="...TArgs"></typeparam>
	/// <param name="...mArgs">Constructor arguments for this event type</param>
	template<class EventType, typename... TArgs>
	static void publish(TArgs... mArgs)
	{
		getInstance().publish_impl<EventType>((mArgs)...);
	}



	/// <summary>
	/// Dispatches all events for the given event type
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	template<class EventType>
	static void dispatch()
	{
		getInstance().dispatch_impl<EventType>();
	}



	/// <summary>
	/// Dispatches all queued events for all registered event types
	/// </summary>
	static void dispatchAllEvents();



private:

	EventBus() = default;



	static EventBus& getInstance();



	/// <summary>
	/// <para>Implementation</para>
	/// Subscribes a listener's callback function to this event type
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	/// <param name="listener">Callback function of the listener</param>
	/// <returns>The listener's subscription ID</returns>
	template<class EventType>
	int subscribe_impl(Callback<EventType> listener)
	{
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= m_handlers.size())
			m_handlers.push_back(std::make_unique<Dispatcher>());

		int listernerID = m_handlers[handlerID]->subscribe<EventType>(listener);
		return listernerID;
	}



	/// <summary>
	/// <para>Implementation</para>
	/// Unsubscribes the given listener from all future events of this type
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	/// <param name="listenerID">Specifies the listerner to be unsubscribed</param>
	template<class EventType>
	void unsubscribe_impl(int listenerID)
	{
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= m_handlers.size())
			m_handlers.push_back(std::make_unique<Dispatcher>());

		m_handlers[handlerID]->unsubscribe(listenerID);
	}



	/// <summary>
	/// <para>Implementation</para>
	/// Queues an event that will be dispatched later
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	/// <typeparam name="...TArgs"></typeparam>
	/// <param name="...mArgs">Constructor arguments for this event type</param>
	template<class EventType, typename... TArgs>
	void publish_impl(TArgs... mArgs)
	{
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= m_handlers.size())
			m_handlers.push_back(std::make_unique<Dispatcher>());

		m_handlers[handlerID]->publish<EventType>((mArgs)...);
	}



	/// <summary>
	/// <para>Implementation</para>
	/// Dispatches all events for the given event type
	/// </summary>
	/// <typeparam name="EventType">Specifies the event type</typeparam>
	template<class EventType>
	void dispatch_impl()
	{
		//The template is only here to ensure that the specified Dispatcher actually exists
		EventID handlerID = IEvent<EventType>::type();
		if (handlerID >= m_handlers.size())
			m_handlers.push_back(std::make_unique<Dispatcher>());

		m_handlers[handlerID]->dispatchAllEvents();
	}



	/// <summary>
	/// <para>Implementation</para>
	/// Dispatches all queued events for all registered event types
	/// </summary>
	void dispatchAllEvents_impl();



	std::vector<std::unique_ptr<Dispatcher>> m_handlers;
};


#endif /* EVENTS_EVENTBUS_HPP_ */




#include "EventBus.hpp"




 EventBus& EventBus::getInstance()
 {
	 static EventBus s_instance;
	 return s_instance;
 }



 /*
  * Dispatches all queued events for all registered event types
  */
void EventBus::dispatchAllEvents()
{
	getInstance().dispatchAllEvents_impl();
}



void EventBus::dispatchAllEvents_impl()
{
	for (auto& itr : this->handlers)
		itr->dispatchAllEvents();
}




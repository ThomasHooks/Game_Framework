#include "EventBus.hpp"




 EventBus& EventBus::getInstance()
 {
	 static EventBus s_instance;
	 return s_instance;
 }



void EventBus::dispatchAllEvents()
{
	getInstance().dispatchAllEvents_impl();
}



void EventBus::dispatchAllEvents_impl()
{
	for (auto& itr : m_handlers)
		itr->dispatchAllEvents();
}




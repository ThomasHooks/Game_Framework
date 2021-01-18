#ifndef EVENTS_IEVENT_HPP_
#define EVENTS_IEVENT_HPP_




typedef unsigned long long EventID;

class BaseEvent 
{
public:

	virtual ~BaseEvent() {}



protected:

	static EventID getNextType() 
	{
		static EventID nextType = 0;
		return nextType++;
	}
};



template<class EventType>
class IEvent : public BaseEvent 
{
public:

	static EventID type() {
		static EventID typeID = BaseEvent::getNextType();
		return typeID;
	}
};


#endif




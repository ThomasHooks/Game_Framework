#ifndef ICAPABILITY_HPP_
#define ICAPABILITY_HPP_


#include <string>




class CapabilityBase
{
public:

	virtual ~CapabilityBase() {}



protected:

	using CapabilityID = uint32_t;



	CapabilityBase() {}



	static CapabilityID getNextID()
	{
		static CapabilityID nextType = 0;
		return nextType++;
	}



	/// <summary>
	/// 
	/// </summary>
	virtual void read() {}



	/// <summary>
	/// 
	/// </summary>
	virtual void write() {}
};



template<class CapabilityType>
class ICapability : public CapabilityBase
{
public:

	virtual ~ICapability() {}



	/// <summary>
	/// Gets the specified Capability's unique identifier
	/// </summary>
	/// <returns></returns>
	static CapabilityID id()
	{
		static CapabilityID typeID = CapabilityBase::getNextID();
		return typeID;
	}



protected:

	ICapability() {}
};


#endif /* ICAPABILITY_HPP_ */




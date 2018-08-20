#ifndef _I_AGENT_H_
#define _I_AGENT_H_

#include "event.h"

#include <string>
#include <tr1/memory>


class IAgent
{
public:
typedef std::tr1::shared_ptr<Event> EventSharedPtr; 
	virtual ~IAgent(){;}
	
	virtual void TransferEvent(EventSharedPtr _event) = 0; 
	virtual const std::string& GetType()const = 0;
	virtual void SendEvents() = 0;

protected:
	virtual EventSharedPtr EventCreate(std::string _type) = 0; 


};





#endif //_I_AGENT_H_

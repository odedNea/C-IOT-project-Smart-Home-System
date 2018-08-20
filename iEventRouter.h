#ifndef _I_EVENT_ROUTER_H_
#define _I_EVENT_ROUTER_H_

#include "event.h"

#include <tr1/memory>

typedef std::tr1::shared_ptr<Event> EventSharedPtr; 

class IEventRouter
{
public:
	virtual ~IEventRouter(){;};
	
	virtual int Publish(EventSharedPtr _event) = 0;

};












#endif //_I_EVENT_ROUTER_H_

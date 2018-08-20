#ifndef _EVENT_ROUTER_H_
#define _EVENT_ROUTER_H_

#include "iEventRouter.h"
#include "event.h"
#include "waitableQueue.h"

#include <queue>
#include <tr1/memory>


class EventRouter : public IEventRouter
{
public: 
	typedef std::tr1::shared_ptr<Event> EventSharedPtr; 
	EventRouter(WaitableQueue<EventSharedPtr>& _eventsQueue);
	virtual ~EventRouter(){;}
	virtual int Publish(EventSharedPtr _event);
	
private:
	WaitableQueue<EventSharedPtr>& m_eventsQueue;

};










#endif //_EVENT_ROUTER_H_

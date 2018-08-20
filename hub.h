#ifndef _HUB_H_
#define _HUB_H_

#include "subscriptionCatalog.h"
#include "eventRouter.h"
#include "notifier.h"
#include "event.h"
#include "scheduler.h"
#include "waitableQueue.h"

#include <queue>
#include <tr1/memory>
#include <pthread.h>




class Hub
{
public:
	typedef std::tr1::shared_ptr<Event> EventSharedPtr; 
	Hub();
	void StartNotify();


public: //change later to private - public for tests

	SubscriptionCatalog m_subsCatalog;
	WaitableQueue<EventSharedPtr> m_eventsQueue;
	EventRouter m_eventRouter;
	Notifier m_notifier;
	
private: 
	static void* HandleEvents(void* _context);
	
private:
	Scheduler m_scheduler;
	
};





#endif //_HUB_H_

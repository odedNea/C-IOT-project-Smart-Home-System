#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#include "event.h"
#include "subscriptionCatalog.h"
#include "waitableQueue.h"

#include <tr1/memory>
#include <queue>


class Notifier
{
typedef std::tr1::shared_ptr<Event> EventSharedPtr; 
public:
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 
	Notifier(SubscriptionCatalog& _catalog, WaitableQueue<EventSharedPtr>& _eventsQueue);
	void Notify(EventSharedPtr _event);
	
private:
	SubscriptionCatalog& m_catalog; 
	WaitableQueue<EventSharedPtr>& m_eventsQueue;

};









#endif //_NOTIFIER_H_

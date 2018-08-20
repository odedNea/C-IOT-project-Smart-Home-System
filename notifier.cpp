#include "notifier.h"
#include "event.h"
#include "eventSubject.h"
#include "iAgent.h"

#include <vector>
#include <tr1/memory>

typedef std::tr1::shared_ptr<Event> EventSharedPtr; 

using namespace std;

Notifier::Notifier(SubscriptionCatalog& _catalog, WaitableQueue<EventSharedPtr>& _eventsQueue) 
:	m_catalog(_catalog),
	m_eventsQueue(_eventsQueue)
{}



void Notifier::Notify(EventSharedPtr _event)
{
	EventSubject& subject = _event->GetData();
	EventSubSharedPtr subptr (new EventSubject(subject));
	
	
	vector<IAgent*> receivers = m_catalog.GetAgents(subptr);
	
	
	size_t size = receivers.size();
	
	for(size_t i = 0; i < size; ++i)
	{
		//thread create ?
		receivers[i]->TransferEvent(_event);
	}
}

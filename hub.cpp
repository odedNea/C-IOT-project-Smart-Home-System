#include "hub.h"
#include "subscriptionCatalog.h"
#include "eventRouter.h"
#include "notifier.h"
#include "smartHomeException.h"

#include <iostream> //tests
#include <queue>
#include <unistd.h>



Hub::Hub()
:	m_subsCatalog(),
	m_eventsQueue(),
	m_eventRouter(m_eventsQueue),
	m_notifier(m_subsCatalog, m_eventsQueue)
{}




void* Hub::HandleEvents(void* _context)
{
	if (NULL == _context)
	{
		throw(HubException("no context"));
	}
	
	Hub* hub = (Hub*)_context;
	std::cout << "in handle events\n";
	
	int i = 0;
	while(i++ < 10)
	{
		EventSharedPtr eventToSend = hub->m_eventsQueue.Pop();
		hub->m_notifier.Notify(eventToSend);
	}
		
	return NULL;
}




void Hub::StartNotify()
{
	std::cout << "in start notify\n";
	pthread_t thread;
	if (pthread_create(&thread, NULL, HandleEvents, this))
	{
		throw(SchedulerException("thread create fail"));
	}
	pthread_join(thread, NULL);
}




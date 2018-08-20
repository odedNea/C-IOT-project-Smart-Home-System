#include "eventRouter.h"
#include "event.h"

#include <tr1/memory>
#include <iostream>

using namespace std;


EventRouter::EventRouter(WaitableQueue<EventSharedPtr>& _eventsQueue)
:	m_eventsQueue(_eventsQueue)
{}


int EventRouter::Publish(EventSharedPtr _event)
{
	if (NULL == _event)
	{
		return 0;
	}

	std::cout << "about to push\n";
	m_eventsQueue.Push(_event);
	
	
	return 1;
}

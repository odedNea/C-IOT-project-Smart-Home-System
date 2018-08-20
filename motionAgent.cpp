#include "motionAgent.h"
#include "event.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <tr1/memory>
#include <assert.h>

using namespace std;


MotionAgent::MotionAgent(std::string _generalLocation, std::string _specificLocation, std::vector<EventSubSharedPtr>& _subsList,
						ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler)
:	m_type("motion"),
	m_floor(_generalLocation),
	m_room(_specificLocation),
	m_catalog(_catalog),
	m_eventRouter(_eventRouter)
	
{
	SubscribeToScheduler(_iAddToScheduler);
}



int MotionAgent::HelpSubToSched(void* _context)
{
	assert(NULL != _context);
	
	((IAgent*)_context)->SendEvents();

	return 0;
}





void MotionAgent::SubscribeToScheduler(IAddToSchedulers& _iAddToScheduler)
{
	_iAddToScheduler.AddToScheduler(1500, HelpSubToSched, this);
}


void MotionAgent::Subscribe()
{
	
}

void MotionAgent::SendEvents()
{
	EventSharedPtr event = EventCreate("motion");
	m_eventRouter.Publish(event);
}




void MotionAgent::TransferEvent(EventSharedPtr _event)
{
	cout <<"\neventType:"<< _event->GetType() << " agentType:"<<m_type <<endl;
}


const std::string& MotionAgent::GetType()const
{
	return m_type;
}


EventSharedPtr MotionAgent::EventCreate(std::string _type)
{
	return (EventSharedPtr (new Event(_type, m_room, m_floor)));
}

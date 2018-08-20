#include "sprinklerAgent.h"
#include "event.h"

#include <iostream>
#include <string>
#include <tr1/memory>
#include <unistd.h>
#include <iostream>

using namespace std;


SprinklerAgent::SprinklerAgent(std::string _generalLocation, std::string _specificLocation, std::vector<EventSubSharedPtr>& _subsList, 									ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter)
:	m_type("sprinkler"),
	m_floor(_generalLocation),
	m_room(_specificLocation),
	m_catalog(_catalog),
	m_eventRouter(_eventRouter)
{
	Subscribe(_subsList);
}


SprinklerAgent::~SprinklerAgent()
{}


void SprinklerAgent::Subscribe(vector<EventSubSharedPtr>& _subsList) 
{
	size_t size = _subsList.size();
	
	for (size_t i = 0; i < size; ++i)
	{
		m_catalog.Subscribe(_subsList[i], this); 
	}

}


void SprinklerAgent::SendEvents()
{
}



void SprinklerAgent::TransferEvent(EventSharedPtr _event)
{
	cout <<"\neventType: "<< _event->GetType() <<", room:"<<_event->GetFloor()<< ", time: " << _event->GetTime() <<endl;
}


const std::string& SprinklerAgent::GetType()const
{
	return m_type;
}


EventSharedPtr SprinklerAgent::EventCreate(std::string _type)
{
	return (EventSharedPtr (new Event(_type, "2", "2b")));
}

#ifndef _SPRINKLER_AGENT_H_
#define _SPRINKLER_AGENT_H_

#include "iAgent.h"
#include "iSubscriptionCatalog.h"
#include "iEventRouter.h"
#include "eventSubject.h"

#include <string>
#include <tr1/memory>
#include <vector>


class SprinklerAgent : public IAgent
{
public:
typedef std::tr1::shared_ptr<Event> EventSharedPtr; 
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 
	SprinklerAgent(std::string _generalLocation, std::string _specificLocation, std::vector<EventSubSharedPtr>& _subsList //check _subsList
	, ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter); 
	virtual ~SprinklerAgent();
	virtual void TransferEvent(EventSharedPtr _event);
	virtual const std::string& GetType()const;
	virtual EventSharedPtr EventCreate(std::string _type); //later will be private
	virtual void Subscribe(std::vector<EventSubSharedPtr>& _subsList);
	virtual void SendEvents();

protected:
	std::string m_type;
	std::string m_floor;
	std::string m_room;
	ISubscriptionCatalog& m_catalog;
	IEventRouter& m_eventRouter;
};



/*SprinklerAgent::~SprinklerAgent(){;} // destroy m_subsVec*/











#endif //_SPRINKLER_AGENT_H_

#ifndef _MOTION_AGENT_H_
#define _MOTION_AGENT_H_

#include "iAgent.h"
#include "iSubscriptionCatalog.h"
#include "iEventRouter.h"
#include "eventSubject.h"
#include "iAddToSchedulers.h"

#include <string>
#include <tr1/memory>
#include <vector>


typedef std::tr1::shared_ptr<Event> EventSharedPtr; 

class MotionAgent : public IAgent
{
public:
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 

	MotionAgent(std::string _generalLocation, std::string _specificLocation, std::vector<EventSubSharedPtr>& _subsList, 
				ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler); 
				
	virtual ~MotionAgent(){;} 
	virtual void TransferEvent(EventSharedPtr _event);
	virtual const std::string& GetType()const;
	virtual void Subscribe();
	virtual void SendEvents();
	void SubscribeToScheduler(IAddToSchedulers& _iAddToScheduler);

private:
	virtual EventSharedPtr EventCreate(std::string _type); //later will be private
	static int HelpSubToSched(void* _context);

private:
	std::string m_type;
	std::string m_floor;
	std::string m_room;
	ISubscriptionCatalog& m_catalog;
	IEventRouter& m_eventRouter;
};







#endif //_MOTION_AGENT_H_

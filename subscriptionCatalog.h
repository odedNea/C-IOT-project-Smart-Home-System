#ifndef _SUBSCRIPTION_CATALOG_H_
#define _SUBSCRIPTION_CATALOG_H_

#include "iSubscriptionCatalog.h"
#include "iAgent.h"
#include "eventSubject.h"

#include <map>
#include <vector>
#include <tr1/memory>

typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 

class SubscriptionCatalog : public ISubscriptionCatalog
{
private:
	struct CmpEvents
	{

		bool operator()(EventSubSharedPtr _a, EventSubSharedPtr _b) const
		{
			return _a->Compare(_b);
		}
	};
typedef std::map<EventSubSharedPtr, std::vector<IAgent*>, CmpEvents> SubsMap; // no need for typedef
	
public:

	virtual int Subscribe(EventSubSharedPtr _eventData, IAgent* _agent);
	
	const std::vector<IAgent*>& GetAgents(EventSubSharedPtr); //CONST!!!!
	
	
	virtual ~SubscriptionCatalog(); //Destroy Event and Agent in the map

private:
	
	SubsMap m_subscribers;

};









#endif //_SUBSCRIPTION_CATALOG_H_

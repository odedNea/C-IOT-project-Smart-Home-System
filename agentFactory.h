#ifndef _AGENT_FACTORY_H_
#define _AGENT_FACTORY_H_

#include "iAgent.h"
#include "iSubscriptionCatalog.h"
#include "iEventRouter.h"
#include "iAddToSchedulers.h"

#include <string>


class AgentFactory // pure virtual
{
public:
	virtual ~AgentFactory(){};

	virtual IAgent* AgentCreate(std::string& _generalLocation, std::string& _specificLocation, std::string& _config,
								 ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler) = 0; 
};




#endif //_AGENT_FACTORY_H_

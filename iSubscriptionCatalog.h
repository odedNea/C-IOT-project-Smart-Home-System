#ifndef _I_SUBSCRIPTION_CATALOG_H_
#define _I_SUBSCRIPTION_CATALOG_H_

#include "eventSubject.h"
#include "iAgent.h"

#include <tr1/memory>

class ISubscriptionCatalog
{
public:
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 
	virtual ~ISubscriptionCatalog(){;}
	
	virtual int Subscribe(EventSubSharedPtr _eventData, IAgent* _agent) = 0;

};












#endif //_I_SUBSCRIPTION_CATALOG_H_

#ifndef _INITIALIZER_H_
#define _INITIALIZER_H_

#include "iAddToMap.h"
#include "agentFactory.h"
#include "iAgent.h"
#include "iSubscriptionCatalog.h"
#include "iEventRouter.h"
#include "iAddToSchedulers.h"

#include <map>
#include <string>

class Initializer : public IAddToMap
{
public:
	Initializer(ISubscriptionCatalog& m_catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler);
	
	~Initializer();
	
	void LoadSharedObjects();

	IAgent* CreateAgents(std::string& _agentType, std::string& _generalLocation, std::string& _specificLocation, std::string& _config); 

	virtual void AddToMap(std::string _type, AgentFactory* _factoryCreator);


private:
	struct CmpCreators
	{
		bool operator()(const std::string _keyA, const std::string _keyB) const
		{
			return _keyA < _keyB;
		}
	};


private:
	ISubscriptionCatalog& m_catalog;
	IEventRouter& m_eventRouter;
	IAddToSchedulers& m_iAddToScheduler;
	std::map<std::string, AgentFactory*, CmpCreators> m_creatorsMap; // destory

};





#endif //_INITIALIZER_H_

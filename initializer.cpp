#include "initializer.h"
#include "iAgent.h"
#include "agentFactory.h"
#include "iLoader.h"

#include <dlfcn.h>
#include <iostream>
#include <map>
#include <string>


using namespace std;





Initializer::Initializer(ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler) 
:	m_catalog(_catalog),
	m_eventRouter(_eventRouter),
	m_iAddToScheduler(_iAddToScheduler)
{}




Initializer::~Initializer()
{
	map<string, AgentFactory*>::iterator it;
	for (it = m_creatorsMap.begin(); it != m_creatorsMap.end(); ++it)
	{
		delete it->second;
	}
}


void Initializer::AddToMap(string _type, AgentFactory* _factoryCreator) 
{
	if (NULL == _factoryCreator)
	{
		return;
	}

	m_creatorsMap[_type] = _factoryCreator;
}



void Initializer::LoadSharedObjects()
{
	void* handle = dlopen("./eltaLibrary.so", RTLD_LAZY); 

	ILoader* (*create)();
	void (*destroy)(ILoader*);

	create = (ILoader* (*)())dlsym(handle, "create_object");
	destroy = (void (*)(ILoader*))dlsym(handle, "destroy_object");

	ILoader* libLoader = (ILoader*)create();
	libLoader->Load(*this);
	destroy( libLoader );

}


IAgent* Initializer::CreateAgents(string& _agentType, string& _generalLocation, string& _specificLocation, string& _config)
{
	return m_creatorsMap[_agentType]->AgentCreate(_generalLocation, _specificLocation, _config, m_catalog, m_eventRouter, m_iAddToScheduler);
}

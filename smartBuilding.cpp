#include "smartBuilding.h"
#include "smartHomeException.h"



SmartBuilding::SmartBuilding(std::string m_configPath) 
:	m_schedulers(3),
	m_initializer(m_hub.m_subsCatalog, m_hub.m_eventRouter, m_schedulers),
	m_configurator(m_configPath)
{}



SmartBuilding::~SmartBuilding()
{
	size_t size = m_agents.size();
	
	for (size_t i = 0; i < size; ++i)
	{
		delete m_agents[i];	
	}
}



void SmartBuilding::Start()
{
	m_initializer.LoadSharedObjects();

	ConfigStruct pack;

	while (m_configurator.Config(pack))
	{
		IAgent* newAgent = m_initializer.CreateAgents(pack.m_type, pack.m_room, pack.m_floor, pack.m_config);
		
		m_agents.push_back(newAgent);
	}
	
	m_schedulers.RunSchedulers();
	
	m_hub.StartNotify();
}

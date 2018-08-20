#ifndef __SMART_BUILDING_H__
#define __SMART_BUILDING_H__

#include "initializer.h"
#include "hub.h"
#include "schedulers.h"
#include "iAgent.h"
#include "configurator.h"

#include <vector>
#include <string>

class SmartBuilding
{
public:
	SmartBuilding(std::string m_configPath);
	
	~SmartBuilding();
	
	void Start();
	

private:
	Hub m_hub;
	std::vector<IAgent*> m_agents; 
	Schedulers m_schedulers;
	Initializer m_initializer; 
	Configurator m_configurator;

};








#endif //__SMART_BUILDING_H__

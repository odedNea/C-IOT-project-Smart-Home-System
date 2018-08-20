#ifndef _I_ADD_TO_MAP_H_
#define _I_ADD_TO_MAP_H_

#include "agentFactory.h"

#include <string>

class IAddToMap
{
public:
	virtual ~IAddToMap(){;}
	virtual void AddToMap(std::string _type, AgentFactory* _factoryCreator) = 0;

};





#endif //_I_ADD_TO_MAP_H_

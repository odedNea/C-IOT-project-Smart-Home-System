#ifndef __I_LOADER_H__
#define __I_LOADER_H__

#include "agentFactory.h"
#include "iAddToMap.h"


class ILoader
{
public:
	virtual ~ILoader(){;}

	virtual void Load(IAddToMap& _interface) = 0;
};



#endif //__I_LOADER_H__

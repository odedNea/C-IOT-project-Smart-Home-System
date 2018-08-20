#ifndef __ELTA_LIBRARY_H__
#define __ELTA_LIBRARY_H__

#include "agentFactory.h"
#include "iAddToMap.h"
#include "iLoader.h"
#include "iAddToSchedulers.h"
#include "eventSubject.h"

#include <map>
#include <vector>
#include <string>
#include <tr1/memory>

class EltaLibrary : public ILoader
{
public:
  EltaLibrary();
  virtual ~EltaLibrary();

  /* use virtual otherwise linker will try to perform static linkage */
  virtual void Load(IAddToMap& _interface);


};


/////////////////// * Motion Factory * ///////////////////////////


class MotionFactory : public AgentFactory
{
public:
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 
	virtual ~MotionFactory(){};

	virtual IAgent* AgentCreate(std::string& _generalLocation, std::string& _specificLocation, std::string& _subscriptionInfo,
								 ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler);

private:
	void SubsVecCreate(std::string _subscriptionInfo, std::vector<EventSubSharedPtr>& _subsVec);
};



/////////////////////// * Sprinkler Factory * //////////////////////////



class SprinklerFactory : public AgentFactory
{
public:
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 
	virtual ~SprinklerFactory(){};

	virtual IAgent* AgentCreate(std::string& _generalLocation, std::string& _specificLocation, std::string& _subscriptionInfo
	, ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler);

private:
	void SubsVecCreate(std::string _subscriptionInfo, std::vector<EventSubSharedPtr>& _subsVec);
};





#endif //__ELTA_LIBRARY_H__

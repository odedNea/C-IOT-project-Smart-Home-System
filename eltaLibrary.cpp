#include "eltaLibrary.h"
#include "iLoader.h"
#include "iAddToMap.h"
#include "motionAgent.h"
#include "sprinklerAgent.h"
#include "smartHomeException.h"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

extern "C" EltaLibrary* create_object()
{
  return new EltaLibrary;
}

extern "C" void destroy_object( EltaLibrary* object )
{
  delete object;
}

EltaLibrary::~EltaLibrary()
{

}

EltaLibrary::EltaLibrary()
{

}


void EltaLibrary::Load(IAddToMap& _addToMap)
{
	MotionFactory* motionFactory = new MotionFactory;
	SprinklerFactory* sprinklerFactory = new SprinklerFactory;

	_addToMap.AddToMap("motion", motionFactory);
	_addToMap.AddToMap("sprinkler", sprinklerFactory);
}



/////////////////// * Motion Factory * ///////////////////////////




void MotionFactory::SubsVecCreate(string _subscriptionInfo, std::vector<EventSubSharedPtr>& _subsVec)
{
    std::istringstream iss(_subscriptionInfo);
    std::string token, type, genLocation, specLocation;


    while (std::getline(iss, token, '|'))
    {
    	for (int i = 0; getline(iss, token, ','); ++i)
    	{
    		switch(i)
			{
				case 0:
				    type = token;
				    break;
				case 1:
				    genLocation = token;
				    break;
			    case 2:
				    specLocation = token;
				    break;
				default:
				    throw (InitException("subscribers list error")); //handle exception
				    break;
			}
    
    	}
    	
    	EventSubSharedPtr eventSubject = EventSubSharedPtr(new EventSubject(type, genLocation, specLocation));
    	_subsVec.push_back(eventSubject);

	}
}

IAgent* MotionFactory::AgentCreate(std::string& _generalLocation, std::string& _specificLocation, std::string& _subscriptionInfo, 										ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler)
{
	vector<EventSubSharedPtr> subsVec;
	SubsVecCreate(_subscriptionInfo, subsVec);

	return new MotionAgent(_generalLocation, _specificLocation, subsVec, _catalog, _eventRouter, _iAddToScheduler); 
}
	
	
/////////////////////// * Sprinkler Factory * //////////////////////////



void SprinklerFactory::SubsVecCreate(string _subscriptionInfo, std::vector<EventSubSharedPtr>& _subsVec)
{
    std::istringstream iss(_subscriptionInfo);
    std::string token, type, genLocation, specLocation;

    while (std::getline(iss, token, '|'))
    {
    	for (int i = 0; getline(iss, token, ','); ++i)
    	{
    		switch(i)
			{
				case 0:
				    type = token;
				    break;
				case 1:
				    genLocation = token;
				    break;
			    case 2:
				    specLocation = token;
				    break;
				default:
				    throw (InitException("subscribers list error"));
				    break;
			}
    
    	}
    	
    	EventSubSharedPtr eventSubject = EventSubSharedPtr(new EventSubject(type, genLocation, specLocation));
    	_subsVec.push_back(eventSubject);

	}
}

IAgent* SprinklerFactory::AgentCreate(std::string& _generalLocation, std::string& _specificLocation, std::string& _subscriptionInfo,
 										ISubscriptionCatalog& _catalog, IEventRouter& _eventRouter, IAddToSchedulers& _iAddToScheduler)
{
	vector<EventSubSharedPtr> subsVec;
	SubsVecCreate(_subscriptionInfo, subsVec);

	return new SprinklerAgent(_generalLocation, _specificLocation, subsVec, _catalog, _eventRouter); 
}




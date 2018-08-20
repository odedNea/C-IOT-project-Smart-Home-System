#include "subscriptionCatalog.h"
#include "eventSubject.h"
#include "iAgent.h"
#include "smartHomeException.h"

#include <map>
#include <vector>
#include <iostream> //delete after

using namespace std;


SubscriptionCatalog::~SubscriptionCatalog()
{

}


int SubscriptionCatalog::Subscribe(EventSubSharedPtr _eventSubject, IAgent* _agent)
{
	if (NULL == _eventSubject)
	{
		throw (InitException("bad input subscribe"));
	}
	cout << m_subscribers.size() << endl;
	cout << _eventSubject->GetType() << endl;
	m_subscribers[_eventSubject].push_back(_agent);
	
	return 1;
}


const vector<IAgent*>& SubscriptionCatalog::GetAgents(EventSubSharedPtr _eventSubject)
{
	if (NULL == _eventSubject)
	{
		throw (InitException("bad input subscription catalog"));
	}

	return m_subscribers[_eventSubject]; //might change the content

}




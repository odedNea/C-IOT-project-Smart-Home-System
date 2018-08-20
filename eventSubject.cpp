#include "eventSubject.h"

#include <string>

using namespace std;


EventSubject::EventSubject(string _type, string _room, string _floor) : m_type(_type), m_room(_room), m_floor(_floor) {}



bool EventSubject::Compare(EventSubSharedPtr _cmpEvent)const
{
	return (m_type < _cmpEvent->GetType());
}

//TODO add more comparisons

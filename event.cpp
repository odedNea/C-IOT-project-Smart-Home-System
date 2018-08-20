#include "event.h"
#include "eventSubject.h"

#include <string>
#include <ctime>

using namespace std;


Event::Event(string _type, string _room, string _floor)
:	m_data(_type, _room, _floor)
{
	time_t now = time(0);
	m_time = ctime(&now);
}



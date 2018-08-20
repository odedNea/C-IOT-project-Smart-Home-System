#ifndef _EVENT_H_
#define _EVENT_H_

#include "eventSubject.h"

#include <string>
#include <ctime>

class Event
{
public:
	Event(std::string _type, std::string _room, std::string _floor);

	inline const std::string& GetType()const;
	inline const std::string& GetRoom()const;
	inline const std::string& GetFloor()const;
	inline const std::string& GetTime()const;
	inline EventSubject& GetData(); //CONST!

private:
	EventSubject m_data;
	std::string m_time;
};





inline const std::string& Event::GetType()const
{
	return m_data.GetType();
}


inline const std::string& Event::GetRoom()const
{
	return m_data.GetRoom();
}


inline const std::string& Event::GetFloor()const
{
	return m_data.GetFloor();
}


inline const std::string& Event::GetTime()const
{
	return m_time;
}


inline EventSubject& Event::GetData()
{
	return m_data;
}





#endif //_EVENT_H_

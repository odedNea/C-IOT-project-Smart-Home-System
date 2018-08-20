#ifndef _EVENT_SUBJECT_H_
#define _EVENT_SUBJECT_H_

#include <string>
#include <tr1/memory>

class EventSubject
{
public:
typedef std::tr1::shared_ptr<EventSubject> EventSubSharedPtr; 

	EventSubject(std::string _type, std::string _room, std::string _floor);

	inline const std::string& GetType()const;
	inline const std::string& GetRoom()const;
	inline const std::string& GetFloor()const;
	bool Compare(EventSubSharedPtr _cmpEvent)const;

private:
	std::string m_type;
	std::string m_room;
	std::string m_floor;
};





inline const std::string& EventSubject::GetType()const
{
	return m_type;
}


inline const std::string& EventSubject::GetRoom()const
{
	return m_room;
}


inline const std::string& EventSubject::GetFloor()const
{
	return m_floor;
}





#endif //_EVENT_SUBJECT_H_

#include "time.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#define MILI_TO_SEC(mili) ((mili)/(1000))
#define MILI_TO_NANO(mili) (((mili) % 1000) * 1000000)
#define SEC_TO_MICRO(sec) ((sec)*(1000000))
#define NANO_TO_MICRO(nano) ((nano)/(1000))

struct Time
{
	clockid_t m_clock;
	struct timespec m_time;
};



Time* TimeCreate(clockid_t _clock_id, size_t _period_ms)
{
	Time* time;

	time = (Time*)malloc(sizeof(Time));

	if(NULL == time)
	{
		return NULL;
	}

	time->m_clock = _clock_id;
	TimeCalculateNext(time, _period_ms);

	return time;
}


void TimeCalculateNext(Time* _time, size_t _period_ms)
{
	size_t sec, nsec;

	if(NULL == _time)
	{
		return;
	}

    clock_gettime(_time->m_clock, &_time->m_time);

	sec = MILI_TO_SEC(_period_ms) ;
	nsec = MILI_TO_NANO(_period_ms);

	_time->m_time.tv_sec+= (long int)sec;
	_time->m_time.tv_nsec+= (long int)nsec;
}


int TimeCompare(Time* _time1, Time* _time2)
{
	if (_time1->m_time.tv_sec == _time2->m_time.tv_sec)
	{
		return _time1->m_time.tv_nsec > _time2->m_time.tv_nsec;
	}

	return _time1->m_time.tv_sec > _time2->m_time.tv_sec;
}


void TimeDestory(Time* _time)
{
	if(NULL == _time)
	{
		return;
	}

	free(_time);
}


void TimeSleep(Time *_time)
{
	struct timespec currentTime;
	size_t diff, TimeNano, CurTimeNano;

	if(NULL == _time)
	{
		return;
	}

	clock_gettime(_time->m_clock, &currentTime);

	CurTimeNano = (size_t)(SEC_TO_MICRO(currentTime.tv_sec) + NANO_TO_MICRO(currentTime.tv_nsec));
	TimeNano = (size_t)(SEC_TO_MICRO(_time->m_time.tv_sec) + NANO_TO_MICRO(_time->m_time.tv_nsec));

	if(CurTimeNano > TimeNano)
	{
		diff = 0;
	}
	else
	{
		diff = TimeNano - CurTimeNano;
	}
 
	usleep( (useconds_t)diff);
}

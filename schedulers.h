#ifndef _SCHEDULERS_H_
#define _SCHEDULERS_H_

#include "iAddToSchedulers.h"
#include "scheduler.h"

#include <vector> //schedulers vec
#include <stddef.h> //size_t

class Schedulers : public IAddToSchedulers
{
public:
	Schedulers(size_t _numOfSchedulers);
	virtual ~Schedulers();

	virtual void AddToScheduler(size_t _timeMs, int (*_helpFunc)(void*), void*);
	
	void RunSchedulers();

private:
	std::vector<Scheduler*> m_schedulers;	
	size_t m_numOfSchedulers;
	size_t m_curSchedulerNum;

};


#endif //_SCHEDULERS_H_

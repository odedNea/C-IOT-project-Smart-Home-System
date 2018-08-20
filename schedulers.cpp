#include "schedulers.h"
#include "scheduler.h"




Schedulers::Schedulers(size_t _numOfSchedulers)
:	m_numOfSchedulers(_numOfSchedulers),
	m_curSchedulerNum(0)
{
	for (size_t i = 0; i < _numOfSchedulers; ++i)
	{
		m_schedulers.push_back(new Scheduler());
	}
}


Schedulers::~Schedulers()
{
	for (size_t i = 0; i < m_numOfSchedulers; ++i)
	{
		delete m_schedulers[i];
	}
}


void Schedulers::AddToScheduler(size_t _timeMs, int (*_helpFunc)(void*), void* _context)
{
	Scheduler* curScheduler = m_schedulers[m_curSchedulerNum];
	curScheduler->Add(_timeMs, _helpFunc, _context);
 
	++m_curSchedulerNum;
	m_curSchedulerNum %= m_numOfSchedulers; 
}



void Schedulers::RunSchedulers()
{
	for (size_t i = 0; i < m_numOfSchedulers; ++i)
	{
		m_schedulers[i]->Run();
	}

}

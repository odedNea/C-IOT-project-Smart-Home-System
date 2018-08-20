#include "scheduler.h"
#include "smartHomeException.h"
//extern "C"
//{
	#include "PE.h"
//}


#include <time.h> //clock_realtime
#include <iostream>
#include <pthread.h>
#include <unistd.h>


Scheduler::Scheduler()
{
	m_executor = PE_Create("testlog", CLOCK_REALTIME);
}


Scheduler::~Scheduler()
{
	PE_Destroy(m_executor);
}


void Scheduler::Add(size_t _period_ms, ActionFunc _func, void* _context)
{
	PE_Add(m_executor, _func, _context, _period_ms);
}



void* Scheduler::WrapRun(void* _context)
{
	PE_Run((PE*)_context);
	return NULL;
}


void Scheduler::Run()
{

	pthread_t thread;
	if (pthread_create(&thread, NULL, WrapRun, m_executor))
	{
		throw(SchedulerException("thread create fail"));
	}
	pthread_detach(thread);
}

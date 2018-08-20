#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

/*extern "C"*/
/*{*/
	#include "PE.h"
/*}*/

typedef int	(*ActionFunc)(void * _context);

class Scheduler
{
public:
	Scheduler();
	~Scheduler();
	
	// add events to publish
	void Add(size_t _period_ms, ActionFunc _func, void* _context);
	
	void Run();



private:
	static void* WrapRun(void* _context);

private:
	PE* m_executor;
};



#endif //__SCHEDULER_H__

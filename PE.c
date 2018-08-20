#include "PE.h"
#include "task.h"
#include "pqueue.h"
#include <stdlib.h> /* malloc */

struct PE
{
	PQ* m_pQueue;
	clockid_t m_clkId;
	int m_Ispaused;
};


PE* PE_Create(const char* _name, clockid_t _clk_id)
{
	PQ* pqueue;
	PE* pe = (PE*)malloc(sizeof(PE));

	if(NULL == pe)
	{
		return NULL;
	}

	pqueue = PQCreate(TaskCompare);

	if(NULL == pqueue)
	{
		return NULL;
	}

	pe->m_pQueue = pqueue;
	pe->m_clkId = _clk_id;
	pe->m_Ispaused = 0;

/*	LoadZLogFile("", _name);*/

	return pe;
}


void PE_Destroy(PE* _pe)
{
	if(NULL == _pe)
	{
		return;
	}	

	PQDestroy(&_pe->m_pQueue);
	free(_pe);
}




int PE_Add(PE* _pe, CompareFunc _Func, void* _context, size_t _period_ms)
{
	Task* task;

	if(NULL == _pe)
	{
		return -1;
	}	

	task = TaskCreate(_Func, _pe->m_clkId, _context, _period_ms);
	PQInsert(_pe->m_pQueue, (void*)task);

	return 0;
}




size_t PE_Run(PE* _pe)
{
	Task* task;
	size_t size, timeCount = 0;

	if(NULL == _pe)
	{
		return 0;
	}

	size = PQSize(_pe->m_pQueue);

	while(size)
	{
		++timeCount;
		task = (Task*)PQExtract(_pe->m_pQueue);

		if(TaskRun(task) == 0)
		{
			TaskUpdateTime(task);
			PQInsert(_pe->m_pQueue, task);
		}
		else
		{
			TaskDestory(task);
			--size;
		}

		if(_pe->m_Ispaused == 1)
		{
			break;
		}
	}

	return timeCount;
}



size_t PE_Pause(PE* _pe)
{
	if(NULL == _pe)
	{
		return 0;
	}

	_pe->m_Ispaused = 1;

	return PQSize(_pe->m_pQueue);



}

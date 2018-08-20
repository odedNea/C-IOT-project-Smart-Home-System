#include "task.h"
#include "time.h"
#include <stdlib.h>

struct Task
{
	CompareFunc m_taskFunc;
	clockid_t m_clkId;
	size_t m_interval;
	void* m_context;
	Time* m_time;
};



Task* TaskCreate(CompareFunc _taskFunc, clockid_t _clk_id, void* _context, size_t _period_ms)
{
	Task* task;
	Time* time;

	if(NULL == _taskFunc)
	{
		return NULL;
	}

	task = (Task*)malloc(sizeof(Task));

	if(NULL == task)
	{
		return NULL;
	}

	time = TimeCreate(_clk_id, _period_ms);
	if(NULL == time)
	{
		free(task);
		return NULL;
	}

	task->m_time = time;
	task->m_taskFunc = _taskFunc;
	task->m_clkId = _clk_id;
	task->m_interval = _period_ms;
	task->m_context = _context;

	return task;
}



void TaskDestory(Task* _task)
{
	if(NULL == _task)
	{
		return;
	}

	TimeDestory(_task->m_time);
	free(_task);
}



int TaskCompare(const void* _task1, const void* _task2)
{
	return TimeCompare( ((Task*)_task1)->m_time, ((Task*)_task2)->m_time);
}



int TaskRun(void* _task)
{
	if(NULL == _task)
	{
		return -1;
	}
	TimeSleep( ((Task*)_task)->m_time );

	return (*((Task*)_task)->m_taskFunc)( ((Task*)_task)->m_context);
}



void TaskUpdateTime(Task* _task)
{
	if(NULL == _task)
	{
		return;
	}	

	TimeCalculateNext(_task->m_time, _task->m_interval);

}

#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>

#include <stddef.h>  /* size_t */

typedef int	(*CompareFunc)(void * _context);

typedef struct Task Task;

/**  
 * @brief creates a Task. 
 * @return a pointer to Task or NULL
 */
Task* TaskCreate(CompareFunc _taskFunc, clockid_t _clk_id, void* _context, size_t _period_ms);

void TaskDestory(Task* _task);


/**  
 * @brief compares between 2 tasks.  
 * @param[in] _task1 
 * @param[in] _task2
 * @return (x<y)?0:1;
 */
int TaskCompare(const void* _task1, const void* _task2);

/**
 * @brief runs the tasks function and updates next run time 
 * @param[in] _task - task
 * @return 0 if the task has finished else 1
 */
int TaskRun(void* _task);


void TaskUpdateTime(Task* _task);

#endif /*__TASK_H__*/

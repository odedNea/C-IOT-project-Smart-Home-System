#ifndef __PE_H__
#define __PE_H__

#include <time.h>

typedef struct PE PE;
typedef int	(*CompareFunc)(void * _context);

/**  
 * @brief creates a PE.  
 * @param[in] _name - Zlog file name
 * @param[in] _clk_id - current time
 * @return a pointer to PE or NULL
 */
PE* PE_Create(const char* _name, clockid_t _clk_id);

/** 
 * @brief destroy PE
 * @param _executor : pointer to the PE
 */	
void PE_Destroy(PE* _pe);

/** 
 * @brief Add a task to PE.
 * @param _executor : pointer to the PE
 * @param _Func : is represented by a user provided function pointer.
 * @param _context : context of the task function
 * @param _period_ms : is the period of recurrence in milli seconds.
 * @return
 */	
int PE_Add(PE* _pe, CompareFunc _Func, void* _context, size_t _period_ms);

/**
 * @brief Start running the executor
 * @param _pe : pointer to the PE
 * @return the number of times the tasks have runned
 */	
size_t PE_Run(PE* _pe);

/** 
 * @brief Pause running the executor
 *
 * @param _pe : pointer to the PE
 * @return the number of tasks remaining inside the executor.
 */	
size_t PE_Pause(PE* _pe);


#endif /*__PE_H__*/

#ifndef _TIME_H_
#define _TIME_H_

#include <time.h>

typedef struct Time Time;

/**  
 * @brief creates a time struct
 *
 * @param[in] clock_id: clock mode.
 * @return return a pointer to the current time.
 * 
 */
Time* TimeCreate(clockid_t _clock_id, size_t _period_ms);



void TimeDestory(Time* _time);



/**  
 * @brief adds a period of recurrence in milli seconds to _time
 *
 * @param[in] _time: time
 * @param[in] _period_ms: the period of recurrence in milli seconds.
 * @return void
 * 
 */
void TimeCalculateNext(Time* _time, size_t _period_ms);

/**  
 * @brief compares between 2 times.  
 * @param[in] _time1 
 * @param[in] _time2
 * @return (x<y)?0:1;
 */
int TimeCompare(Time* _time1, Time* _time2);

/** 
 * @brief sleep 
 * @param[in] _time
 * @return
 */
void TimeSleep(Time *_time);








#endif /*_TIME_H_*/

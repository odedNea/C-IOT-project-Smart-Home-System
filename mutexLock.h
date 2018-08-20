#ifndef _MUTEX_LOCK_H_
#define _MUTEX_LOCK_H_

#include <pthread.h>

class MutexLock
{
public:	
	MutexLock(pthread_mutex_t& _mutex);
	~MutexLock();

private:
	pthread_mutex_t& m_mutex;
};







#endif //_MUTEX_LOCK_H_

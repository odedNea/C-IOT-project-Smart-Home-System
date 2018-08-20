#include "mutexLock.h"


MutexLock::MutexLock(pthread_mutex_t& _mutex)
:	m_mutex(_mutex)
{
	pthread_mutex_lock(&m_mutex);
}

MutexLock::~MutexLock()
{
	pthread_mutex_unlock(&m_mutex);
}

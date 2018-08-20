#ifndef _WAITABLE_QUEUE_H_
#define _WAITABLE_QUEUE_H_

#include "mutexLock.h"

#include <queue>
#include <pthread.h>

template <class T>
class WaitableQueue
{
public:
	WaitableQueue();
	~WaitableQueue();
	
	void Push(T _t);
	
	T Pop();
	
	pthread_mutex_t& GetMutex();

private:
	std::queue<T> m_queue;
	pthread_mutex_t m_lock;
	pthread_cond_t m_cond;
};


template <class T>
WaitableQueue<T>::WaitableQueue()
{
	pthread_mutex_init(&m_lock, NULL);
	pthread_cond_init(&m_cond, NULL);
}


template <class T>
WaitableQueue<T>::~WaitableQueue()
{
	pthread_mutex_destroy(&m_lock);
}

template <class T>
void WaitableQueue<T>::Push(T _t)
{
	MutexLock(GetMutex());

	m_queue.push(_t);
	if (1 == m_queue.size())
	{
		pthread_cond_broadcast(&m_cond);
	}
}

template <class T>
T WaitableQueue<T>::Pop()
{
	MutexLock(GetMutex());
	while (m_queue.empty())
	{
		pthread_cond_wait(&m_cond, &m_lock);
	}
	
	T t = m_queue.front();
	m_queue.pop();

	return t;
}


template<class T>	
pthread_mutex_t& WaitableQueue<T>::GetMutex()
{
	return m_lock;
}


#endif //_WAITABLE_QUEUE_H_

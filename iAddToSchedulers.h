#ifndef _I_ADD_TO_SCHEDULERS_H_
#define _I_ADD_TO_SCHEDULERS_H_

#include "iAddToSchedulers.h"

#include <stddef.h>

class IAddToSchedulers
{
public:
	virtual ~IAddToSchedulers(){;}

	virtual void AddToScheduler(size_t _timeMs, int (*_helpFunc)(void*), void*) = 0;
};

#endif //_I_ADD_TO_SCHEDULERS_H_

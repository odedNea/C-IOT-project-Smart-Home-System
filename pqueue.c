#include "pqueue.h"
#include "Heap.h"
#include "vector.h"
#include <stdlib.h>

struct PQ
{
	Heap* m_heap;
};




PQ* PQCreate(LessThan _Less)
{
	PQ* pqueue;
	Heap* heap;
	Vector* vec;

	if(NULL == _Less)
	{
		return NULL;
	}

	pqueue = (PQ*)malloc(sizeof(PQ));
	if(NULL == pqueue)
	{
		return NULL;
	}

	vec = Vector_Create(50, 50);
	if(NULL == vec)
	{
		return NULL;
	}

	heap = Heap_Build(vec, _Less);
	if(NULL == heap)
	{
		return NULL;
	}

	pqueue->m_heap = heap;

	return pqueue;
}


void PQDestroy(PQ** _pqueue)
{
	Vector* vec;

	if(NULL == _pqueue || NULL == *_pqueue)
	{
		return;
	}

	vec = Heap_Destroy(&(*_pqueue)->m_heap);
	Vector_Destroy(&vec, NULL);
	free(*_pqueue);
	*_pqueue = NULL;
}


void PQInsert(PQ* _pqueue, void* _element)
{
	if(NULL == _pqueue)
	{
		return;
	}

	Heap_Insert(_pqueue->m_heap, _element);
}


void* PQExtract(PQ* _pqueue)
{
	if(NULL == _pqueue)
	{
		return NULL;
	}

	return Heap_Extract(_pqueue->m_heap);
}


size_t PQSize(PQ* _pqueue)
{
	if(NULL == _pqueue)
	{
		return 0;
	}

	return Heap_Size(_pqueue->m_heap);
}

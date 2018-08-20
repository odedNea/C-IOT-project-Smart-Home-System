#include "Heap.h"

#include <stdio.h>   /* printf */
#include <stdlib.h> /* realloc, malloce */

struct Heap
{
    Vector*              m_vec;
    LessThanComparator   m_less;
    size_t               m_heapSize;
};



static void IdxSwap(Vector *_vec, size_t _parentInx, size_t _chiledInx)
{
	void *child, *parent;

	Vector_Get(_vec, _chiledInx, &child);
	Vector_Get(_vec, _parentInx, &parent);

	Vector_Set(_vec, _chiledInx, parent);
	Vector_Set(_vec, _parentInx, child);	
}
/********************************************************************************************************************/
static Heap_ResultCode BubbleUp(Vector* _vec, size_t _index, LessThanComparator _pfLess)
{
	void* newChild, *parent;
	if(_index/2 < 1)
	{
		return HEAP_SUCCESS;
	}
	
	Vector_Get( _vec, _index, &newChild);
	
	Vector_Get( _vec, _index/2, &parent); 
	
	
	
	if(_pfLess(parent, newChild))
	{
		IdxSwap(_vec, _index/2, _index);
		
		BubbleUp(_vec , _index/2, _pfLess); 
	}
	
	return HEAP_SUCCESS;

}
/********************************************************************************************************************/
static void Heapify(Vector* _vector, size_t _root, LessThanComparator _pfLess, size_t _size)
{
	void *rootValue, *largestValue, *leftValue, *rightValue;
	size_t left, right, largest;

	right = 2*_root + 1;
	left = 2*_root;

	Vector_Get(_vector, _root, &rootValue);
	largestValue = rootValue;
	largest = _root;

	if(_size >= right)
	{
		Vector_Get(_vector, right, &rightValue);
		if( (_pfLess)(largestValue, rightValue) )
		{
			largestValue = rightValue;
			largest = right;		
		}
	}

	if(_size >= left)
	{
		Vector_Get(_vector, left, &leftValue);
		if( (_pfLess)(largestValue, leftValue) )
		{
			largestValue = leftValue;
			largest = left;		
		}
	}

	if(largest != _root)
	{
		IdxSwap(_vector, _root, largest);
		Heapify(_vector, largest, _pfLess, _size);
	}
}



static void HeapifyAll(Vector* _vector, LessThanComparator _pfLess, size_t _size)
{
	size_t i;

	for(i = _size/2; i > 0; --i)
	{
		Heapify(_vector, i, _pfLess, _size);
	}
}


/***************************************************************************************************************/
static Heap* CreateInitilizeHeap(Vector* _vector, LessThanComparator _pfLess)
{
	Heap* heap;
	size_t numOfItems;

	heap = (Heap*)malloc(sizeof(Heap) );
	
	if(NULL == heap)
	{
		return NULL;
	}

	numOfItems = Vector_Size(_vector);
	heap->m_vec = _vector;
	heap->m_heapSize = numOfItems;
	heap->m_less = _pfLess;

	return heap;
}

/***************************************************************************************************************/
static void* DeleteMax(Heap* _heap)
{
	void* _pValue;

	IdxSwap(_heap->m_vec, 1, _heap->m_heapSize--);
	Vector_Remove(_heap->m_vec, &_pValue);
	HeapifyAll(_heap->m_vec, _heap->m_less, _heap->m_heapSize);

	return _pValue;
}
/*-------------------------------------------------------------------*/
void* Heap_Extract(Heap* _heap)
{
	if(NULL == _heap || _heap->m_heapSize == 0)
	{
		return NULL;
	}

	return DeleteMax(_heap);
}


	Heap* Heap_Build(Vector* _vector, LessThanComparator _pfLess)
{
	Heap* heap;

	if(NULL == _vector)
	{
		return NULL;
	}

	heap = CreateInitilizeHeap(_vector, _pfLess);

	HeapifyAll(heap->m_vec, heap->m_less, heap->m_heapSize);


	return heap;
}
		
 
/***************************************************************************************************************/
Vector* Heap_Destroy(Heap** _heap)
{	
    Vector* vector;
	if(NULL == _heap || NULL == *_heap)
	{
		return NULL;
	}
	vector = (*_heap)->m_vec;
	free(*_heap);
	_heap = NULL;
	return vector;
 }
/***************************************************************************************************************/
Heap_ResultCode Heap_Insert(Heap* _heap, void* _element)
{
	size_t index;
	
	Vector_Append(_heap->m_vec, _element);
	
	index = Vector_Size( _heap->m_vec);

	BubbleUp(_heap->m_vec , index, _heap->m_less);
	
	++_heap->m_heapSize;
	
	return HEAP_SUCCESS;
}

 
/***************************************************************************************************************/
const void* Heap_Peek(const Heap* _heap)
{
	void* element;

	if (NULL == _heap)
	{
		return NULL;
	}
	if (VECTOR_SUCCESS != Vector_Get(_heap->m_vec, 1 , &element))
	{
		return NULL;
	}
	
	return element;
}
/***************************************************************************************************************/
size_t Heap_Size(const Heap* _heap)
{
	if (NULL == _heap)
	{
		return 0;
	}

 	return _heap->m_heapSize;

}
/***************************************************************************************************************/

size_t Heap_ForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t heapSize = _heap->m_heapSize;
	size_t i = 1;
	void* element;

	if (NULL == _heap || NULL == _act || NULL == _context)
	{
		return 0;
	}
	
	for (i = 1; i <= heapSize; ++i)
	{
		Vector_Get(_heap->m_vec, i, &element);
		if (! (_act(element, _context)))
		{
			break;
		}
	}
	printf("\n");
	
	return i - 1;
}



void Heap_Sort(Vector* _vec, LessThanComparator _pfLess)
{
	Heap* heap;
	void* maxElement;
	size_t heapSize = Vector_Size(_vec);
	size_t i = 0;
	size_t last = 0, first = 1;

	if (NULL == _vec || NULL == _pfLess)
	{
		return;
	}
	heap = Heap_Build(_vec, _pfLess);
	if (NULL == heap)
	{
		return;
	}
	
	for (i = 0; i < heapSize; ++i)
	{
		Vector_Get(_vec, first, &maxElement);
		last = heapSize - i; 
		IdxSwap(_vec, first, last);

		Heapify(_vec, first, _pfLess, last-1);
		
	}
}





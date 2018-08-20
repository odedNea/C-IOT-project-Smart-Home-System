#include <stdlib.h> /* realloc, malloce */
#include <assert.h>
#include "vector.h"


struct Vector
{
	void**    m_items;
	
	size_t  m_originalSize;   /* original allocated space for items)	*/
	size_t  m_size;           /* actual allocated space for items) */
	size_t  m_nItems;     	  /* actual number of items */
	size_t  m_blockSize;	  /* the chunk size to be allocated when no space */
};

/**********************************************************************************/

/**********************************************************************************/
static Vector_Result initializeVector(Vector* _vector, size_t _initialSize, size_t _extensionBblockSize)
{
	_vector->m_blockSize = _extensionBblockSize;
	_vector->m_size = _initialSize;
	_vector->m_nItems = 0;
	_vector->m_originalSize = _initialSize;
	
	return VECTOR_SUCCESS;
}

/**********************************************************************/
static Vector* allocateVector(size_t _initialSize)
{
	Vector* vector;
	void** tmp;
	
	if( (vector=(Vector*)malloc(sizeof(Vector)) ) == NULL)
	{	
		return NULL;
	}
	
	if( ( tmp=(void**)calloc(_initialSize, sizeof(void*)) ) == NULL)
	{	free(vector);
		return NULL;
	}

	vector->m_items = tmp; 

	return vector; 
}
/**********************************************************************/
static Vector_Result checkAndDoRealloc(Vector* _vector)
{
	void** tmp;
	if(_vector->m_nItems == _vector->m_size)
	{		
		if (0 == _vector->m_blockSize)
		{		
			return VECTOR_OVERFLOW;
		}
		
		tmp = (void**)realloc(_vector->m_items,(_vector->m_size + _vector->m_blockSize)*sizeof(void*));
		if (NULL == tmp)
		{
			return VECTOR_ALLOCATION_ERROR;
		}	

		_vector->m_items = tmp;
		_vector->m_size +=_vector->m_blockSize;		
	}

	return VECTOR_SUCCESS;
}
/**********************************************************************/
static Vector_Result checkShrinkRealloc(Vector* _vector)
{
	void** tmp;
	
	if(_vector->m_size <=  _vector->m_originalSize  )
	{
		return VECTOR_SUCCESS;
	}
	
	
	if(((_vector->m_size - _vector->m_nItems) > _vector->m_blockSize))
	{		
		
		tmp = (void**)realloc(_vector->m_items,(_vector->m_size - _vector->m_blockSize) * sizeof(void*));
		if(NULL == tmp)
		{
			return VECTOR_ALLOCATION_ERROR;
		}	

		_vector->m_items = tmp;
		_vector->m_size -= _vector->m_blockSize;		
	}

	return VECTOR_SUCCESS;
}
/***************						******************************************/
/***************  program start here   ******************************************/


Vector* Vector_Create(size_t _initialCapacity, size_t _blockSize)
{
	
	/* create temp pointer */
	Vector* vector;
	
	if (0 == _initialCapacity && 0 == _blockSize)
	{
		return NULL;
	}
	if ( (vector = allocateVector(_initialCapacity)) == NULL )
	{
		return NULL;
	}
	
	
	initializeVector(vector, _initialCapacity, _blockSize);

	return vector;

}
/**********************************************************************************/
void Vector_Destroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	size_t i = 0;

	if(NULL == _vector)
	{
		return;
	}
		if (_elementDestroy)
		{
			for (i = 0; i < (*_vector)->m_nItems; ++i)
			{
				_elementDestroy((*_vector)->m_items[i]);
			}
		}
		
		free((*_vector)->m_items);
		(*_vector)->m_items = NULL; /* TODO add this check above */
		free(*_vector);
		*_vector = NULL;
}


/**********************************************************************************/
Vector_Result Vector_Append(Vector* _vector, void* _item)
{	
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	
	assert(NULL != _item);
	
	if( checkAndDoRealloc(_vector) != VECTOR_SUCCESS )
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	
	
	_vector->m_items[_vector->m_nItems] = _item;
	++_vector->m_nItems;
	
	return VECTOR_SUCCESS;
}





/**********************************************************************************/
Vector_Result Vector_Remove(Vector* _vector, void** _pValue)	
{		
		if (NULL == _vector || NULL == _vector->m_items)
		{
			return VECTOR_UNITIALIZED_ERROR;
		}
		
		if (0 == _vector->m_nItems)
		{
			return VECTOR_UNDERFLOW;
		}
		
		*_pValue = _vector->m_items[--_vector->m_nItems];

		if ( checkShrinkRealloc(_vector) != VECTOR_SUCCESS )
		{
			return VECTOR_ALLOCATION_ERROR;
		}

	return VECTOR_SUCCESS;
		

}


/**********************************************************************************/

Vector_Result Vector_Get(const Vector* _vector, size_t _index, void** _pValue)
{		

		if(NULL == _vector || NULL == _pValue)
		{
			return VECTOR_UNITIALIZED_ERROR;
		}
		
		if(_index  > _vector->m_nItems || _index < 1)
		{
			return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
		}
		
		*_pValue = _vector->m_items[_index-1];
		
		return VECTOR_SUCCESS;
}

/**********************************************************************************/

Vector_Result Vector_Set(Vector* _vector, size_t _index, void*  _value)
{
		if (NULL == _vector)
		{
			return VECTOR_UNITIALIZED_ERROR;
		}
		
		if (_index  > _vector->m_nItems || _index < 1)
		{
			return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
		}

	 	_vector->m_items[_index-1] = _value;
		
		return VECTOR_SUCCESS;
}

/**********************************************************************************/

size_t Vector_Size(const Vector* _vector)
{
	if (NULL == _vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}

	return  _vector->m_nItems;

}
/**********************************************************************************/

size_t Vector_Capacity(const Vector* _vector)
{
	if (NULL == _vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}

	return  _vector->m_size;

}

/**********************************************************************************/

 size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
/*	size_t noe = _vector->m_nItems;*/
	size_t i = 0;
	
	if (NULL == _vector || NULL == _vector->m_items)
	{
		return 0;
	}

	while (NULL != _vector->m_items[i] && _action(_vector->m_items[i], i, _context))
	{
		++i;
	}

	return i;
}


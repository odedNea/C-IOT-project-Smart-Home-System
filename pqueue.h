#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h>  /* size_t */

typedef struct PQ PQ;


typedef int	(*LessThan)(const void *_left, const void *_right);


/**  
 * @brief creates a PQ
 * @return a pointer to PQ
 */
PQ* PQCreate(LessThan _Less);

/**  
 * @brief Dynamically deallocate a previously allocated vector  
 * @param[in] PQ - pointer to PQ.
 * @return void
 */
void PQDestroy(PQ** _PQ);

/**  
 * @brief Add an element to pqueue.  
 * @param[in] _pqueue - pointer to PQ.
 * @param[in] _element - Element to insert. can't be null
 */
void PQInsert(PQ* _pqueue, void* _element);

/**  
 * @brief Extract first element in pqueue.  
 * @param[in] _pqueue - pointer to PQ.
 * @return pointer to element, can be null if heap is empty. 
 */
void* PQExtract(PQ* _pqueue);

/**  
 * @brief Get the current size (number of elements) in the pqueue.  
 * @param[in] _pqueue - the pqueue.
 * @return number of elements or zero if empty. 
 */
size_t PQSize(PQ* _pqueue);

#endif /*__PQUEUE_H__ */
